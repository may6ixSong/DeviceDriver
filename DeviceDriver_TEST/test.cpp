#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/Application.cpp"
using namespace testing;
using namespace std;

class DeviceDriverMock : public DeviceDriver
{
public:
	MOCK_METHOD(int, read, (long), ());
	MOCK_METHOD(void, write, (long, int), ());
protected:
	FlashMemoryDevice* m_hardware;
};

TEST(ApplicationTest, ReturnPassReadTest) {
	long start_addr = 0x40001000;
	long end_addr = 0x40001003;

	FlashMemoryDevice device;
	DeviceDriverMock mock(&device);
	EXPECT_CALL(mock, read(_))
		.Times(4)
		.WillOnce(Return(int(1)))
		.WillOnce(Return(int(2)))
		.WillOnce(Return(int(3)))
		.WillOnce(Return(int(4)));

	Application app(&mock);
	app.ReadAndPrint(start_addr, end_addr);
}

TEST(ApplicationTest, ReturnPassWriteTest) {
	int value = 0;
	
	FlashMemoryDevice device;
	DeviceDriverMock mock(&device);
	EXPECT_CALL(mock, write(_, _))
		.Times(4);

	Application app(&mock);
	app.WriteAll(value);
}