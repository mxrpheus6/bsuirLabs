#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <Windows.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>

#pragma comment(lib, "setupapi.lib")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    centralWidget(new QWidget(this)),
    deviceComboBox(new QComboBox(this)),
    safeEjectButton(new QPushButton("Safe remove", this)),
    refreshButton(new QPushButton("Update devices list", this)),
    busNumberLabel(new QLabel(this)),
    deviceNumberLabel(new QLabel(this)),
    vendorIDLabel(new QLabel(this)),
    productIDLabel(new QLabel(this)),
    vendorNameLabel(new QLabel(this)),
    productNameLabel(new QLabel(this)),
    friendlyNameLabel(new QLabel(this)),
    manufacturerLabel(new QLabel(this)),
    deviceDescriptionLabel(new QLabel(this)),
    deviceClassLabel(new QLabel(this)),
    deviceSubclassLabel(new QLabel(this)),
    deviceProtocolLabel(new QLabel(this)),
    hardwareIDLabel(new QLabel(this)),
    compatibleIDsLabel(new QLabel(this)),
    configFlagsLabel(new QLabel(this)),
    fileCheckTimer(new QTimer(this))
{
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    mainLayout->addWidget(deviceComboBox);
    mainLayout->addWidget(safeEjectButton);  // Добавляем кнопку безопасного отключения
    mainLayout->addWidget(refreshButton);   // Добавляем кнопку обновления устройств

    QVBoxLayout *detailsLayout = new QVBoxLayout();
    detailsLayout->addWidget(busNumberLabel);
    detailsLayout->addWidget(deviceNumberLabel);
    detailsLayout->addWidget(vendorIDLabel);
    detailsLayout->addWidget(productIDLabel);
    detailsLayout->addWidget(vendorNameLabel);
    detailsLayout->addWidget(productNameLabel);
    detailsLayout->addWidget(friendlyNameLabel);
    detailsLayout->addWidget(manufacturerLabel);
    detailsLayout->addWidget(deviceDescriptionLabel);
    detailsLayout->addWidget(deviceClassLabel);
    detailsLayout->addWidget(deviceSubclassLabel);
    detailsLayout->addWidget(deviceProtocolLabel);
    detailsLayout->addWidget(hardwareIDLabel);
    detailsLayout->addWidget(compatibleIDsLabel);
    detailsLayout->addWidget(configFlagsLabel);

    mainLayout->addLayout(detailsLayout);

    loadDeviceData();  // Первоначальная загрузка устройств

    for (const auto &device : devices) {
        deviceComboBox->addItem(device.busNumber + "-" + device.deviceNumber + " " + device.vendorName + " --- " + device.deviceDescription);
    }

    deviceComboBox->setPlaceholderText("Choose");
    deviceComboBox->setCurrentIndex(-1);

    safeEjectButton->setEnabled(false);

    connect(fileCheckTimer, &QTimer::timeout, this, &MainWindow::checkNotifyFile);
    fileCheckTimer->start(1000);

    connect(deviceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_deviceComboBox_currentIndexChanged(int)));
    connect(safeEjectButton, &QPushButton::clicked, this, &MainWindow::onSafeEjectButtonClicked);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshButtonClicked); // Подключаем слот для кнопки обновления
}

MainWindow::~MainWindow()
{
    // Деструктор
}

void MainWindow::checkNotifyFile() {
    QFile notifyFile("../notify.txt");

    if (notifyFile.exists()) {
        // Читаем содержимое файла
        if (notifyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&notifyFile);
            QString fileContent = in.readAll();
            notifyFile.close();

            // Показать информационное сообщение
            QMessageBox::information(this, "Info", fileContent);

            // Удаляем файл после показа сообщения
            notifyFile.remove();
        }
    }
}

void MainWindow::loadDeviceData() {
    devices.clear();  // Очистить список устройств перед загрузкой новых данных
    QFile file("../usb_devices.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file!";
        return;
    }

    QTextStream in(&file);
    Device currentDevice;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) continue;

        if (line.startsWith("Bus Number:")) {
            if (!currentDevice.busNumber.isEmpty()) {
                devices.append(currentDevice);
            }
            currentDevice = Device();
            currentDevice.busNumber = line.mid(11);
        } else if (line.startsWith("Device Number:")) {
            currentDevice.deviceNumber = line.mid(14);
        } else if (line.startsWith("Vendor ID:")) {
            currentDevice.vendorID = line.mid(10);
        } else if (line.startsWith("Product ID:")) {
            currentDevice.productID = line.mid(11);
        } else if (line.startsWith("Vendor Name:")) {
            currentDevice.vendorName = line.mid(12);
        } else if (line.startsWith("Product Name:")) {
            currentDevice.productName = line.mid(13);
        } else if (line.startsWith("Friendly Name:")) {
            currentDevice.friendlyName = line.mid(14);
        } else if (line.startsWith("Manufacturer:")) {
            currentDevice.manufacturer = line.mid(13);
        } else if (line.startsWith("Device Description:")) {
            currentDevice.deviceDescription = line.mid(19);
        } else if (line.startsWith("Device Class:")) {
            currentDevice.deviceClass = line.mid(13);
        } else if (line.startsWith("Device Subclass:")) {
            currentDevice.deviceSubclass = line.mid(16);
        } else if (line.startsWith("Device Protocol:")) {
            currentDevice.deviceProtocol = line.mid(16);
        } else if (line.startsWith("Hardware ID:")) {
            currentDevice.hardwareID = line.mid(12);
        } else if (line.startsWith("Compatible IDs:")) {
            currentDevice.compatibleIDs = line.mid(15);
        } else if (line.startsWith("Config Flags:")) {
            currentDevice.configFlags = line.mid(13);
        }
    }

    if (!currentDevice.busNumber.isEmpty()) {
        devices.append(currentDevice);
    }

    file.close();
}

