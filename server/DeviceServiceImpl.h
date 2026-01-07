#pragma once

#include <grpcpp/grpcpp.h>
#include "device.grpc.pb.h"
#include "DeviceManager.h"

class DeviceServiceImpl final : public devicefleet::DeviceFleetService::Service
{
public:
    explicit DeviceServiceImpl(DeviceManager& manager);

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

    

private:
    DeviceManager& manager_;
};