#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriveKATA/FlashMemoryDevice.h"
#include "../DeviceDriveKATA/DeviceDriver.cpp"

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, ReadFive) {
	FlashMemoryDeviceMock mk;
	DeviceDriver driver(&mk);

	long address = 0x1;

	EXPECT_CALL(mk, read)
		.Times(5);
	driver.read(address);
}