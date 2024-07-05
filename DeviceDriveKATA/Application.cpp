#include <iostream>
#include <vector>
#include "DeviceDriver.h"

using namespace std;

class Application {
	void ReadAndPrint(long startAddr, long endAddr) {
		for (int i = startAddr; i <= endAddr, i++) {
			cout << "address: " << startAddr << " "
				<< "value: " << m_deviceDriver->read(startAddr) << '\n';
		}
	}
	void WriteAll(int value){
		for (int i = 0x1; i < 0x4; i++) {
			m_deviceDriver->write(i, i);
		}
	}
private:
	DeviceDriver* m_deviceDriver;
};