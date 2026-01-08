#pragma once
#include <shared_mutex>
#include <unordered_map>
#include <string>
#include "device.pb.h"

class DeviceManager
{
public:
    bool registerDevice(const std::string& deviceId, devicefleet::DeviceState deviceState);
    bool setDeviceStatus(const std::string& deviceId, devicefleet::DeviceState deviceState);
    bool getDeviceInfo(const std::string& deviceId, devicefleet::Device& device) const;
    std::vector<devicefleet::Device> listDevices() const;
    bool deviceExists(const std::string& id) const;
    bool setInternalDeviceState(const std::string& id,
                            devicefleet::DeviceState state);
private:
    std::unordered_map<std::string, devicefleet::Device> devices_;
    mutable std::shared_mutex mutex_;
};