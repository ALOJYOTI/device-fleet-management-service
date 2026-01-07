cmake_minimum_required(VERSION 3.10)
project(device_fleet)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

add_subdirectory(../proto proto_build)

add_executable(device_server
    main.cpp
    DeviceManager.cpp
)

target_link_libraries(device_server
    proto_files
    gRPC::grpc++
    protobuf::libprotobuf
)
