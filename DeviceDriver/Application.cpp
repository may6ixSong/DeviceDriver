#include "Application.h"
#include <iostream>
#include <vector>

Application::Application(DeviceDriver* driver) : m_driver(driver)
{}

void Application::ReadAndPrint(long startaddr, long endAddr)
{
   for(int i = 0; i < endAddr - startaddr; i++)
   {
   		long addr = startaddr + (0x1 * i);
        std::cout << m_driver->read(addr) << " ";
   }
   std::cout << "\n";
}

void Application::WriteAll(int value)
{
    long addr = 0x0;
    for(int i = 0; i < 4; i++)
    {
        addr += (0x1 * i);
        m_driver->write(addr, value);
    }
}