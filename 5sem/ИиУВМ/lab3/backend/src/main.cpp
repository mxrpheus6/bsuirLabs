#include "ataData.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>

#include "IO.h"

const char info_file[] = "ata_devices.info";
const char dump_prefix[] = "dump-0x";
std::filesystem::path dumps_path = "./dumps/";

void convertStirngToBE(uint16_t* buffer, uint32_t len) {
    for (int i = 0; i < len; ++i) {
        buffer[i] = (buffer[i] >> 8) | (buffer[i] << 8);
    }
}

DeviceStatus deviceIdentification(HANDLE hDevice, uint16_t base, uint16_t drive, uint16_t buffer[256]) {
    const uint8_t drive_select = (drive == 0) ? DEVICE_MASTER : DEVICE_SLAVE;

    PortsIoWrite(hDevice, base + SELECT_REG, drive_select, IO_BYTE);
    PortsIoWrite(hDevice, base + SECTOR_COUNT_REG, 0x0, IO_BYTE);
    PortsIoWrite(hDevice, base + LBA_LOW_REG, 0x0, IO_WORD);
    PortsIoWrite(hDevice, base + LBA_MID_REG, 0x0, IO_WORD);
    PortsIoWrite(hDevice, base + LBA_HIG_REG, 0x0, IO_WORD);
    //init
    PortsIoWrite(hDevice, base + COMMAND_REG, 0xEC, IO_BYTE);

    auto status = PortsIoRead(hDevice, base + STATUS_REG, IO_BYTE);
    if (status == 0) {
        return DeviceStatus::NotConnected; 
    }

    // BSY busy, Ready 
    while ((status & 0x80) != 0 && !(status & 0x40)) {
        status = PortsIoRead(hDevice, base + STATUS_REG, IO_BYTE);
    }
    // ERR
    if (status & 1) { 
        const auto lba_mid = PortsIoRead(hDevice, base + LBA_MID_REG, IO_BYTE);
        const auto lba_hig = PortsIoRead(hDevice, base + LBA_HIG_REG, IO_BYTE);

        if (lba_mid != 0 && lba_hig != 0) {
            buffer[0] = lba_mid;
            buffer[1] = lba_hig;
            return DeviceStatus::NotPATA; 
        }
        else {
            buffer[0] = PortsIoRead(hDevice, base + ERROR_REG, IO_BYTE);
            return DeviceStatus::Error;
        }
    }

    //buffer[1] = 0;
    for (int i = 0; i < 256; ++i) {
        buffer[i] = static_cast<uint16_t>(PortsIoRead(hDevice, base + DATA_REG, IO_WORD));
    }

    convertStirngToBE(&buffer[offsetof(PataDevicesInfo, SerialNumber) / 2], 10);
    convertStirngToBE(&buffer[offsetof(PataDevicesInfo, ModelNumber) / 2], 20);
    convertStirngToBE(&buffer[offsetof(PataDevicesInfo, FirmwareRevision) / 2], 4);

    return (buffer[1] == 0) ? DeviceStatus::NotConnected : DeviceStatus::Identified;
}

void dumpDataToFile(uint16_t deviceId, uint16_t driveNum, const uint16_t dataBuffer[256]) {
    std::stringstream ss;
    ss << dump_prefix << std::hex << deviceId << '-' << driveNum << ".bin";

    const auto path = dumps_path / ss.str();
    std::ofstream file(path, std::ios_base::binary);

    file.write(reinterpret_cast<const char*>(dataBuffer), 512);
    file.close();
}

void saveResultsToFile(const std::vector<DeviceBaseInformation>& results) {
    const auto path = dumps_path / info_file;

    std::ofstream out(path, std::ios_base::binary);

    out.write(reinterpret_cast<const char*>(results.data()), results.size() * sizeof(DeviceBaseInformation));
    out.close();
}

DeviceInterface getInterface(uint8_t mid, uint8_t hig) {
    if (mid == 0x14 && hig == 0xEB) return DeviceInterface::PATAPI;
    if (mid == 0x69 && hig == 0x96) return DeviceInterface::SATAPI;
    if (mid == 0x3C && hig == 0xC3) return DeviceInterface::SATA;
    if (mid == 0x00 && hig == 0x00) return DeviceInterface::PATA;

    std::cerr << "Unknown device: " << std::hex << mid << ' ' << std::hex << hig << std::endl;
    return DeviceInterface::UNKNOWN;
}

std::string getInterfaceNameByValue(DeviceInterface interfaceName) {
    switch (interfaceName) {
    case DeviceInterface::PATA: return "PATA";
    case DeviceInterface::SATA: return "SATA";
    case DeviceInterface::PATAPI: return "PATAPI";
    case DeviceInterface::SATAPI: return "SATAPI";
    default: return "UNKNOWN";
    }
}

int main() {
    HANDLE hDevice = CreateFileW(
        L"\\??\\ISA-IO",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open driver handle: code: " << GetLastError() << std::endl;
        return -1;
    }

    uint16_t buffer[256] = { 0 };
    std::vector<DeviceBaseInformation> results;

    for (auto bus : buses) {
        std::cout << bus.first << ": " << std::hex << bus.second << "h" << " checked" << std::endl;
        unsigned int temp = PortsIoRead(hDevice, bus.second + STATUS_REG, IO_BYTE);

        if ((temp & FLOATING_BUS) != FLOATING_BUS) {
            for (auto i = 0; i < 2; ++i) {
                DeviceBaseInformation result;
                result.bus = static_cast<AtaBus>(bus.second);
                result.position = static_cast<DeviceOnBusType>(i);

                DeviceStatus status = deviceIdentification(hDevice, bus.second, i, buffer);

                result.status = status;

                switch (status) {
                case DeviceStatus::Identified: {
                    result.interf = DeviceInterface::PATA;
                    dumpDataToFile(bus.second, i, buffer);
                    break;
                }
                case DeviceStatus::NotPATA: {
                    result.interf = getInterface((uint8_t)buffer[0], (uint8_t)buffer[1]);
                    break;
                }
                case DeviceStatus::Error: {
                    result.interf = static_cast<DeviceInterface>(buffer[0]);
                    break;
                }
                case DeviceStatus::NotConnected: break;
                default:
                    break;
                }

                results.push_back(result);
            }
        }
        else {
            printf("Bus Floating\n");

            DeviceBaseInformation result;
            result.bus = static_cast<AtaBus>(bus.second);
            result.position = DeviceOnBusType::Undefined;
            result.status = DeviceStatus::Floating;

            results.push_back(result);
        }
    }

    saveResultsToFile(results);

    CloseHandle(hDevice);

    std::cout << std::endl << "Press Enter to exit...";
    std::cin.get();
    return 0;
}