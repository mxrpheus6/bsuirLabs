#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QWidget>

class Device {
public:
    QString busNumber;
    QString deviceNumber;
    QString vendorID;
    QString productID;
    QString vendorName;
    QString productName;
    QString friendlyName;
    QString manufacturer;
    QString deviceDescription;
    QString deviceClass;
    QString deviceSubclass;
    QString deviceProtocol;
    QString hardwareID;
    QString compatibleIDs;
    QString configFlags;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_deviceComboBox_currentIndexChanged(int index);
    void onSafeEjectButtonClicked();
    void onRefreshButtonClicked();

private:
    void loadDeviceData();
    void updateDeviceDetails(int index);
    void checkNotifyFile();
    bool ejectDevice(const QString& hardwareID);

    QWidget *centralWidget;
    QComboBox *deviceComboBox;
    QPushButton *safeEjectButton;
    QPushButton *refreshButton;
    QLabel *busNumberLabel;
    QLabel *deviceNumberLabel;
    QLabel *vendorIDLabel;
    QLabel *productIDLabel;
    QLabel *vendorNameLabel;
    QLabel *productNameLabel;
    QLabel *friendlyNameLabel;
    QLabel *manufacturerLabel;
    QLabel *deviceDescriptionLabel;
    QLabel *deviceClassLabel;
    QLabel *deviceSubclassLabel;
    QLabel *deviceProtocolLabel;
    QLabel *hardwareIDLabel;
    QLabel *compatibleIDsLabel;
    QLabel *configFlagsLabel;
    QTimer *fileCheckTimer;

    QVector<Device> devices;
};

#endif // MAINWINDOW_H
