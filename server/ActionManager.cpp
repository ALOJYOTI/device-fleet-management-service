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
        outMessage = "Device : " + deviceId + " not registered";
        LOG_DEBUG("[ActionManager] initiateDeviceAction failed: device not registered");
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
            LOG_INFO("[ActionManager] Action completed: " << actionId);
            if(!deviceManager_.setInternalDeviceState(action.device_id,
                                                  devicefleet::IDLE))
            {
                LOG_INFO("[ActionManager] Internal error: failed to set state for device "
                << action.device_id);
            }
        } else {
            LOG_INFO("[ActionManager] Action failed: " << actionId << ", recovering device");

            if(!deviceManager_.setInternalDeviceState(action.device_id,
                                                  devicefleet::RECOVERING))
            {
                LOG_INFO("[ActionManager] Internal error: failed to set RECOVERING for device "
                << action.device_id);
            }
            std::this_thread::sleep_for(std::chrono::seconds(5));
            if(!deviceManager_.setInternalDeviceState(action.device_id,
                                                  devicefleet::IDLE))
            {
                LOG_INFO("[ActionManager] Internal error: failed to reset state for device "
                << action.device_id);
            }
        }
    }
}
