cmake_minimum_required(VERSION 3.10)
project(device_fleet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

add_subdirectory(../proto proto_build)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_BUILD)
endif()

add_executable(device_server
    main.cpp
    DeviceManager.cpp
    DeviceServiceImpl.cpp
)

target_link_libraries(device_server
    proto_files
    gRPC::grpc++
    protobuf::libprotobuf
)
