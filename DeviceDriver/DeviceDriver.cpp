#include "DeviceDriver.h"

#include <iostream>
#include <stdexcept>

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
    // TODO: implement this method properly
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    if ((int)m_hardware->read(address) != 0xFF) throw WriteException("Write Error!");

    m_hardware->write(address, (unsigned char)data);
}