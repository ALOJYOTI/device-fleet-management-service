#include "DeviceServiceImpl.h"
#include "Validations.h"

DeviceServiceImpl::DeviceServiceImpl(DeviceManager& manager)
    : manager_(manager) {}

// ---------------- RegisterDevice ----------------//

grpc::Status DeviceServiceImpl::RegisterDevice(grpc::ServerContext* context,
    const devicefleet::RegisterDeviceRequest* request,
    devicefleet::RegisterDeviceResponse* response)
{
    const std::string& deviceId = request->device_id();
    auto state = request->initial_state();

    if(!isValidDeviceId(deviceId)){
        response->set_success(false);
        response->set_message("Device Id can not be empty");
        return grpc::Status::OK;
    }

    if (!isValidDeviceState(state)){
        response->set_success(false);
        response->set_message("Invalid device state");
        return grpc::Status::OK;
    }

    bool success = manager_.registerDevice(deviceId, state);
    if(!success){
        response->set_success(false);
        response->set_message("Device already Registered");
    }
    else{
        response->set_success(true);
        response->set_message("Device Registered Successfully");
    }
    return grpc::Status::OK;
}

// ---------------- SetDeviceStatus ----------------//

grpc::Status DeviceServiceImpl::SetDeviceStatus(grpc::ServerContext* context,
    const devicefleet::SetDeviceStatusRequest* request,
    devicefleet::SetDeviceStatusResponse* response)
{
    const std::string& deviceId = request->device_id();
    auto state = request->state();

    if(!isValidDeviceId(deviceId)){
        response->set_success(false);
        response->set_message("Device Id can not be empty");
        return grpc::Status::OK;
    }

    if (!isValidDeviceState(state)){
        response->set_success(false);
        response->set_message("Invalid device state");
        return grpc::Status::OK;
    }

    bool success = manager_.setDeviceStatus(deviceId, state);

    if (!success){
        response->set_success(false);
        response->set_message("Device not found");
    } 
    else{
        response->set_success(true);
        response->set_message("Device status updated");
    }
    return grpc::Status::OK;
}

// ---------------- GetDeviceInfo ----------------//

grpc::Status DeviceServiceImpl::GetDeviceInfo(grpc::ServerContext* context,
    const devicefleet::GetDeviceInfoRequest* request,
    devicefleet::GetDeviceInfoResponse* response)
{
    if (!isValidDeviceId(request->device_id())){
        response->set_found(false);
        return grpc::Status::OK;
    }
    devicefleet::Device device;
    bool found = manager_.getDeviceInfo(request->device_id(), device);

    response->set_found(found);
    if (found) {
        *response->mutable_device() = device;
    }
    return grpc::Status::OK;
}
