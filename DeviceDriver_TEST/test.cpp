#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"
using namespace testing;
using namespace std;

class FlashMemoryMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST(DeviceDriveTest, ReturnPassWriteTest) {
	long address = 0x40001000;
	int data = 10;
	FlashMemoryMock mock;
	EXPECT_CALL(mock, read(address))
		.WillRepeatedly(Return(unsigned char(0xFF)));

	DeviceDriver driver(&mock);

	driver.write(address, data);
}

TEST(DeviceDriveTest, ReturnErrorWriteTest) {
	long address = 0x40001000;
	int data = 10;
	FlashMemoryMock device;
	EXPECT_CALL(device, read(address))
		.WillRepeatedly(Return(unsigned char(0x80)));
		
	DeviceDriver driver(&device);
	EXPECT_THROW(driver.write(address, data), WriteException);
}