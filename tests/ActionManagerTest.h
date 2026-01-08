#include <cxxtest/TestSuite.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "ActionManager.h"
#include "mocks/MockDeviceManager.h"

class ActionManagerTest : public CxxTest::TestSuite {
public:

    void testRejectsUnregisteredDevice() {
        std::cout << "\n========== testRejectsUnregisteredDevice ==========\n";

        MockDeviceManager dm;
        dm.exists = false;

        ActionManager mgr(dm, 1);

        std::string actionId, msg;
        bool ok = mgr.initiateDeviceAction("dev1", devicefleet::SOFTWARE_UPDATE, {}, actionId, msg);

        TS_ASSERT(!ok);
        TS_ASSERT(msg.find("not registered") != std::string::npos);
    }

    void testRejectsNonIdleDevice() {
        std::cout << "\n========== testRejectsNonIdleDevice ==========\n";

        MockDeviceManager dm;
        dm.currentState = devicefleet::BUSY;

        ActionManager mgr(dm, 1);

        std::string actionId, msg;
        bool ok = mgr.initiateDeviceAction("dev1", devicefleet::SOFTWARE_UPDATE, {}, actionId, msg);

        TS_ASSERT(!ok);
        TS_ASSERT(msg.find("not available") != std::string::npos);
    }

    void testAcceptsValidAction() {
        std::cout << "\n========== testAcceptsValidAction ==========\n";

        MockDeviceManager dm;
        ActionManager mgr(dm, 1);

        std::string actionId, msg;
        bool ok = mgr.initiateDeviceAction("dev1", devicefleet::SOFTWARE_UPDATE, {}, actionId, msg);

        TS_ASSERT(ok);
        TS_ASSERT(!actionId.empty());
    }

    void testActionStatusTracking() {
        std::cout << "\n========== testActionStatusTracking ==========\n";

        MockDeviceManager dm;
        ActionManager mgr(dm, 1);

        std::string actionId, msg;
        mgr.initiateDeviceAction("dev1", devicefleet::SOFTWARE_UPDATE, {}, actionId, msg);

        devicefleet::ActionStatus st;
        bool found = mgr.getDeviceActionStatus(actionId, st);

        TS_ASSERT(found);
        TS_ASSERT(st == devicefleet::PENDING || st == devicefleet::RUNNING);
    }

    void testWorkerStartsExecution() {
        std::cout << "\n========== testWorkerStartsExecution ==========\n";

        MockDeviceManager dm;
        ActionManager mgr(dm, 1);

        std::string actionId, msg;
        mgr.initiateDeviceAction("dev1", devicefleet::SOFTWARE_UPDATE, {}, actionId, msg);

        devicefleet::ActionStatus st = devicefleet::PENDING;

        // Wait only for the worker to pick up the job
        for (int i = 0; i < 20; ++i) {
            mgr.getDeviceActionStatus(actionId, st);
            if (st == devicefleet::RUNNING)
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        TS_ASSERT_EQUALS(st, devicefleet::RUNNING);
    }
};
