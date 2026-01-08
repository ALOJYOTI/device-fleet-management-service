find_program(CXXTESTGEN_EXECUTABLE cxxtestgen REQUIRED)

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/tests/runner.cpp
    COMMAND ${CXXTESTGEN_EXECUTABLE} --error-printer
            -o ${CMAKE_SOURCE_DIR}/tests/runner.cpp
            ${CMAKE_SOURCE_DIR}/tests/DeviceManagerTest.h
            ${CMAKE_SOURCE_DIR}/tests/ActionManagerTest.h
    DEPENDS
        ${CMAKE_SOURCE_DIR}/tests/DeviceManagerTest.h
        ${CMAKE_SOURCE_DIR}/tests/ActionManagerTest.h
)

add_executable(DeviceServerTests
    ${CMAKE_SOURCE_DIR}/tests/runner.cpp
    ../server/DeviceManager.cpp
    ../server/ActionManager.cpp
)

target_include_directories(DeviceServerTests PRIVATE
    ${CMAKE_SOURCE_DIR}/server
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(DeviceServerTests
    proto_files
    pthread
)