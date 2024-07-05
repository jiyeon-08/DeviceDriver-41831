#include "DeviceDriver.h"
#include "ReadFailException.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

//app이 read할 예정. app 클래스 만들어야함.
int DeviceDriver::read(long address)
{
    int firstValue = m_hardware->read(address); 

    for (int i = 1; i < RERTY_TEST_COUNT; ++i) {
        int nextValue = m_hardware->read(address);
        if (nextValue != firstValue) {
            throw ReadFailException();
        }
    }
    return firstValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}