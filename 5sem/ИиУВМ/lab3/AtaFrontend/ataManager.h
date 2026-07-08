#include "ataData.h"

#include <vector>

static const char info_file[] = "ata_devices.info";
static const char dump_prefix[] = "dump-0x";
static std::filesystem::path dumps_path = "D:/BSUIR/bsuirLabs/5sem/IiUVM/lab3/dumps";

struct DeviceInfo {
    DeviceBaseInformation id_result;
    std::vector<uint8_t> dump;
};

const std::vector<DeviceInfo>& getAtaDevices();

bool deserializeAtaInfo();
