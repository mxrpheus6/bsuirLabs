#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QList>
#include <QSerialPort>
#include <QStringEncoder>

#include <iostream>
#include <bitset>

class Packet
{
public:
    static const uint8_t packetDataFieldSize = 11;

    static QList<Packet> generatePacketListByData(const QString& data);
    static bool transmitPackets(QSerialPort* port, const QList<Packet> &packets);
    static QList<Packet> receivePackets(QSerialPort* port);
    static QByteArray bitStuffing(const QString& data);
    static QString Unstuffing(const QByteArray& data);
    static QString byteArrayToString(const QByteArray &byteArray);

    int64_t getFlag() const { return flag; }
    int32_t getDestinationAddress() const { return destinationAddress; }
    int32_t getSourceAddress() const { return sourceAddress; }
    QByteArray getData() const { return data; }
    int8_t getFcs() const { return fcs; }

    void setFlag(int64_t value) { flag = value; }
    void setDestinationAddress(int32_t value) { destinationAddress = value; }
    void setSourceAddress(int32_t value) { sourceAddress = value; }
    void setData(const QByteArray& value) { data = value; }
    void setFcs(int8_t value) { fcs = value; }
private:
    uint64_t flag = 10;
    uint32_t destinationAddress = 0;
    uint32_t sourceAddress;
    QByteArray data;
    uint8_t fcs = 0;

    static QByteArray serializePacket(const Packet& packet);
};

#endif // PACKET_H
