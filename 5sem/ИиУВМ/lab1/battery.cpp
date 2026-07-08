#include "Battery.h"
#include <sstream>
#include <fstream>
#include <iomanip>

Battery::Battery() {
	SYSTEM_POWER_STATUS sps;
	GetSystemPowerStatus(&sps);

    this->energyType = getEnergyType(sps);
    this->batteryType = getBatteryType();
    this->percent = getPercent(sps);
    this->energySavingMode = getEnergySavingMode(sps);
    this->timeRemaining = getTimeRemaining(sps);
    this->timeAfterChargingOff = 0;
    processTimeAfterChargingOff(sps);
}

void Battery::setBatteryInfo() {
    SYSTEM_POWER_STATUS sps;
    GetSystemPowerStatus(&sps);

    this->energyType = getEnergyType(sps);
    this->percent = getPercent(sps);
    this->energySavingMode = getEnergySavingMode(sps);
    this->timeRemaining = getTimeRemaining(sps);
    processTimeAfterChargingOff(sps);
}

void Battery::printBatteryInfo() {
    std::cout << "Тип энергопитания: " << this->energyType << std::endl;
    std::cout << "Тип батареи: " << this->batteryType << std::endl;
    std::cout << "Уровень заряда батареи: " << static_cast<int>(this->percent) << "%" << std::endl;
    std::cout << "Режим энергосбережения: " << this->energySavingMode << std::endl;
    std::cout << "Оставшееся время работы: " << this->timeRemaining << std::endl;
    std::cout << "Время с момента отключения зарядки: ";
    printTimeAfterChargingOff();
}

std::string Battery::getBatteryType() {
    HDEVINFO DeviceInfoSet;
    // получаем класс устройств заданный
    DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    SP_DEVICE_INTERFACE_DATA DeviceInterfaceData = { 0 };
    ZeroMemory(&DeviceInterfaceData, sizeof(SP_DEVINFO_DATA));
    DeviceInterfaceData.cbSize = sizeof(SP_DEVINFO_DATA);

    // заполняем инфой об интерфейсе устройства структуру и определяем размер структуры
    SetupDiEnumDeviceInterfaces(DeviceInfoSet, NULL, &GUID_DEVCLASS_BATTERY, 0, &DeviceInterfaceData);
    DWORD cbRequired = 0;
    SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, NULL, NULL, &cbRequired, NULL);
    PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired);
    pdidd->cbSize = sizeof(*pdidd);

    SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, pdidd, cbRequired, &cbRequired, NULL);
    // получаем дескриптор устройства
    HANDLE hBattery = CreateFile(pdidd->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // получаем тег батареи
    BATTERY_QUERY_INFORMATION BatteryQueryInformation = { 0 };
    DWORD bytesWait = 0;
    DWORD bytesReturned = 0;
    DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_TAG, &bytesWait, sizeof(bytesWait), &BatteryQueryInformation.BatteryTag,
        sizeof(BatteryQueryInformation.BatteryTag), &bytesReturned, NULL) && BatteryQueryInformation.BatteryTag;

    BATTERY_INFORMATION BatteryInfo = { 0 };
    BatteryQueryInformation.InformationLevel = BatteryInformation;

    DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_INFORMATION, &BatteryQueryInformation, sizeof(BatteryQueryInformation),
        &BatteryInfo, sizeof(BatteryInfo), &bytesReturned, NULL);

    std::string result;

    for (int b = 0; b < 4; ++b) {
        result += BatteryInfo.Chemistry[b];
    }

    LocalFree(pdidd);
    SetupDiDestroyDeviceInfoList(DeviceInfoSet);

    return result;
}

std::string Battery::getEnergyType(SYSTEM_POWER_STATUS sps) {
    switch (sps.ACLineStatus) {
    case 0:
        this->isCharging = false;
        return "от батареи";
    case 1:
        this->isCharging = true;
        return "от сети";
    default:
        return "неизвестно";
    }
}

void Battery::processTimeAfterChargingOff(SYSTEM_POWER_STATUS sps) {
    switch (sps.ACLineStatus) {
    case 0:
        this->timeAfterChargingOff++;
        break;
    default:
        this->timeAfterChargingOff = 0;
    }
}

uint8_t Battery::getPercent(SYSTEM_POWER_STATUS sps) {
    switch (sps.BatteryLifePercent) {
    case 255:
        return 255;
    default:
        return static_cast<uint8_t>(sps.BatteryLifePercent);
    }
}

std::string Battery::getEnergySavingMode(SYSTEM_POWER_STATUS sps) {
    switch (sps.SystemStatusFlag) {
    case 0:
        return "выключен";
    case 1:
        return "включен";
    default:
        return "N/A";
    }
}

std::string Battery::getTimeRemaining(SYSTEM_POWER_STATUS sps) {
    if (sps.BatteryLifeTime != (DWORD)-1) {
        int hours = sps.BatteryLifeTime / 3600;
        int minutes = (sps.BatteryLifeTime % 3600) / 60;

        std::string hoursString = std::to_string(hours);
        std::string minutesString = std::to_string(minutes);
        
        return hoursString + " часов " + minutesString + " минут";
    }
    else {
        return "N/A";
    }
}

void Battery::printTimeAfterChargingOff() {
    if (this->isCharging) {
        std::cout << "N/A" << std::endl;
        return;
    }
    uint64_t hours = this->timeAfterChargingOff / 3600;
    uint64_t minutes = (this->timeAfterChargingOff % 3600) / 60;
    uint64_t seconds = this->timeAfterChargingOff % 60;

    std::cout << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds << std::endl;
}

void Battery::writeBatteryInfoToFile(const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Ошибка при открытии файла для записи: " << filename << std::endl;
        return;
    }

    outFile << this->energyType << std::endl;
    outFile << this->batteryType << std::endl;
    outFile << static_cast<int>(this->percent) << "%" << std::endl;
    outFile << this->energySavingMode << std::endl;
    outFile << this->timeRemaining << std::endl;
    outFile << (isCharging ? "N/A" : std::to_string(this->timeAfterChargingOff));

    outFile.close();
}
