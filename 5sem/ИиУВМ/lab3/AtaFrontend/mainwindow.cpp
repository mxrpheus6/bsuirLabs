#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPalette>
#include <QFile>
#include <QFileDialog>
#include <cmath>
#include <QScrollArea>
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    deviceList = new QListWidget(this);
    deviceInfoLabel = new QLabel("Выберите устройство для просмотра", this);
    deviceInfoLabel->setWordWrap(true);

    loadFileButton = new QPushButton("Загрузить существующий дамп", this);
    connect(loadFileButton, &QPushButton::clicked, this, &MainWindow::onLoadFileButtonClicked);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(deviceInfoLabel);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(deviceList);
    layout->addWidget(loadFileButton);
    layout->addWidget(scrollArea);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    loadDeviceList();

    connect(deviceList, &QListWidget::itemSelectionChanged, this, &MainWindow::onDeviceSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDeviceList() {
    const auto &devices = getAtaDevices();

    int i = 0;
    for (const auto &device : devices) {
        QListWidgetItem *item = new QListWidgetItem(
            QString("Диск %1").arg(++i), deviceList);
        item->setData(Qt::UserRole, QVariant::fromValue(device));
    }
}

QString MainWindow::getDeviceDetails(const DeviceInfo &device) {
    const auto *pataInfo = reinterpret_cast<const PataDeviceInfo*>(device.dump.data());
    QString details;

    details += QString("Модель: %1\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->ModelNumber), 40).trimmed());
    details += QString("Серийный номер: %1\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->SerialNumber), 20).trimmed());
    details += QString("Версия прошивки: %1\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->FirmwareRevision), 8).trimmed());
    details += QString("Производитель носителя: %1\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->FirmwareRevision), 8).trimmed());
    details += QString("Тип носителя: Н/Д\n\n");

    details += QString("Носитель съемный: %1\n").arg(pataInfo->GeneralConfiguration.RemovableMedia ? "Съемный" : "Несъемный");
    details += QString("Дополнительный идентификатор продукта: %1\n\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->AdditionalProductID), 8).trimmed());

    details += QString("Логические цилиндры (макс): %1\n").arg(pataInfo->NumCylinders);
    details += QString("Логические цилиндры (текущие): %1\n").arg(pataInfo->NumberOfCurrentCylinders);
    details += QString("Логические головки (макс): %1\n").arg(pataInfo->NumHeads);
    details += QString("Логические головки (текущие): %1\n").arg(pataInfo->NumberOfCurrentHeads);
    details += QString("Логические сектора на дорожке (макс): %1\n").arg(pataInfo->NumSectorsPerTrack);
    details += QString("Логические сектора на дорожке (текущие): %1\n").arg(pataInfo->CurrentSectorsPerTrack);

    details += QString("CHS Текущие адресуемые сектора: %1\n").arg(pataInfo->NumberOfCurrentCylinders * pataInfo->CurrentSectorsPerTrack * pataInfo->NumberOfCurrentHeads);

    details += QString("LBA Адресуемые сектора пользователем: %1\n").arg(pataInfo->UserAddressableSectors);
    quint64 lba48Sectors = (static_cast<quint64>(pataInfo->Max48BitLBA[1]) << 32) | pataInfo->Max48BitLBA[0];
    details += QString("LBA48 Адресуемые сектора пользователем: %1\n").arg(lba48Sectors);

    const auto logicalSectorSize = 512;
    details += QString("Размер логического сектора (Б): %1\n").arg(logicalSectorSize);
    details += QString("Размер физического сектора (Б): %1\n").arg(pataInfo->CurrentSectorCapacity);
    details += QString("Непустой смещение логического сектора: %1\n").arg(pataInfo->BlockAlignment.AlignmentOfLogicalWithinPhysical);

    const uint32_t* buffer = reinterpret_cast<const uint32_t*>(pataInfo);
    const uint64_t size = (uint64_t)buffer[30] * logicalSectorSize;

    details += QString("Размер устройства (МБ): %1\n").arg(size / (1000 * 1000));
    details += QString("Размер устройства (Миб): %1\n").arg(size / (1024 * 1024));
    details += QString("Размер устройства (ГБ): %1\n").arg(size / (1000 * 1000 * 1000));
    details += QString("Размер устройства (Гиб): %1\n\n").arg(size / (1024 * 1024 * 1024));

    details += QString("Поддержка LBA: %1\n").arg(pataInfo->Capabilities.LbaSupported);
    details += QString("Поддержка LBA48: %1\n").arg(pataInfo->Capabilities.LbaSupported ? "Включена" : "Отключена");

    details += QString("IOReady: %1\n").arg(pataInfo->Capabilities.IordySupported ? "Включен" : "Отключен");

    details += QString("Поддержка DMA: %1\n").arg(pataInfo->Capabilities.DmaSupported ? "Да" : "Нет");

    details += QString("Время цикла PIO (без управления потоком): %1\n").arg(pataInfo->MinimumPIOCycleTime);
    details += QString("Время цикла PIO (управление потоком IOReady): %1\n").arg(pataInfo->MinimumPIOCycleTimeIORDY);

    details += QString("Время цикла DMA (минимум): %1\n").arg(pataInfo->MinimumMWXferCycleTime);
    details += QString("Время цикла DMA (рекомендуемое): %1\n").arg(pataInfo->RecommendedMWXferCycleTime);

    details += QString("Поддерживаемые режимы PIO: %1\n").arg(pataInfo->AdvancedPIOModes);
    details += QString("Поддерживаемые режимы одиночного DMA: %1\n").arg(pataInfo->MultiWordDMASupport);
    details += QString("Поддерживаемые режимы множественного DMA: %1\n").arg(pataInfo->MultiWordDMAActive);
    details += QString("Поддерживаемые режимы Ultra DMA: %1\n").arg(pataInfo->UltraDMASupport);

    return details;
}

QString getDeviceDetailsByPath(const DeviceInfo &device) {
    const auto *pataInfo = reinterpret_cast<const PataDeviceInfo*>(device.dump.data());
    QString details;

    details += QString("Модель: %1\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->ModelNumber), 40).trimmed());
    details += QString("Серийный номер: %1\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->SerialNumber), 20).trimmed());
    details += QString("Версия прошивки: %1\n").arg(QString::fromLocal8Bit(reinterpret_cast<const char*>(pataInfo->FirmwareRevision), 8).trimmed());

    details += QString("Логические цилиндры (макс): %1\n").arg(pataInfo->NumCylinders);
    details += QString("Логические цилиндры (текущие): %1\n").arg(pataInfo->NumberOfCurrentCylinders);
    details += QString("Логические головки (макс): %1\n").arg(pataInfo->NumHeads);
    details += QString("Логические головки (текущие): %1\n").arg(pataInfo->NumberOfCurrentHeads);
    details += QString("Логические сектора на дорожке (макс): %1\n").arg(pataInfo->NumSectorsPerTrack);
    details += QString("Логические сектора на дорожке (текущие): %1\n").arg(pataInfo->CurrentSectorsPerTrack);

    details += QString("CHS Текущие адресуемые сектора: %1\n").arg(pataInfo->CurrentSectorCapacity);

    details += QString("LBA Адресуемые сектора пользователем: %1\n").arg(pataInfo->UserAddressableSectors);
    quint64 lba48Sectors = (static_cast<quint64>(pataInfo->Max48BitLBA[1]) << 32) | pataInfo->Max48BitLBA[0];
    details += QString("LBA48 Адресуемые сектора пользователем: %1\n").arg(lba48Sectors);

    const auto logicalSectorSize = 512;
    details += QString("Размер логического сектора (Б): %1\n").arg(logicalSectorSize);
    details += QString("Размер физического сектора (Б): %1\n").arg(pataInfo->CurrentSectorCapacity);

    details += QString("Непустой смещение логического сектора: %1\n").arg(pataInfo->BlockAlignment.AlignmentOfLogicalWithinPhysical);

    uint64_t deviceSizeBytes = (uint64_t)pataInfo->UserAddressableSectors * logicalSectorSize;
    details += QString("Размер устройства (МБ): %1\n").arg(deviceSizeBytes / (1000 * 1000));
    details += QString("Размер устройства (Миб): %1\n").arg(deviceSizeBytes / (1024 * 1024));
    details += QString("Размер устройства (ГБ): %1\n").arg(deviceSizeBytes / (1000 * 1000 * 1000));
    details += QString("Размер устройства (Гиб): %1\n\n").arg(deviceSizeBytes / (1024 * 1024 * 1024));

    return details;
}

void MainWindow::onLoadFileButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выбор дампа", "", "Binary Files (*.bin);;Hex Files (*.hex);;All Files (*)");
    if (filePath.isEmpty()) return;

    std::string dumpPath = filePath.toStdString();

    DeviceInfo device;

    std::ifstream dump(dumpPath, std::ios::binary);
    if (!dump.is_open()) {
        std::cerr << "Ошибка открытия дампа: \"" << dumpPath << "\"" << std::endl;
        return;
    }

    device.dump.resize(512);

    dump.read(reinterpret_cast<char*>(device.dump.data()), device.dump.size());

    if (!dump) {
        std::cerr << "Ошибка чтения дампа: \"" << dumpPath << "\"" << std::endl;
        return;
    }

    dump.close();

    QString details = getDeviceDetails(device);

    deviceInfoLabel->setText(details);
}


QString getInterfaceNameByValue(DeviceInterface interfaceName) {
    switch (interfaceName) {
    case DeviceInterface::PATA: return "PATA";
    case DeviceInterface::SATA: return "SATA";
    case DeviceInterface::PATAPI: return "PATAPI";
    case DeviceInterface::SATAPI: return "SATAPI";
    default: return "UNKNOWN";
    }
}

QString getBusNameByValue(AtaBus busName) {
    switch (busName) {
    case AtaBus::PrimaryBus: return "Primary Bus";
    case AtaBus::SecondaryBus: return "Secondary Bus";
    case AtaBus::ExtraPrimaryBus: return "Extra Primary Bus";
    case AtaBus::ExtraSecondaryBus: return "Extra Secondary Bus";
    default: return "";
    }
}

void MainWindow::onDeviceSelected() {
    if (deviceList->selectedItems().isEmpty()) return;

    QListWidgetItem *selectedItem = deviceList->selectedItems().first();
    DeviceInfo device = selectedItem->data(Qt::UserRole).value<DeviceInfo>();

    switch(device.id_result.status) {
    case DeviceStatus::Floating: deviceInfoLabel->setText("Bus Floating"); return;
    case DeviceStatus::Error: {
        QString text = getBusNameByValue(device.id_result.bus); text += "\n";
        text += QString("Номер диска: %1\n").arg(static_cast<uint32_t>(device.id_result.position));
        text += QString("Ошибка идентификации устройства\n\n");
        deviceInfoLabel->setText(text);
        return;
    }
    case DeviceStatus::NotConnected: {
        QString text = getBusNameByValue(device.id_result.bus); text += "\n";
        text += QString("Номер диска: %1\n").arg(static_cast<uint32_t>(device.id_result.position));
        text += QString("Устройство не подключено\n\n");
        deviceInfoLabel->setText(text);
        return;
    }
    case DeviceStatus::NotPATA: {
        QString text = QString("Интерфейс: %1\n").arg(getInterfaceNameByValue(device.id_result.interf));
        text += getBusNameByValue(device.id_result.bus); text += "\n";
        text += QString("Номер диска: %1").arg(static_cast<uint32_t>(device.id_result.position));
        deviceInfoLabel->setText(text);
        return;
    }
    case DeviceStatus::Identified: {
        QString text = QString("Интерфейс: %1\n").arg(getInterfaceNameByValue(device.id_result.interf));
        text += getBusNameByValue(device.id_result.bus); text += "\n";
        text += QString("Номер диска: %1\n\n").arg(static_cast<uint32_t>(device.id_result.position));
        text += getDeviceDetails(device);
        deviceInfoLabel->setText(text);
        return;
    }
    }
}
