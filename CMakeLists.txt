cmake_minimum_required(VERSION 3.16)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

project(DeviceFleetService CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

add_subdirectory(proto)
add_subdirectory(server)
add_subdirectory(tests)