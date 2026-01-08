/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_DeviceManagerTest_init = false;
#include "/mnt/c/STUDY/Device_Fleet_Management_Service/tests/DeviceManagerTest.h"

static DeviceManagerTest suite_DeviceManagerTest;

static CxxTest::List Tests_DeviceManagerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DeviceManagerTest( "/mnt/c/STUDY/Device_Fleet_Management_Service/tests/DeviceManagerTest.h", 5, "DeviceManagerTest", suite_DeviceManagerTest, Tests_DeviceManagerTest );

static class TestDescription_suite_DeviceManagerTest_testRegisterDeviceSuccess : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testRegisterDeviceSuccess() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 8, "testRegisterDeviceSuccess" ) {}
 void runTest() { suite_DeviceManagerTest.testRegisterDeviceSuccess(); }
} testDescription_suite_DeviceManagerTest_testRegisterDeviceSuccess;

static class TestDescription_suite_DeviceManagerTest_testRegisterDuplicateFails : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testRegisterDuplicateFails() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 14, "testRegisterDuplicateFails" ) {}
 void runTest() { suite_DeviceManagerTest.testRegisterDuplicateFails(); }
} testDescription_suite_DeviceManagerTest_testRegisterDuplicateFails;

static class TestDescription_suite_DeviceManagerTest_testGetDeviceInfoSuccess : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testGetDeviceInfoSuccess() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 21, "testGetDeviceInfoSuccess" ) {}
 void runTest() { suite_DeviceManagerTest.testGetDeviceInfoSuccess(); }
} testDescription_suite_DeviceManagerTest_testGetDeviceInfoSuccess;

static class TestDescription_suite_DeviceManagerTest_testGetDeviceInfoFails : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testGetDeviceInfoFails() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 31, "testGetDeviceInfoFails" ) {}
 void runTest() { suite_DeviceManagerTest.testGetDeviceInfoFails(); }
} testDescription_suite_DeviceManagerTest_testGetDeviceInfoFails;

static class TestDescription_suite_DeviceManagerTest_testSetDeviceStatusSuccess : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testSetDeviceStatusSuccess() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 38, "testSetDeviceStatusSuccess" ) {}
 void runTest() { suite_DeviceManagerTest.testSetDeviceStatusSuccess(); }
} testDescription_suite_DeviceManagerTest_testSetDeviceStatusSuccess;

static class TestDescription_suite_DeviceManagerTest_testSetDeviceStatusFailsOnMissingDevice : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testSetDeviceStatusFailsOnMissingDevice() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 46, "testSetDeviceStatusFailsOnMissingDevice" ) {}
 void runTest() { suite_DeviceManagerTest.testSetDeviceStatusFailsOnMissingDevice(); }
} testDescription_suite_DeviceManagerTest_testSetDeviceStatusFailsOnMissingDevice;

static class TestDescription_suite_DeviceManagerTest_testListDevices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testListDevices() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 52, "testListDevices" ) {}
 void runTest() { suite_DeviceManagerTest.testListDevices(); }
} testDescription_suite_DeviceManagerTest_testListDevices;

static class TestDescription_suite_DeviceManagerTest_testDeviceExists : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testDeviceExists() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 62, "testDeviceExists" ) {}
 void runTest() { suite_DeviceManagerTest.testDeviceExists(); }
} testDescription_suite_DeviceManagerTest_testDeviceExists;

static class TestDescription_suite_DeviceManagerTest_testSetInternalDeviceStateValid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testSetInternalDeviceStateValid() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 71, "testSetInternalDeviceStateValid" ) {}
 void runTest() { suite_DeviceManagerTest.testSetInternalDeviceStateValid(); }
} testDescription_suite_DeviceManagerTest_testSetInternalDeviceStateValid;

static class TestDescription_suite_DeviceManagerTest_testSetInternalDeviceStateInvalid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testSetInternalDeviceStateInvalid() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 79, "testSetInternalDeviceStateInvalid" ) {}
 void runTest() { suite_DeviceManagerTest.testSetInternalDeviceStateInvalid(); }
} testDescription_suite_DeviceManagerTest_testSetInternalDeviceStateInvalid;

static class TestDescription_suite_DeviceManagerTest_testSetInternalDeviceStateMissingDevice : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DeviceManagerTest_testSetInternalDeviceStateMissingDevice() : CxxTest::RealTestDescription( Tests_DeviceManagerTest, suiteDescription_DeviceManagerTest, 87, "testSetInternalDeviceStateMissingDevice" ) {}
 void runTest() { suite_DeviceManagerTest.testSetInternalDeviceStateMissingDevice(); }
} testDescription_suite_DeviceManagerTest_testSetInternalDeviceStateMissingDevice;

#include "/mnt/c/STUDY/Device_Fleet_Management_Service/tests/ActionManagerTest.h"

static ActionManagerTest suite_ActionManagerTest;

static CxxTest::List Tests_ActionManagerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ActionManagerTest( "/mnt/c/STUDY/Device_Fleet_Management_Service/tests/ActionManagerTest.h", 9, "ActionManagerTest", suite_ActionManagerTest, Tests_ActionManagerTest );

static class TestDescription_suite_ActionManagerTest_testRejectsUnregisteredDevice : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionManagerTest_testRejectsUnregisteredDevice() : CxxTest::RealTestDescription( Tests_ActionManagerTest, suiteDescription_ActionManagerTest, 12, "testRejectsUnregisteredDevice" ) {}
 void runTest() { suite_ActionManagerTest.testRejectsUnregisteredDevice(); }
} testDescription_suite_ActionManagerTest_testRejectsUnregisteredDevice;

static class TestDescription_suite_ActionManagerTest_testRejectsNonIdleDevice : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionManagerTest_testRejectsNonIdleDevice() : CxxTest::RealTestDescription( Tests_ActionManagerTest, suiteDescription_ActionManagerTest, 27, "testRejectsNonIdleDevice" ) {}
 void runTest() { suite_ActionManagerTest.testRejectsNonIdleDevice(); }
} testDescription_suite_ActionManagerTest_testRejectsNonIdleDevice;

static class TestDescription_suite_ActionManagerTest_testAcceptsValidAction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionManagerTest_testAcceptsValidAction() : CxxTest::RealTestDescription( Tests_ActionManagerTest, suiteDescription_ActionManagerTest, 42, "testAcceptsValidAction" ) {}
 void runTest() { suite_ActionManagerTest.testAcceptsValidAction(); }
} testDescription_suite_ActionManagerTest_testAcceptsValidAction;

static class TestDescription_suite_ActionManagerTest_testActionStatusTracking : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionManagerTest_testActionStatusTracking() : CxxTest::RealTestDescription( Tests_ActionManagerTest, suiteDescription_ActionManagerTest, 55, "testActionStatusTracking" ) {}
 void runTest() { suite_ActionManagerTest.testActionStatusTracking(); }
} testDescription_suite_ActionManagerTest_testActionStatusTracking;

static class TestDescription_suite_ActionManagerTest_testWorkerStartsExecution : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionManagerTest_testWorkerStartsExecution() : CxxTest::RealTestDescription( Tests_ActionManagerTest, suiteDescription_ActionManagerTest, 71, "testWorkerStartsExecution" ) {}
 void runTest() { suite_ActionManagerTest.testWorkerStartsExecution(); }
} testDescription_suite_ActionManagerTest_testWorkerStartsExecution;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
