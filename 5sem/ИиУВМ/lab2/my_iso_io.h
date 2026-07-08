#pragma once

#ifndef NTDDI_VERSION
#include <windows.h>
#endif

#define IOCTL_ISA_READ_32 CTL_CODE(FILE_DEVICE_UNKNOWN, 0xA30B | 0xCB0 | 0xB0BA, METHOD_BUFFERED, GENERIC_READ | GENERIC_WRITE)
#define IOCTL_ISA_WRITE_32 CTL_CODE(FILE_DEVICE_UNKNOWN, 0xDEAD | 0xC00L , METHOD_BUFFERED, GENERIC_READ | GENERIC_WRITE)

struct IsaIoRequestRead {
	unsigned short port;
};

struct IsaIoRequestWrite {
	unsigned short port;
	unsigned int value;
};

struct IsaIoResponse {
	unsigned int value;
};