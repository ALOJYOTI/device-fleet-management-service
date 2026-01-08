#pragma once

#include <string>
#include "device.pb.h"

inline bool isValidDeviceId(const std::string& id){
    return !id.empty();
}

inline bool isValidClientSettableState(devicefleet::DeviceState state){
    switch (state) {
        case devicefleet::IDLE:
        case devicefleet::BUSY:
        case devicefleet::OFFLINE:
        case devicefleet::MAINTENANCE:
            return true;
        default:
            return false;
    }
}

inline bool isValidInternalState(devicefleet::DeviceState state) {
    switch (state) {
        case devicefleet::IDLE:
        case devicefleet::UPDATING:
        case devicefleet::RECOVERING:
        case devicefleet::ERROR:
            return true;
        default:
            return false;
    }
}

inline bool isValidActionType(devicefleet::ActionType type) {
    return type == devicefleet::SOFTWARE_UPDATE;
}

inline bool isValidSoftwareVersion(devicefleet::SoftwareVersion v) {
    switch (v) {
        case devicefleet::V1_0:
        case devicefleet::V1_1:
        case devicefleet::V2_0:
            return true;
        default:
            return false;
    }
}