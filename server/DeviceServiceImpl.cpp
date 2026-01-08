#include "DeviceServiceImpl.h"
#include "Validations.h"

DeviceServiceImpl::DeviceServiceImpl(DeviceManager& dm, ActionManager& am)
    : deviceManager_(dm), actionManager_(am) {}

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

    if (!isValidClientSettableState(state)){
        response->set_success(false);
        response->set_message("Invalid device state");
        return grpc::Status::OK;
    }

    bool success = deviceManager_.registerDevice(deviceId, state);
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

    if (!isValidClientSettableState(state)){
        response->set_success(false);
        response->set_message("Invalid device state");
        return grpc::Status::OK;
    }

    bool success = deviceManager_.setDeviceStatus(deviceId, state);

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
    bool found = deviceManager_.getDeviceInfo(request->device_id(), device);

    response->set_found(found);
    if (found) {
        *response->mutable_device() = device;
    }
    return grpc::Status::OK;
}

grpc::Status DeviceServiceImpl::ListDevices(
    grpc::ServerContext*,
    const devicefleet::ListDevicesRequest*,
    devicefleet::ListDevicesResponse* response) {

    auto devices = deviceManager_.listDevices();

    for (const auto& d : devices) {
        auto* dev = response->add_devices();
        *dev = d;
    }

    return grpc::Status::OK;
}



grpc::Status DeviceServiceImpl::InitiateDeviceAction(grpc::ServerContext*,
                                      const devicefleet::InitiateDeviceActionRequest*  request,
                                      devicefleet::InitiateDeviceActionResponse* response)
{
    if (!isValidDeviceId(request->device_id())) {
        response->set_success(false);
        response->set_message("Device ID is empty");
        return grpc::Status::OK;
    }

    if (!isValidActionType(request->action_type())) {
        response->set_success(false);
        response->set_message("Invalid action type");
        return grpc::Status::OK;
    }

    if (!isValidSoftwareVersion(request->params().target_version())) {
        response->set_success(false);
        response->set_message("Invalid software version");
        return grpc::Status::OK;
    }

    std::string actionId;
    std::string message;

    bool success = actionManager_.initiateDeviceAction(
        request->device_id(),
        request->action_type(),
        request->params(),
        actionId,
        message);

    response->set_success(success);
    response->set_message(message);
    response->set_action_id(actionId);

    return grpc::Status::OK;
}

grpc::Status DeviceServiceImpl::GetDeviceActionStatus(grpc::ServerContext*,
                                       const devicefleet::GetDeviceActionStatusRequest* request,
                                       devicefleet::GetDeviceActionStatusResponse* response)
{
    devicefleet::ActionStatus status;
    if(!actionManager_.getDeviceActionStatus(request->action_id(), status)) {
        response->set_found(false);
        return grpc::Status::OK;
    }

    response->set_found(true);
    response->set_status(status);
    return grpc::Status::OK;
}

