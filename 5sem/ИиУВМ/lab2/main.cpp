#include <iostream>
#include <conio.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "my_iso_io.h"

// Поиск вендора/устройства по его коду в файле pci.ids
int setInfoFromFile(std::string path, std::string& vendorName, const std::string& vendorId, std::string& deviceName, const std::string& deviceId, int nubmerOfLine) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Can't open pci file" << std::endl;
        abort();
    }

    std::string line;
    int numberVendorLine = 0;

    int count = 0;

    bool isFindVendorName = false;

    while (std::getline(file, line)) {
        count++;
        if (count < nubmerOfLine) {
            continue;
        }
        if (line.size() >= 4 && line.substr(0, 4) == vendorId && !isFindVendorName) {
            vendorName = line.substr(4);
            isFindVendorName = true;
            numberVendorLine = count;
            continue;
        }

        if (line[0] == '#') {
            continue;
        }

        if (line[0] != '\t' && isFindVendorName) {
            if (deviceName == "")
                deviceName = "N/A";
            break;
        }

        if (isFindVendorName && line.size() >= 5 && line.substr(1, 4) == deviceId) {
            deviceName = line.substr(5);
            break;
        }
    }
    file.close();
    return numberVendorLine;
}

// Класс для хранения информации о PCI устройствах
class Info {
private:
    int bus, slot, function;
    std::string vId, dId, vendor_name, device_name;

public:
    Info(int bus, int slot, int function, std::string vId, std::string dId)
        : bus(bus), slot(slot), function(function), vId(vId), dId(dId), vendor_name("n/a"), device_name("n/a") {}

    // Геттеры и сеттеры для работы с полями
    int getBus() const { return bus; }
    int getSlot() const { return slot; }
    int getFunction() const { return function; }
    std::string getVId() const { return vId; }
    std::string getDId() const { return dId; }
    std::string getVendorName() const { return vendor_name; }
    std::string getDeviceName() const { return device_name; }
    void setVendorName(std::string newVendorName) { vendor_name = newVendorName; }
    void setDeviceName(std::string newDeviceName) { device_name = newDeviceName; }

    // Печать информации в консоль и файл
    void print() {
        std::cout << bus << " " << slot << " " << function << " " << vId << " " << dId << " " << vendor_name << " " << device_name << "\n";
    }

    void printToFile(std::ofstream& outFile) {
        if (outFile.is_open()) {
            outFile << bus << "|" << slot << "|" << function << "|" << vId << "|" << dId << "|" << vendor_name << "|" << device_name << "\n";
        }
        else {
            std::cerr << "File stream is not open.\n";
        }
    }
};

// Чтение данных с порта через драйвер ISA IO
unsigned int read(unsigned int port, HANDLE hDevice) {
    IsaIoRequestRead request;
    request.port = port;
    IsaIoResponse response = { 0 };

    // Выполнение запроса чтения через драйвер
    DeviceIoControl(hDevice, IOCTL_ISA_READ_32, &request, sizeof(request), &response, sizeof(response), NULL, NULL);

    return response.value;  // Возвращаем прочитанные данные
}

// Запись данных на порт через драйвер ISA IO
void write(unsigned int port, unsigned int value, HANDLE hDevice) {
    IsaIoRequestWrite request;
    request.port = port;  
    request.value = value;  

    // Выполнение запроса записи через драйвер
    DeviceIoControl(hDevice, IOCTL_ISA_WRITE_32, &request, sizeof(request), NULL, 0, NULL, NULL);
}

// Формирование адреса для чтения данных из PCI конфигурационного пространства
uint32_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address = (uint32_t)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    return address;  // Возвращаем подготовленный адрес
}

int main() {
    // Открытие файла устройства драйвера ISA IO
    HANDLE hDevice = CreateFileW(L"\\??\\ISA-IO", 
        GENERIC_READ | GENERIC_WRITE, 
        FILE_SHARE_READ, 
        NULL, 
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL);

    std::vector<Info> list;

    // Обход всех возможных PCI устройств
    for (int bus = 0; bus < 256; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            for (int func = 0; func < 8; func++) {
                unsigned int address = pciConfigReadWord(bus, slot, func, 0);  // Адрес регистра PCI конфигурации
                write(0xCF8, address, hDevice);  // Запись адреса в конфигурационный регистр
                unsigned int result = read(0xCFC, hDevice);  // Чтение данных из регистра

                if (result != pow(2, 32) - 1) {  // Проверка на наличие устройства
                    std::stringstream ss;
                    ss << std::hex << result;  // Преобразуем результат в строку
                    std::string hexStr = ss.str();

                    // Добавляем информацию об устройстве в список
                    list.push_back(Info(bus, slot, func, hexStr.substr(4), hexStr.substr(0, 4)));
                }
            }
        }
    }

    // Открытие файла для записи данных о PCI устройствах
    std::ofstream outFile("data.txt");
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << "data.txt" << "\n";
        return 1;
    }
    outFile.clear();

    // Запись информации о каждом устройстве в файл
    for (int i = 0; i < list.size(); i++) {
        std::string vendorName = "N/A";
        std::string deviceName = "N/A";
        setInfoFromFile("pci.ids", vendorName, list[i].getVId(), deviceName, list[i].getDId(), 0);
        list[i].setVendorName(vendorName);
        list[i].setDeviceName(deviceName);
        list[i].print();  // Вывод в консоль
        list[i].printToFile(outFile);  // Запись в файл
    }

    std::cout << "\nPress any button to exit..." << std::endl;
    _getch();
    std::cout << "Bye!" << std::endl;

    return 0;
}