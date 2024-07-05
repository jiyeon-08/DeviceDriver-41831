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
	FlashMemoryDeviceMock mk;
	DeviceDriver driver{ &mk }; //Mock Injection
	long address = 0x1;
	int expected = 1;
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
	driver.write(address, 0x72);
}

TEST_F(DeviceDriverFixture, WriteException) {
	EXPECT_CALL(mk, read(address))
		.WillRepeatedly(testing::Return(0xFA));

	EXPECT_THROW(driver.write(address, 0xFA), WriteFailException);
}