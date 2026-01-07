#include <iostream>
#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "device.grpc.pb.h"
#include "DeviceManager.h"
#include "DeviceServiceImpl.h"

int main()
{
    std::string serverAddress = "0.0.0.0:50051";

    DeviceManager deviceManager;
    DeviceServiceImpl service(deviceManager);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "Device Fleet Server starting on "<< serverAddress << std::endl;
    server->Wait();
    return 0;
}