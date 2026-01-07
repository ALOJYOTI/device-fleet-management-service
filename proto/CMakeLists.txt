find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/device.proto)
set(GENERATED_PROTO_DIR ${CMAKE_BINARY_DIR}/generated)

file(MAKE_DIRECTORY ${GENERATED_PROTO_DIR})

add_custom_command(
    OUTPUT
        ${GENERATED_PROTO_DIR}/device.pb.cc
        ${GENERATED_PROTO_DIR}/device.pb.h
        ${GENERATED_PROTO_DIR}/device.grpc.pb.cc
        ${GENERATED_PROTO_DIR}/device.grpc.pb.h
    COMMAND protobuf::protoc
    ARGS
        --grpc_out ${GENERATED_PROTO_DIR}
        --cpp_out ${GENERATED_PROTO_DIR}
        -I ${CMAKE_CURRENT_SOURCE_DIR}
        --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin
        ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
)

add_library(proto_files
    ${GENERATED_PROTO_DIR}/device.pb.cc
    ${GENERATED_PROTO_DIR}/device.grpc.pb.cc
)

target_include_directories(proto_files PUBLIC ${GENERATED_PROTO_DIR})

target_link_libraries(proto_files
    protobuf::libprotobuf
    gRPC::grpc++
)
