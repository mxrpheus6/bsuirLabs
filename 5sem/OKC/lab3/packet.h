#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QList>
#include <QSerialPort>
#include <QStringEncoder>

#include <iostream>
#include <bitset>
#include <cstdint>

class Packet
{
public:
    struct FixedDataInfo {
        QString data;
        std::vector<int> controlBitsBefore;
        std::vector<int> controlBitsAfter;
        int errorPosition;
    };

    static const uint16_t controlBitsPositions[8];
    static const uint8_t packetDataFieldSize = 11;

    static QList<Packet> generatePacketListByData(const QString& data);
    static bool transmitPackets(QSerialPort *port, QList<Packet> &packets);
    static QList<Packet> receivePackets(QSerialPort* port);
    static QByteArray bitStuffing(const QString& data);
    static QString Unstuffing(const QByteArray& data);
    static QString byteArrayToString(const QByteArray &byteArray);
    static std::vector<int> convertBitsToVector(uint16_t bits);
    static QList<FixedDataInfo> checkPacketsDataIntegrity(const QList<Packet> &packets);

    int64_t getFlag() const { return flag; }
    int32_t getDestinationAddress() const { return destinationAddress; }
    int32_t getSourceAddress() const { return sourceAddress; }
    QByteArray getData() const { return data; }
    int16_t getFcs() const { return fcs; }

    void setFlag(int64_t value) { flag = value; }
    void setDestinationAddress(int32_t value) { destinationAddress = value; }
    void setSourceAddress(int32_t value) { sourceAddress = value; }
    void setData(const QByteArray& value) { data = value; }
    void setFcs(int16_t value) { fcs = value; }
private:
    uint64_t flag = 10;
    uint32_t destinationAddress = 0;
    uint32_t sourceAddress;
    QByteArray data;
    uint16_t fcs = 0;

    static QByteArray serializePacket(const Packet& packet);
    static std::vector<int> calculateHammingCode(const std::string& bitsStr, int& r);
    static std::vector<int> getControlBits(const QString& bitsStr);
    static uint16_t getControlBitsFCS(const QString& bitsStr);
    static FixedDataInfo findAndFixError(QString data, uint16_t fcs);
};

#endif // PACKET_H
