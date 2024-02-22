#include <iostream>
#include <windows.h>

enum Mode {
	WRITE,
	READ
};

class Port {
private:
	HANDLE portHandle;
	LPCTSTR portName;
public:
	Port(LPCTSTR port, Mode mode) : portName(port) {
		if (mode == WRITE) {
			portHandle = CreateFile(portName, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		}
		else if (mode == READ) {
			portHandle = CreateFile(portName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		}
		else

		if (portHandle == INVALID_HANDLE_VALUE) {
			std::wcout << "Failed to open the port " << portName << std::endl;
			exit(-1);
		}
	}

	HANDLE getPortHandle() {
		return portHandle;
	}
	LPCTSTR getportName() {
		return portName;
	}

	void setPortParams() {
		DCB portParams = { 0 };
		portParams.DCBlength = sizeof(portParams);
		if (!GetCommState(portHandle, &portParams)) {
			std::wcout << "Failed to get state for port " << portName << std::endl;
			exit(-1);
		}
		portParams.BaudRate = CBR_9600;		//скорость передачи в бит\с
		portParams.ByteSize = 8;			//размер байта
		portParams.StopBits = ONESTOPBIT;	//количество стоповых битов
		portParams.Parity = NOPARITY;		//использование паритета

		if (!SetCommState(portHandle, &portParams)) {
			std::wcout << "Failed to set state for port " << portName << std::endl;
			exit(-1);
		}
	}

	void readCOM() {
		DWORD size = 0;
		char recievedChar;
		while (true) {
			if (ReadFile(portHandle, &recievedChar, 1, &size, nullptr)) {
				if (size > 0) {
					std::cout << "Recieved char is: " << recievedChar << std::endl;
					break;
				}
				else {
					std::cout << "Nothing to read" << std::endl;
				}
			}
			else {
				std::cout << "Failed to read port" << std::endl;
			}
		}
	}
};

int main() {
	Port port1(L"COM1", WRITE);
	Port port2(L"COM2", READ);

	port1.setPortParams();
	port2.setPortParams();

	char data = 'A';
	DWORD size = sizeof(data);
	DWORD bytesWritten;

	BOOL Ret = WriteFile(port1.getPortHandle(), &data, size, &bytesWritten, NULL);

	std::cout << size << " Bytes in char. " << bytesWritten << " Bytes sended. " << std::endl;

	port2.readCOM();

	return 0;
}