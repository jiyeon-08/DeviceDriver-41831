#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriveKATA/FlashMemoryDevice.h"
#include "../DeviceDriveKATA/DeviceDriver.cpp"

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class CustomException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Custom Exception: Read operation failed";
	}
};


TEST(TestCaseName, ReadFive) {
	FlashMemoryDeviceMock mk;
	DeviceDriver driver(&mk);

	long address = 0x1;
	int expected= 1;

	EXPECT_CALL(mk, read)
		.Times(5)
		.WillRepeatedly(testing::Return(expected));
	EXPECT_EQ(driver.read(address), expected);
}
