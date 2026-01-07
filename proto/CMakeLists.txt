find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/device.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILE})

add_library(proto_files
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(proto_files
    protobuf::libprotobuf
    gRPC::grpc++
)
