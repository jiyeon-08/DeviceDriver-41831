#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriveKATA/FlashMemoryDevice.h"
#include "../DeviceDriveKATA/DeviceDriver.cpp"
#include "../DeviceDriveKATA/ReadFailException.h"
#include "../DeviceDriveKATA/WriteFailException.h"

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public testing::Test {
public:
	testing::NiceMock<FlashMemoryDeviceMock> mk;
	testing::NiceMock<DeviceDriver> driver{ &mk }; //Mock Injection
	long address = 0x1;
	int expected = 1;
	int data = 0xDD;
};

TEST_F(DeviceDriverFixture, ReadFive) {
	EXPECT_CALL(mk, read(address))
		.Times(5)
		.WillRepeatedly(testing::Return(expected));
	EXPECT_EQ(driver.read(address), expected);
}

TEST_F(DeviceDriverFixture, ReadFiveThrow) {
	EXPECT_CALL(mk, read(address))
		.Times(5)
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(2));

	EXPECT_THROW(driver.read(address), ReadFailException);
}

TEST_F(DeviceDriverFixture, WriteBeforeRead) {
	EXPECT_CALL(mk, read(address))
		.WillRepeatedly(testing::Return(0xFF));
	driver.write(address, data);
}

TEST_F(DeviceDriverFixture, WriteException) {
	EXPECT_CALL(mk, read(address))
		.WillRepeatedly(testing::Return(data));

	EXPECT_THROW(driver.write(address, data), WriteFailException);
}