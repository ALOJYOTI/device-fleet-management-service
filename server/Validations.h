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