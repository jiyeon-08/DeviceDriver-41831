#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

//app�� read�� ����. app Ŭ���� ��������.
int DeviceDriver::read(long address)
{
    int val;
    for (int i = 0; i < 5; i++) {
        val = m_hardware->read(address);
    }
    return val;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}