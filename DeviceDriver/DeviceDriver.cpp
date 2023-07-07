#include "DeviceDriver.h"
#include <iostream>
#include <stdexcept>

class ReadException : public std::exception
{
public:
    explicit  ReadException(char const* _Message)
        : exception(_Message) {}
};

class WriteException : public std::exception
{
public:
    explicit  WriteException(char const* _Message)
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
    if ((int)m_hardware->read(address) != 0xFF) throw WriteException("Write Error!");

    m_hardware->write(address, (unsigned char)data);
}