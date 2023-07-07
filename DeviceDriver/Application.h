#pragma once
#include "DeviceDriver.h"

class Application
{
public:
    Application(IDriver* driver);
    void ReadAndPrint(long startAddr, long endAddr);
    void WriteAll(int value);

protected:
    IDriver* m_driver;
};