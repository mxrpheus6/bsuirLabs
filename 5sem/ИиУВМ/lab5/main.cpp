#include <windows.h>
#include <dbt.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <locale>
#include <string>
#include <initguid.h>
#include <usbiodef.h>

#pragma comment(lib, "setupapi.lib")

std::wstring GetDevicePropertyString(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData, DWORD property) {
    WCHAR buffer[256];
    DWORD size;
    if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, property, nullptr,
        (PBYTE)buffer, sizeof(buffer), &size)) {
        return buffer;
    }
    return L"N/A";
}

DWORD GetDevicePropertyDWORD(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData, DWORD property) {
    DWORD data;
    DWORD size;
    if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, property, nullptr,
        (PBYTE)&data, sizeof(data), &size)) {
        return data;
    }
    return 0;
}

void parseVIDPID(const std::wstring& devicePath, std::wstring& vid, std::wstring& pid) {
    size_t vidPos = devicePath.find(L"VID_");
    size_t pidPos = devicePath.find(L"PID_");

    if (vidPos != std::wstring::npos && pidPos != std::wstring::npos) {
        vid = devicePath.substr(vidPos + 4, 4);
        pid = devicePath.substr(pidPos + 4, 4);
    }

    if (vid.size() == 0) {
        vid = L"N/A";
    }
    if (pid.size() == 0) {
        pid = L"N/A";
    }
}

void parseUsbIdsOpt(const std::wstring& vid, const std::wstring& pid, std::wstring& vidResult, std::wstring& pidResult) {
    std::wifstream usbIdsFile(L"usb.ids");
    if (!usbIdsFile.is_open()) {
        vidResult = L"N/A";
        pidResult = L"N/A";
        return;
    }

    if ((pid.size() == 0 && vid.size() == 0) || (vid == L"N/A" && pid == L"N/A")) {
        vidResult = L"N/A";
        pidResult = L"N/A";
        return;
    }

    std::wstring line;
    bool vidFound = false;

    while (std::getline(usbIdsFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (!vidFound && (line[0] == '\t' || line[0] == ' ')) {
            continue;
        }

        if (vidFound && line[0] != '\t') {
            pidResult = L"N/A";
            break;
        }

        size_t vidPos = line.find(vid);
        if (vidPos != std::wstring::npos) {
            if (line[0] == ' ' || line[0] == '\t') {
                continue;
            }
            vidFound = true;
            vidResult = line.substr(6);
            continue;
        }

        if (vidFound) {
            size_t pidPos = line.find(pid);
            if (pidPos != std::wstring::npos) {
                pidResult = line.substr(7);
                break;
            }
        }
    }

    if (!vidFound) {
        vidResult = L"N/A";
    }

    usbIdsFile.close();
}

void getDeviceAdditionalInfo(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData,
    std::wstring& classResult, std::wstring& subclassResult, std::wstring& protocolResult) {
    DWORD dataType, requiredSize;
    WCHAR buffer[256];

    if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_CLASS, &dataType,
        (PBYTE)buffer, sizeof(buffer), &requiredSize)) {
        classResult = buffer;
    }
    else {
        classResult = L"Unknown";
    }

    if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_CLASSGUID, &dataType,
        (PBYTE)buffer, sizeof(buffer), &requiredSize)) {
        subclassResult = buffer;
    }
    else {
        subclassResult = L"Unknown";
    }

    if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_SERVICE, &dataType,
        (PBYTE)buffer, sizeof(buffer), &requiredSize)) {
        protocolResult = buffer;
    }
    else {
        protocolResult = L"Unknown";
    }
}

bool EjectDevice(HDEVINFO deviceInfo, SP_DEVINFO_DATA& deviceInfoData) {
    DEVINST devInst = deviceInfoData.DevInst;
    CONFIGRET cr = CM_Request_Device_Eject(devInst, nullptr, 0, 0, 0);
    if (cr == CR_SUCCESS) {
        std::cout << "Device was safely removed." << std::endl;
        return true;
    }
    else {
        std::cerr << "Safe remove error." << std::endl;
        return false;
    }
}

