#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriveKATA/FlashMemoryDevice.h"
#include "../DeviceDriveKATA/ReadFailException.h"
#include "../DeviceDriveKATA/DeviceDriver.cpp"

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
	EXPECT_CALL(mk, read)
		.Times(5)
		.WillRepeatedly(testing::Return(expected));
	EXPECT_EQ(driver.read(address), expected);
}

TEST_F(DeviceDriverFixture, ReadFiveThrow) {
	FlashMemoryDeviceMock mk;
	DeviceDriver driver(&mk);

	long address = 0x1;

	EXPECT_CALL(mk, read)
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(2));

	EXPECT_THROW(driver.read(address), ReadFailException);
}