#pragma once

#ifndef KERNEL_SPACE
#include <windows.h>
#endif

#define IOCTL_PIO_READ CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2000, METHOD_BUFFERED, GENERIC_READ | GENERIC_WRITE)
#define IOCTL_PIO_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2001, METHOD_BUFFERED, GENERIC_READ | GENERIC_WRITE)

enum IoSize {
	IO_BYTE,
	IO_WORD,
	IO_DWORD,
	IO_QWORD
};

typedef enum IoSize IoSize;

struct PortsIoRequestRead {
	unsigned short port;

	IoSize size;
};

struct PortsIoRequestWrite {
	unsigned short port;
	unsigned int value;

	IoSize size;
};

struct PortsIoResponse {
	unsigned int value;
};

typedef struct PortsIoResponse IoResponse;

static unsigned int PortsIoRead(HANDLE hDevice, unsigned short port, IoSize size) {
	struct PortsIoRequestRead request;
	struct PortsIoResponse response;
	request.port = port;
	request.size = size;

	if (!DeviceIoControl(
		hDevice, IOCTL_PIO_READ,
		&request, sizeof(request),
		&response, sizeof(response),
		NULL, NULL
	)) return 0xFFFFFFFF;

	return response.value;
}

static bool PortsIoWrite(HANDLE hDevice, unsigned short port, unsigned int value, IoSize size) {
	struct PortsIoRequestWrite request;
	request.port = port;
	request.value = value;
	request.size = size;

	return DeviceIoControl(hDevice, IOCTL_PIO_WRITE, &request, sizeof(request), NULL, 0, NULL, NULL);
}