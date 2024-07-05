#include "DeviceDriver.h"
#include "ReadFailException.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

//app이 read할 예정. app 클래스 만들어야함.
int DeviceDriver::read(long address)
{
    int val = m_hardware->read(address); 
   // int val2 = val1;

    for (int i = 1; i < 5; ++i) {
        int tmp = m_hardware->read(address);
        if (tmp != val) {
            throw ReadFailException();
        }
    }
    return val;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}