void MainWindow::updateDeviceDetails(int index) {
    if (index < 0 || index >= devices.size()) return;

    const Device &device = devices[index];
    busNumberLabel->setText("Bus Number: " + device.busNumber);
    deviceNumberLabel->setText("Device Number: " + device.deviceNumber);
    vendorIDLabel->setText("Vendor ID: " + device.vendorID);
    productIDLabel->setText("Product ID: " + device.productID);
    vendorNameLabel->setText("Vendor Name: " + device.vendorName);
    productNameLabel->setText("Product Name: " + device.productName);
    friendlyNameLabel->setText("Friendly Name: " + device.friendlyName);
    manufacturerLabel->setText("Manufacturer: " + device.manufacturer);
    deviceDescriptionLabel->setText("Device Description: " + device.deviceDescription);
    deviceClassLabel->setText("Device Class: " + device.deviceClass);
    deviceSubclassLabel->setText("Device Subclass: " + device.deviceSubclass);
    deviceProtocolLabel->setText("Device Protocol: " + device.deviceProtocol);
    hardwareIDLabel->setText("Hardware ID: " + device.hardwareID);
    compatibleIDsLabel->setText("Compatible IDs: " + device.compatibleIDs);
    configFlagsLabel->setText("Config Flags: " + device.configFlags);

    // Активируем кнопку только для USB-устройств
    safeEjectButton->setEnabled(device.deviceClass == "USB");
}

void MainWindow::on_deviceComboBox_currentIndexChanged(int index)
{
    updateDeviceDetails(index);
}

bool MainWindow::ejectDevice(const QString& pid)
{
    HDEVINFO deviceInfo = SetupDiGetClassDevs(nullptr, nullptr, nullptr, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfo == INVALID_HANDLE_VALUE) {
        qDebug() << "SetupDiGetClassDevs failed.";
        return false;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfo, i, &deviceInfoData); i++) {
        DWORD dataSize = 0;
        SetupDiGetDeviceInstanceId(deviceInfo, &deviceInfoData, nullptr, 0, &dataSize);
        TCHAR* buffer = new TCHAR[dataSize];
        if (SetupDiGetDeviceInstanceId(deviceInfo, &deviceInfoData, buffer, dataSize, nullptr)) {
            QString deviceInstanceId = QString::fromWCharArray(buffer);
            delete[] buffer;

            if (deviceInstanceId.contains(pid, Qt::CaseInsensitive)) {
                DEVINST devInst = deviceInfoData.DevInst;
                ULONG status = 0;

                CONFIGRET cr = CM_Request_Device_Eject(devInst, nullptr, nullptr, 0, 0);
                SetupDiDestroyDeviceInfoList(deviceInfo);

                if (cr == CR_SUCCESS) {
                    qDebug() << "Device ejected successfully.";
                    return true;
                } else {
                    qDebug() << "Failed to eject device.";
                    return false;
                }
            }
        } else {
            delete[] buffer;
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfo);
    qDebug() << "Device not found.";
    return false;
}

void MainWindow::onSafeEjectButtonClicked() {
    if (deviceComboBox->currentIndex() < 0) return;

    const Device &device = devices[deviceComboBox->currentIndex()];
    QString pid = device.productID;

    bool result = ejectDevice(pid);

    if (result) {
        QMessageBox::information(this, "Success", "Device safely ejected.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to eject device.");
    }
}

void MainWindow::onRefreshButtonClicked() {
    loadDeviceData();  // Заново загружаем данные устройств
    deviceComboBox->clear();  // Очищаем комбобокс перед обновлением

    for (const auto &device : devices) {
        deviceComboBox->addItem(device.busNumber + "-" + device.deviceNumber + " " + device.vendorName + " --- " + device.deviceDescription);
    }

    // Сбрасываем текущий индекс и обновляем детали
    deviceComboBox->setCurrentIndex(-1);
    updateDeviceDetails(-1);
}
