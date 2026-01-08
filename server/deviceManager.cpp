#include "DeviceManager.h"
#include "Validations.h"
#include "Logger.h"

bool DeviceManager::registerDevice(const std::string& deviceId, devicefleet::DeviceState deviceState){
    std::unique_lock<std::shared_mutex> lock(mutex_);
    LOG_DEBUG("[DeviceManager] RegisterDevice request for device: " << deviceId);
    if(devices_.count(deviceId)){
        LOG_DEBUG( "[DeviceManager] Device already Registered: " << deviceId);
        return false;
    }
    devicefleet::Device device;
    device.set_device_id(deviceId);
    device.set_device_state(deviceState);
    devices_[deviceId] = device;

    LOG_DEBUG("[DeviceManager] Device registered: " << deviceId);
    return true;

}

bool DeviceManager::setDeviceStatus(const std::string& deviceId, devicefleet::DeviceState deviceState){
    std::unique_lock<std::shared_mutex> lock(mutex_);
    LOG_DEBUG("[DeviceManager] SetDeviceStatus request for device: " << deviceId);
    if(!devices_.count(deviceId)){
        LOG_DEBUG("[DeviceManager] Device not Registered: " << deviceId);
        return false;
    }
    devices_[deviceId].set_device_state(deviceState);
    LOG_DEBUG("[DeviceManager] Device Status updated: " << deviceId);
    return true;
}

bool DeviceManager::getDeviceInfo(const std::string& deviceId, devicefleet::Device& device) const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    LOG_DEBUG("[DeviceManager] Get device info: " << deviceId);

    auto it = devices_.find(deviceId);
    if (it == devices_.end()) {
        LOG_DEBUG("[DeviceManager] Device not found: " << deviceId);
        return false;
    }
    device = it->second;
    LOG_DEBUG("[DeviceManager] Device returned: " << deviceId);
    return true;
}

std::vector<devicefleet::Device> DeviceManager::listDevices() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    std::vector<devicefleet::Device> result;
    for (const auto& [_, device] : devices_) {
        result.push_back(device);
    }
    return result;
}

bool DeviceManager::deviceExists(const std::string& id) const {
    std::lock_guard<std::shared_mutex> lock(mutex_);
    return devices_.count(id) > 0;
}

bool DeviceManager::setInternalDeviceState(const std::string& id,
                    devicefleet::DeviceState state) {

    if (!isValidInternalState(state)) {
        LOG_DEBUG("[DeviceManager] INVALID device state "<< state);
        return false;
    }
    
    std::lock_guard<std::shared_mutex> lock(mutex_);
    auto it = devices_.find(id);
    if (it == devices_.end()) {
        LOG_DEBUG("[DeviceManager] Device does not exists "<< id);
        return false;
    }

    it->second.set_device_state(state);
    return true;   
}
