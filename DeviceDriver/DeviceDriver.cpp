#include "DeviceDriver.h"

#include <iostream>
#include <windows.h>
#include <stdexcept>

class ReadException : public std::exception
{
public:
    explicit  ReadException(char const* _Message)
        : exception(_Message) {}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int first_read_data = (int)m_hardware->read(address);
    for(int i = 0; i < 4; i++)
    {
        if(first_read_data != (int)m_hardware->read(address))
        {
            throw ReadException("Read Error!");
        }
        //Sleep(200);
    }

	return first_read_data;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}