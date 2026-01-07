#pragma once
#include <shared_mutex>
#include <unordered_map>
#include <string>
#include "device.pb.h"

class DeviceManager
{
public:
    bool RegisterDevice(const std::string& id, devicefleet::DeviceState state);
    bool SetDeviceStatus(const std::string& id, devicefleet::DeviceState state);
    bool GetDeviceInfo(const std::string& id, devicefleet::Device& device);
private:
    std::unordered_map<std::string, devicefleet::Device> devices_;
    mutable std::shared_mutex mutex;
};