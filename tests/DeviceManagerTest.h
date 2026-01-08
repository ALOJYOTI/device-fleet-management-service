#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../server/DeviceManager.h"

class DeviceManagerTest : public CxxTest::TestSuite {
public:

    void testRegisterDeviceSuccess() {
        std::cout << "\n========== testRegisterDeviceSuccess ==========\n";
        DeviceManager dm;
        TS_ASSERT(dm.registerDevice("dev1", devicefleet::IDLE));
    }

    void testRegisterDuplicateFails() {
        std::cout << "\n========== testRegisterDuplicateFails ==========\n";
        DeviceManager dm;
        dm.registerDevice("dev1", devicefleet::IDLE);
        TS_ASSERT(!dm.registerDevice("dev1", devicefleet::BUSY));
    }

    void testGetDeviceInfoSuccess() {
        std::cout << "\n========== testGetDeviceInfoSuccess ==========\n";
        DeviceManager dm;
        dm.registerDevice("dev1", devicefleet::IDLE);

        devicefleet::Device d;
        TS_ASSERT(dm.getDeviceInfo("dev1", d));
        TS_ASSERT_EQUALS(d.device_state(), devicefleet::IDLE);
    }

    void testGetDeviceInfoFails() {
        std::cout << "\n========== testGetDeviceInfoFails ==========\n";
        DeviceManager dm;
        devicefleet::Device d;
        TS_ASSERT(!dm.getDeviceInfo("unknown", d));
    }

    void testSetDeviceStatusSuccess() {
        std::cout << "\n========== testSetDeviceStatusSuccess ==========\n";
        DeviceManager dm;
        dm.registerDevice("dev1", devicefleet::IDLE);

        TS_ASSERT(dm.setDeviceStatus("dev1", devicefleet::MAINTENANCE));
    }

    void testSetDeviceStatusFailsOnMissingDevice() {
        std::cout << "\n========== testSetDeviceStatusFailsOnMissingDevice ==========\n";
        DeviceManager dm;
        TS_ASSERT(!dm.setDeviceStatus("dev1", devicefleet::IDLE));
    }

    void testListDevices() {
        std::cout << "\n========== testListDevices ==========\n";
        DeviceManager dm;
        dm.registerDevice("dev1", devicefleet::IDLE);
        dm.registerDevice("dev2", devicefleet::BUSY);

        auto devices = dm.listDevices();
        TS_ASSERT_EQUALS(devices.size(), 2);
    }

    void testDeviceExists() {
        std::cout << "\n========== testDeviceExists ==========\n";
        DeviceManager dm;
        dm.registerDevice("dev1", devicefleet::IDLE);

        TS_ASSERT(dm.deviceExists("dev1"));
        TS_ASSERT(!dm.deviceExists("dev2"));
    }

    void testSetInternalDeviceStateValid() {
        std::cout << "\n========== testSetInternalDeviceStateValid ==========\n";
        DeviceManager dm;
        dm.registerDevice("dev1", devicefleet::IDLE);

        TS_ASSERT(dm.setInternalDeviceState("dev1", devicefleet::UPDATING));
    }

    void testSetInternalDeviceStateInvalid() {
        std::cout << "\n========== testSetInternalDeviceStateInvalid ==========\n";
        DeviceManager dm;
        dm.registerDevice("dev1", devicefleet::IDLE);

        TS_ASSERT(!dm.setInternalDeviceState("dev1", devicefleet::BUSY));
    }

    void testSetInternalDeviceStateMissingDevice() {
        std::cout << "\n========== testSetInternalDeviceStateMissingDevice ==========\n";
        DeviceManager dm;
        TS_ASSERT(!dm.setInternalDeviceState("dev1", devicefleet::UPDATING));
    }
};