#include <iostream>
#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "device.grpc.pb.h"
#include "DeviceManager.h"
#include "DeviceServiceImpl.h"
#include "Logger.h"

int main()
{
    std::string serverAddress = "0.0.0.0:50051";

    DeviceManager deviceManager;
    ActionManager actionManager(deviceManager);
    DeviceServiceImpl service(deviceManager, actionManager);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    LOG_INFO("Device Fleet Server starting on "<< serverAddress);
    server->Wait();
    return 0;
}