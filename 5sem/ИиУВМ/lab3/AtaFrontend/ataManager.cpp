#include "ataManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::vector<DeviceInfo> devices;

const std::vector<DeviceInfo>& getAtaDevices() {
    return devices;
}

bool deserializeAtaInfo() {
    const auto info_path = dumps_path / info_file;

    std::ifstream info(info_path);

    if (info.is_open() == false) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return false;
    }

    info.seekg(0, std::ios::end);

    const auto entries_num = info.tellg() / sizeof(DeviceBaseInformation);
    info.seekg(0, std::ios::beg);

    for (int i = 0; i < entries_num; ++i) {
        DeviceInfo device;
        info.read(reinterpret_cast<char*>(&device.id_result), sizeof(DeviceBaseInformation));

        switch (device.id_result.status)
        {
        case DeviceStatus::Identified: {
            std::stringstream ss;
            ss << dump_prefix << std::hex << static_cast<uint32_t>(device.id_result.bus) << '-' << (uint16_t)device.id_result.position << ".bin";

            const auto dump_path = dumps_path / ss.str();

            std::ifstream dump(dump_path);

            if (dump.is_open() == false) {
                std::cerr << "Ошибка открытия дампа: \"" << dump_path << "\"" << std::endl;
                continue;
            }

            devices.push_back(device);

            auto& vec = devices.back().dump;
            vec.resize(512);

            dump.read(reinterpret_cast<char*>(vec.data()), 512);
            dump.close();

            break;
        }
        default:
            devices.push_back(device);
            break;
        }
    }

    info.close();
}
