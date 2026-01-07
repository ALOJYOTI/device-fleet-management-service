#include "DeviceManager.h"
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

bool DeviceManager::getDeviceInfo(const std::string& deviceId, devicefleet::Device& device) {
    std::lock_guard<std::shared_mutex> lock(mutex_);
    LOG_DEBUG("[DeviceManager] Get device info: " << deviceId);

    if (!devices_.count(deviceId)) {
        LOG_DEBUG("[DeviceManager] Device not found: " << deviceId);
        return false;
    }
    device = devices_[deviceId];
    LOG_DEBUG("[DeviceManager] Device returned: " << deviceId);
    return true;
}