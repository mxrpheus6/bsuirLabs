#include "packet.h"

QByteArray encodeToByteArray(const QString &input) {
    QStringEncoder encoder(QStringEncoder::Utf16LE);
    return encoder.encode(input);
}

QString getBinaryRepresentation(const QByteArray &data) {
    QString binaryRepresentation;

    for (char byte : data) {
        binaryRepresentation += QString::fromStdString(std::bitset<8>(static_cast<unsigned char>(byte)).to_string());
    }

    return binaryRepresentation;
}

QByteArray Packet::serializePacket(const Packet& packet) {
    QByteArray byteArray;

    byteArray.append(reinterpret_cast<const char*>(&packet.flag), sizeof(packet.flag));
    byteArray.append(reinterpret_cast<const char*>(&packet.destinationAddress), sizeof(packet.destinationAddress));
    byteArray.append(reinterpret_cast<const char*>(&packet.sourceAddress), sizeof(packet.sourceAddress));

    byteArray.append(packet.data);

    byteArray.append(reinterpret_cast<const char*>(&packet.fcs), sizeof(packet.fcs));

    return byteArray;
}

QList<Packet> Packet::generatePacketListByData(const QString &data) {
    QList<Packet> packets;

    QByteArray staffedData = bitStuffing(data);

    int64_t totalDataSize = staffedData.size(), offset = 0;
    while (totalDataSize > 0) {
        Packet packet;

        if (totalDataSize > packetDataFieldSize)
            packet.data = staffedData.mid(offset, packetDataFieldSize);
        else {
            packet.data = staffedData.mid(offset, totalDataSize);
            packet.data.append(QByteArray((packetDataFieldSize - totalDataSize), '\0'));
        }

        packets.append(packet);
        totalDataSize -= packetDataFieldSize;
        offset += packetDataFieldSize;
    }

    return packets;
}

bool Packet::transmitPackets(QSerialPort *port, const QList<Packet> &packets) {
    if (port->isOpen()) {
        for (const auto& p : packets) {
            port->write(serializePacket(p));
            port->waitForBytesWritten(1000);
        }
        return true;
    } else {
        return false;
    }
}

QList<Packet> Packet::receivePackets(QSerialPort *port) {
    QList<Packet> packets;

    if (port->isOpen() && port->waitForReadyRead(1000)) {
        QByteArray receivedData = port->readAll();

        while (port->waitForReadyRead(10)) {
            receivedData += port->readAll();
        }

        const int packetSize = 28;

        for (int i = 0; i < receivedData.size(); i += packetSize) {
            Packet packet;

            QByteArray flagBytes = receivedData.mid(i, 8);
            packet.flag = *reinterpret_cast<const uint64_t*>(flagBytes.constData());

            QByteArray destinationBytes = receivedData.mid(i + 8, 4);
            packet.destinationAddress = *reinterpret_cast<const uint32_t*>(destinationBytes.constData());

            QByteArray sourceBytes = receivedData.mid(i + 12, 4);
            packet.sourceAddress = *reinterpret_cast<const uint32_t*>(sourceBytes.constData());

            packet.data = receivedData.mid(i + 16, 11);

            packet.fcs = static_cast<uint8_t>(receivedData[i + 27]);

            packets.append(packet);
        }
    }

    return packets;
}

QByteArray Packet::bitStuffing(const QString &data) {
    QByteArray byteArray = data.toUtf8();

    QString binaryRepresentation = getBinaryRepresentation(byteArray);

    QString stuffedBinary;
    uint32_t consecutiveOnes = 0;
    for (int i = 0; i < binaryRepresentation.size();) {
        stuffedBinary += binaryRepresentation[i];
        if (binaryRepresentation[i] == '0' && i != binaryRepresentation.size() - 1) {
            i++;
            consecutiveOnes = 0;
            while (binaryRepresentation[i] == '1' && i != binaryRepresentation.size() - 1) {
                stuffedBinary += binaryRepresentation[i];
                consecutiveOnes++;
                if (consecutiveOnes == 6) {
                    stuffedBinary += '1';
                    consecutiveOnes = 0;
                    i++;
                    break;
                }
                i++;
            }
        } else {
            i++;
        }
    }

    stuffedBinary.append(QString(((8 - (stuffedBinary.size() % 8)) % 8), '0'));

    QString result;
    for (int i = 0; i < stuffedBinary.size(); i += 8) {
        QString byteString = stuffedBinary.mid(i, 8);
        std::bitset<8> bits(byteString.toStdString());
        char character = static_cast<char>(bits.to_ulong());
        result += QChar(character);
    }

    QByteArray a = encodeToByteArray(result);

    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '\0') {
            a.remove(i, 1);
        }
    }

    return a;
}

QString Packet::Unstuffing(const QByteArray &data) {
    QByteArray dataWithoutZero = data;

    for (int i = dataWithoutZero.size() - 1; i >= 0; --i) {
        if (dataWithoutZero[i] == '\0') {
            dataWithoutZero.remove(i, 1);
        }
    }

    QString binaryRepresentation = getBinaryRepresentation(dataWithoutZero);

    QString deStuffedBinary;
    uint32_t consecutiveOnes = 0;
    for (int i = 0; i < binaryRepresentation.size();) {
        deStuffedBinary += binaryRepresentation[i];
        if (binaryRepresentation[i] == '0' && i != binaryRepresentation.size() - 1) {
            i++;
            consecutiveOnes = 0;
            while (binaryRepresentation[i] == '1' && i != binaryRepresentation.size() - 1) {
                deStuffedBinary += binaryRepresentation[i];
                consecutiveOnes++;
                if (consecutiveOnes == 6) {
                    consecutiveOnes = 0;
                    QString partToShift = binaryRepresentation.mid(i + 1);
                    partToShift = partToShift.mid(1) + '0';
                    binaryRepresentation = binaryRepresentation.left(i + 1) + partToShift;
                    i++;
                    break;
                }
                i++;
            }
        } else {
            i++;
        }
    }

    QString result;
    for (int i = 0; i < deStuffedBinary.size(); i += 8) {
        QString byteString = deStuffedBinary.mid(i, 8);
        std::bitset<8> bits(byteString.toStdString());
        char character = static_cast<char>(bits.to_ulong());
        result += QChar(character);
    }

    for (int i = result.size() - 1; i >= 0; --i) {
        if (result[i] == '\0') {
            result.remove(i, 1);
        }
    }

    return result;
}
