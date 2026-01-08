#pragma once
#include <queue>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

#include "device.pb.h"
#include "DeviceManager.h"

struct Action {
    std::string action_id;
    std::string device_id;
    devicefleet::ActionStatus status;
    devicefleet::ActionType type;
};

class ActionManager {
public:

    explicit ActionManager(DeviceManager& deviceManager, size_t workers = 4);

    ~ActionManager();

    bool initiateDeviceAction(const std::string& deviceId,
                            const devicefleet::ActionType& type,
                            const devicefleet::ActionParams& params,
                            std::string& outActionId,
                            std::string& outMessage);

    bool getDeviceActionStatus(const std::string& actionId,
                                devicefleet::ActionStatus& status) const;

private:

    void workerLoop();

    std::vector<std::thread> workers_;
    std::atomic<bool> shutdown_{false};

    std::queue<std::string> tasksQueue_;
    std::mutex queueMutex_;
    std::condition_variable cv_;

    std::unordered_map<std::string, Action> actions_;
    mutable std::mutex actionsMutex_;

    DeviceManager& deviceManager_;

    const size_t MAX_QUEUE_SIZE = 100;
};