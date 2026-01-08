#include "ActionManager.h"
#include "Logger.h"

#include <chrono>
#include <cstdlib>

std::atomic<int> actionCounter{0};

ActionManager::ActionManager(DeviceManager& deviceManager, size_t workers)
    :  deviceManager_(deviceManager) {

    LOG_INFO("Starting ActionManager with " << workers << " worker threads");
    
    for(size_t worker = 0; worker < workers; worker++)
        this->workers_.emplace_back(&ActionManager::workerLoop, this);
    }

ActionManager::~ActionManager() {
    LOG_INFO("[ActionManager] Shutting down ActionManager");
    shutdown_ = true;
    cv_.notify_all();

    for(auto& worker : workers_)
    {
        if(worker.joinable()) {
            worker.join();
        }
    }
    LOG_INFO("[ActionManager] ActionManager shutdown complete");
}

bool ActionManager::initiateDeviceAction(const std::string& deviceId,
                            const devicefleet::ActionType& type,
                            const devicefleet::ActionParams& params,
                            std::string& outActionId,
                            std::string& outMessage)
{
    LOG_DEBUG("[ActionManager] Received initiateDeviceAction request for device: " << deviceId);

    if (!deviceManager_.deviceExists(deviceId)) {
        outMessage = "Device : " + deviceId + " ,not registered";
        LOG_DEBUG("[ActionManager] initiateDeviceAction failed: device not registered");
        return false;
    }

    devicefleet::Device device;
    if (!deviceManager_.getDeviceInfo(deviceId, device)) {
        outMessage = "Device : " + deviceId + " ,state not available";
        LOG_DEBUG("[ActionManager] initiateDeviceAction failed: device state not available");
        return false;
    }

    if (device.device_state() != devicefleet::IDLE) {
    outMessage = "Device not available for action, current device state: "+
                    devicefleet::DeviceState_Name(device.device_state());
    LOG_DEBUG("[ActionManager] initiateDeviceAction failed: device not available for action");
    return false;
    }

    std::string newActionId;

    {
        std::lock_guard<std::mutex> qlock(queueMutex_);
        if(tasksQueue_.size() >= MAX_QUEUE_SIZE)
        {
            outMessage = "System overloaded, try later";
            LOG_DEBUG("[ActionManager] initiateDeviceAction rejected: queue full");
            return false;
        }

        newActionId = "action_" + std::to_string(++actionCounter);

        {
            std::lock_guard<std::mutex> alock(actionsMutex_);
            actions_[newActionId] = {newActionId, deviceId, devicefleet::ActionStatus::PENDING, type};
        }

        tasksQueue_.push(newActionId);
    }

    cv_.notify_one();

    LOG_INFO("[ActionManager] Action accepted: " << outActionId << " for device " << deviceId);
    outActionId = newActionId;
    outMessage = "Action initiated";
    return true;
}

bool ActionManager::getDeviceActionStatus(const std::string& actionId,
                                devicefleet::ActionStatus& status) const
{
    std::lock_guard<std::mutex> lock(actionsMutex_);
    auto it = actions_.find(actionId);
    if(it == actions_.end()) {
        LOG_DEBUG("[ActionManager] Action not found " << actionId);
        return false;
    }

    status = it->second.status;
    LOG_DEBUG("[ActionManager] Action " << actionId << " status = " << status);
    return true;
}

void ActionManager::workerLoop(){

    LOG_DEBUG("[ActionManager] Worker thread started");

    while (true) {
        std::string actionId;

        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            cv_.wait(lock, [&] { return shutdown_ || !tasksQueue_.empty(); });

            if (shutdown_ && tasksQueue_.empty()) {
                LOG_DEBUG("Worker thread exiting");
                return;
            }

            actionId = tasksQueue_.front();
            tasksQueue_.pop();
        }

        Action action;
        {
            std::lock_guard<std::mutex> alock(actionsMutex_);
            action = actions_[actionId];
            actions_[actionId].status = devicefleet::RUNNING;
        }

        LOG_INFO("[ActionManager] Executing action " << actionId << " on device " << action.device_id);

        if(!deviceManager_.setInternalDeviceState(action.device_id,
                                              devicefleet::UPDATING))
        {
            LOG_INFO("[ActionManager] Internal error: failed to set UPDATING for device "
             << action.device_id);

            {
                std::lock_guard<std::mutex> alock(actionsMutex_);
                actions_[actionId].status = devicefleet::FAILED;
            }
            continue;
        }

        std::this_thread::sleep_for(std::chrono::seconds(30));

        bool success = (std::rand() % 5 != 0); // ~20% failure

        {
            std::lock_guard<std::mutex> alock(actionsMutex_);
            actions_[actionId].status = success ?
                devicefleet::COMPLETED : devicefleet::FAILED;
        }

        if (success) {
            LOG_INFO("[ActionManager] Action completed: action Id: " << actionId);
            if(!deviceManager_.setInternalDeviceState(action.device_id,
                                                  devicefleet::IDLE))
            {
                LOG_INFO("[ActionManager] Internal error: failed to set state for device "
                << action.device_id);
            }
        } 
        else {
            LOG_INFO("[ActionManager] Action failed: action Id : " << actionId << ", entering ERROR state");
            if(!deviceManager_.setInternalDeviceState(action.device_id, devicefleet::ERROR))
            {
                LOG_INFO("[ActionManager] CRITICAL: failed to set ERROR state for device "
                << action.device_id);
                continue;
            }

            if(!deviceManager_.setInternalDeviceState(action.device_id,
                                                  devicefleet::RECOVERING))
            {
                LOG_INFO("[ActionManager] CRITICAL: failed to RECOVER device "
                << action.device_id);
                continue;
            }
            LOG_DEBUG("[ActionManager] Action failed: " << actionId << ", recovering device");
            std::this_thread::sleep_for(std::chrono::seconds(5));
            if(!deviceManager_.setInternalDeviceState(action.device_id,
                                                  devicefleet::IDLE))
            {
                LOG_INFO("[ActionManager] CRITICAL: failed to restore IDLE for device: "
                << action.device_id);
                continue;
            }

            LOG_INFO("[ActionManager] Recovery complete for device " << action.device_id);
        }
    }
}
