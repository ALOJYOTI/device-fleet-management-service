#pragma once
#include "DeviceManager.h"
#include <unordered_map>

class MockDeviceManager : public DeviceManager {
public:
    bool exists = true;
    devicefleet::DeviceState currentState = devicefleet::IDLE;

    bool deviceExists(const std::string&) const override {
        return exists;
    }

    bool getDeviceInfo(const std::string&, devicefleet::Device& d) const override {
        d.set_device_state(currentState);
        return true;
    }

    bool setInternalDeviceState(const std::string&, devicefleet::DeviceState s) override {
        currentState = s;
        return true;
    }
};
