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

TEST(DeviceDriveTest, ReturnPassReadTest) {
	long address = 0x40001000;
	FlashMemoryMock mock;
	EXPECT_CALL(mock, read(address))
		.Times(5)
		.WillRepeatedly(Return(unsigned char(0x80)));

	DeviceDriver driver(&mock);

	cout << driver.read(address) << endl;
}

TEST(DeviceDriveTest, ReturnErrorReadTest) {
	long address = 0x40001000;
	FlashMemoryMock device;
	EXPECT_CALL(device, read(address))
		.Times(2)
		.WillOnce(Return(unsigned char(0x10)))
		.WillRepeatedly(Return(unsigned char(0x80)));

	DeviceDriver driver(&device);
	EXPECT_THROW(driver.read(address), ReadException);
}
