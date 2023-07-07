#pragma once
#include "FlashMemoryDevice.h"
#define interface struct

interface IDriver
{
    virtual int read(long address) = 0;
    virtual void write(long address, int data) = 0;
};

class DeviceDriver : public IDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};