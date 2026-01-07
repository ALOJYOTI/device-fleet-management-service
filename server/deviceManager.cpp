#include "DeviceManager.h"

bool DeviceManager::registerDevice(const std::string& deviceId, devicefleet::DeviceState deviceState){
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::cout << "[DeviceManager] RegisterDevice request for device: " << deviceId << std::endl;
    if(devices_.count(deviceId)){
        std::cout << "[DeviceManager] Device already Registered: " << deviceId << std::endl;
        return false;
    }
    devicefleet::Device device;
    device.set_device_id(deviceId);
    device.set_device_state(deviceState);
    devices_[deviceId] = device;

    std::cout<< "[DeviceManager] Device registered: " << deviceId << std::endl;
    return true;

}

bool DeviceManager::setDeviceStatus(const std::string& deviceId, devicefleet::DeviceState deviceState){
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::cout << "[DeviceManager] SetDeviceStatus request for device: " << deviceId << std::endl;
    if(!devices_.count(deviceId)){
        std::cout << "[DeviceManager] Device not Registered: " << deviceId << std::endl;
        return false;
    }
    devices_[deviceId].set_device_state(deviceState);
    std::cout << "[DeviceManager] Device Status updated: " << deviceId << std::endl;
    return true;
}

bool DeviceManager::getDeviceInfo(const std::string& deviceId, devicefleet::Device& device) {
    std::lock_guard<std::shared_mutex> lock(mutex_);
    std::cout << "[DeviceManager] Get device info: " << deviceId << std::endl;

    if (!devices_.count(deviceId)) {
        std::cout << "[DeviceManager] Device not found: " << deviceId << std::endl;
        return false;
    }
    device = devices_[deviceId];
    std::cout << "[DeviceManager] Device returned: " << deviceId << std::endl;
    return true;
}