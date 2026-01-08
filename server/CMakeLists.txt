cmake_minimum_required(VERSION 3.10)
project(device_server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_BUILD)
endif()

add_executable(device_server
    main.cpp
    DeviceManager.cpp
    DeviceServiceImpl.cpp
    ActionManager.cpp
)

target_include_directories(device_server PRIVATE
    ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(device_server
    proto_files
    gRPC::grpc++
    protobuf::libprotobuf
    pthread
)
