#include "DeviceDriver.h"
#include "ReadFailException.h"
#include "WriteFailException.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

//app�� read�� ����. app Ŭ���� ��������.
int DeviceDriver::read(long address)
{
    int firstValue = m_hardware->read(address); 

    for (int i = 1; i < 5; ++i) {
        int nextValue = m_hardware->read(address);
        if (nextValue != firstValue) {
            throw ReadFailException();
        }
    }
    return firstValue;
}

void DeviceDriver::write(long address, int data)
{
    int value = (int)(DeviceDriver::read(address));
    if (value != BLANK) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);
}
