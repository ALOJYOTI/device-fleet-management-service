#pragma once

#include <grpcpp/grpcpp.h>
#include "device.grpc.pb.h"
#include "DeviceManager.h"
#include "ActionManager.h"

class DeviceServiceImpl final : public devicefleet::DeviceFleetService::Service
{
public:
    explicit DeviceServiceImpl(DeviceManager& dm, ActionManager& am);

    grpc::Status RegisterDevice(grpc::ServerContext* context,
        const devicefleet::RegisterDeviceRequest* request,
        devicefleet::RegisterDeviceResponse* response
    ) override;

    grpc::Status SetDeviceStatus(grpc::ServerContext* context,
        const devicefleet::SetDeviceStatusRequest* request,
        devicefleet::SetDeviceStatusResponse* response
    ) override;

    grpc::Status GetDeviceInfo(grpc::ServerContext* context,
        const devicefleet::GetDeviceInfoRequest* request,
        devicefleet::GetDeviceInfoResponse* response
    ) override;

    grpc::Status ListDevices(grpc::ServerContext*,
        const devicefleet::ListDevicesRequest*,
        devicefleet::ListDevicesResponse*) override;


    grpc::Status InitiateDeviceAction(grpc::ServerContext*,
        const devicefleet::InitiateDeviceActionRequest*,
        devicefleet::InitiateDeviceActionResponse*) override;

    grpc::Status GetDeviceActionStatus(grpc::ServerContext*,
        const devicefleet::GetDeviceActionStatusRequest*,
        devicefleet::GetDeviceActionStatusResponse*) override;

    

private:
    DeviceManager& deviceManager_;
    ActionManager& actionManager_;
};