void processUsbDevices(std::wofstream& outFile) {
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(nullptr, L"USB", nullptr, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get device information set." << std::endl;
        return;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        std::wstring vid, pid, classResult, subclassResult, protocolResult;

        WCHAR deviceID[256];
        if (SetupDiGetDeviceInstanceId(deviceInfoSet, &deviceInfoData, deviceID, sizeof(deviceID) / sizeof(WCHAR), nullptr)) {
            parseVIDPID(deviceID, vid, pid);
            if (vid != L"N/A" && pid != L"N/A") {
                std::transform(vid.begin(), vid.end(), vid.begin(), towlower);
                std::transform(pid.begin(), pid.end(), pid.begin(), towlower);
            }
            std::wstring vidResult, pidResult;
            parseUsbIdsOpt(vid, pid, vidResult, pidResult);

            getDeviceAdditionalInfo(deviceInfoSet, deviceInfoData, classResult, subclassResult, protocolResult);

            std::wstring deviceDescription = GetDevicePropertyString(deviceInfoSet, deviceInfoData, SPDRP_DEVICEDESC);
            std::wstring hardwareID = GetDevicePropertyString(deviceInfoSet, deviceInfoData, SPDRP_HARDWAREID);
            std::wstring compatibleIDs = GetDevicePropertyString(deviceInfoSet, deviceInfoData, SPDRP_COMPATIBLEIDS);
            DWORD configFlags = GetDevicePropertyDWORD(deviceInfoSet, deviceInfoData, SPDRP_CONFIGFLAGS);
            std::wstring manufacturer = GetDevicePropertyString(deviceInfoSet, deviceInfoData, SPDRP_MFG);
            std::wstring friendlyName = GetDevicePropertyString(deviceInfoSet, deviceInfoData, SPDRP_FRIENDLYNAME);
            std::wstring deviceLocation = GetDevicePropertyString(deviceInfoSet, deviceInfoData, SPDRP_LOCATION_INFORMATION);

            DWORD busNumber = 0;
            DWORD deviceNumber = 0;
            std::wstring busNumberStr;
            std::wstring deviceNumberStr;
            bool isBusNumberExists = false;
            bool isDeviceNumberExists = false;

            if (!deviceLocation.empty()) {
                std::wstringstream ss(deviceLocation);
                std::wstring token;
                while (std::getline(ss, token, L',')) {
                    if (token.find(L"Hub") != std::wstring::npos) {
                        busNumber = std::stoi(token.substr(16));
                        isBusNumberExists = true;
                    }
                    if (token.find(L"Port") != std::wstring::npos) {
                        deviceNumber = std::stoi(token.substr(6, 11));
                        isDeviceNumberExists = true;
                    }
                }
            }

            std::wstringstream wss;
            if (isBusNumberExists) {
                wss << busNumber;
                busNumberStr = wss.str();
            }
            else {
                busNumberStr = L"N/A";
            }
            if (isDeviceNumberExists) {
                wss << deviceNumber;
                deviceNumberStr = wss.str();
            }
            else {
                deviceNumberStr = L"N/A";
            }

            outFile << L"Bus Number:" << busNumberStr << std::endl;
            outFile << L"Device Number:" << deviceNumberStr << std::endl;
            outFile << L"Vendor ID:" << vid << std::endl;
            outFile << L"Product ID:" << pid << std::endl;
            outFile << L"Vendor Name:" << vidResult << std::endl;
            outFile << L"Product Name:" << pidResult << std::endl;
            outFile << L"Friendly Name:" << friendlyName << std::endl;
            outFile << L"Manufacturer:" << manufacturer << std::endl;
            outFile << L"Device Description:" << deviceDescription << std::endl;
            outFile << L"Device Class:" << classResult << std::endl;
            outFile << L"Device Subclass:" << subclassResult << std::endl;
            outFile << L"Device Protocol:" << protocolResult << std::endl;
            outFile << L"Hardware ID:" << hardwareID << std::endl;
            outFile << L"Compatible IDs:" << compatibleIDs << std::endl;
            outFile << L"Config Flags:" << configFlags << std::endl << std::endl;
        }
    }
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DEVICECHANGE:
        if (wParam == DBT_DEVICEARRIVAL) {
            std::wofstream outFile("usb_devices.txt");
            std::wofstream notifyFile("notify.txt");
            notifyFile << "New USB-device was connected." << std::endl;
            processUsbDevices(outFile);
            outFile.close();
            notifyFile.close();
        }
        else if (wParam == DBT_DEVICEREMOVECOMPLETE) {
            std::wofstream outFile("usb_devices.txt");
            std::wofstream notifyFile("notify.txt");
            notifyFile << "USB-device was removed." << std::endl;
            processUsbDevices(outFile);
            outFile.close();
            notifyFile.close();
        }
        else if (wParam == DBT_DEVICEQUERYREMOVE) {
            DEV_BROADCAST_HDR* pHdr = (DEV_BROADCAST_HDR*)lParam;

            if (pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
                DEV_BROADCAST_DEVICEINTERFACE* pDevIface = (DEV_BROADCAST_DEVICEINTERFACE*)pHdr;
                std::wofstream outFile("usb_devices.txt");
                std::wofstream notifyFile("notify.txt");
                notifyFile << L"Safe remove request for device: " << pDevIface->dbcc_name << std::endl;
                processUsbDevices(outFile);
                outFile.close();
                notifyFile.close();
            }

            return BROADCAST_QUERY_DENY;
        }
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //system("chcp 65001");
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale());

    // Создание фиктивного окна для регистрации уведомлений, без отображения
    const wchar_t* className = L"USBMonitorClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;

    RegisterClass(&wc);

    // Окно не будет отображаться
    HWND hwnd = CreateWindowEx(0, className, L"USB Monitor", 0, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) {
        std::cerr << "Ошибка при создании окна." << std::endl;
        return 1;
    }

    // Регистрация уведомлений для USB-устройств
    DEV_BROADCAST_DEVICEINTERFACE dbdi = {};
    dbdi.dbcc_size = sizeof(dbdi);
    dbdi.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    dbdi.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
    HDEVNOTIFY hDevNotify = RegisterDeviceNotification(hwnd, &dbdi, DEVICE_NOTIFY_WINDOW_HANDLE);
    if (!hDevNotify) {
        std::cerr << "Ошибка регистрации уведомлений." << std::endl;
        return 1;
    }

    // Получение информации о подключенных устройствах
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(nullptr, L"USB", nullptr, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Не удалось получить информацию о устройствах." << std::endl;
        return 1;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    // Запись информации о устройствах в файл
    std::wofstream outFile("usb_devices.txt");
    processUsbDevices(outFile);
    outFile.close();

    SetupDiDestroyDeviceInfoList(deviceInfoSet);

    // Цикл обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}