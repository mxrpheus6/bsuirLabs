#include "packet.h"

#include <bitset>
#include <QStringEncoder>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

const uint16_t Packet::controlBitsPositions[8] = {0, 1, 3, 7, 15, 31, 63, 127};

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

std::vector<int> Packet::calculateHammingCode(const std::string& bitsStr, int& r) {
    int n = bitsStr.length();
    r = 1;

    while (std::pow(2, r) < n + r + 1) {
        r++;
    }

    std::vector<int> code(n + r, 0);

    int j = 0;
    int k = 0;
    for (int i = 1; i < n + r + 1; i++) {
        if (i == static_cast<int>(std::pow(2, j))) {
            j++;
        }
        else {
            code[i - 1] = bitsStr[k++] - '0';
        }
    }

    for (int i = 0; i < r; i++) {
        int powerOfTwo = static_cast<int>(std::pow(2, i));
        int count = 0;
        for (int j = powerOfTwo; j < n + r + 1; j++) {
            if (j & powerOfTwo) {
                count += code[j - 1];
            }
        }
        code[powerOfTwo - 1] = count % 2;
    }

    return code;
}

int calculateParity(const std::vector<int>& bitsStr) {
    int parity = 0;
    for (int bit : bitsStr) {
        parity ^= bit;
    }
    return parity;
}

std::vector<int> Packet::getControlBits(const QString& bitsStr) {
    int r = 0;
    std::vector<int> a = Packet::calculateHammingCode(bitsStr.toStdString(), r);
    std::vector<int> b(r + 1, 0);

    for (int i = 0; i < r; i++) {
        b[i] = a[Packet::controlBitsPositions[i]];
    }

    b[b.size() - 1] = calculateParity(a);

    return b;
}

uint16_t Packet::getControlBitsFCS(const QString& bitsStr) {
    std::vector<int> bits = getControlBits(bitsStr);

    uint16_t result = 0;

    for (int i = 0; i < bits.size(); ++i) {
        result |= (bits[i] << (15 - i));
    }

    return result;
}

std::vector<int> Packet::convertBitsToVector(uint16_t bits) {
    std::vector<int> bitVector;

    for (int i = 15; i >= 0; --i) {
        int bit = (bits >> i) & 1;
        bitVector.push_back(bit);
    }

    return bitVector;
}

int calcPosByBits(std::vector<int> a, std::vector<int> b, int r) {
    int res = 0;

    if (r >= 1 && a[0] != b[0])
        res += 1;
    if (r >= 2 && a[1] != b[1])
        res += 2;
    if (r >= 3 && a[2] != b[2])
        res += 4;
    if (r >= 4 && a[3] != b[3])
        res += 8;
    if (r >= 5 && a[4] != b[4])
        res += 16;
    if (r >= 6 && a[5] != b[5])
        res += 32;
    if (r >= 7 && a[6] != b[6])
        res += 64;
    if (r >= 8 && a[7] != b[7])
        res += 128;

    return res;
}

int getWithoutBits(int errorPosition) {
    int res = errorPosition;

    if (errorPosition == 3) {
        res -= 2;
        return res;
    }
    if (errorPosition > 4 && errorPosition < 8) {
        res -= 3;
        return res;
    }
    if (errorPosition > 8 && errorPosition < 16) {
        res -= 4;
        return res;
    }
    if (errorPosition > 16 && errorPosition < 32) {
        res -= 5;
        return res;
    }
    if (errorPosition > 32 && errorPosition < 64) {
        res -= 6;
        return res;
    }
    if (errorPosition > 64 && errorPosition < 128) {
        res -= 7;
        return res;
    }
    if (errorPosition > 128) {
        res -= 8;
        return res;
    }
    return res;
}

void fixError(std::string& bitsStr, std::vector<int> bitsStrHam, std::vector<int> newBitsHam, int r) {
    int pos = calcPosByBits(bitsStrHam, newBitsHam, r);
    int pos2 = getWithoutBits(pos);
    bitsStr[pos2 - 1] = (bitsStr[pos2 - 1] == '0') ? '1' : '0';
}

QString bitsToBytes(const QString& stuffedBinary) {
    QString result;

    for (int i = 0; i < stuffedBinary.size(); i += 8) {
        QString byteString = stuffedBinary.mid(i, 8);
        std::bitset<8> bits(byteString.toStdString());
        char character = static_cast<char>(bits.to_ulong());
        result += QChar(character);
    }

    return result;
}

Packet::FixedDataInfo Packet::findAndFixError(QString data, uint16_t fcs) {
    std::vector<int> convertedFcs = Packet::convertBitsToVector(fcs);
    std::vector<int> controlBits = Packet::getControlBits(getBinaryRepresentation(data.toUtf8()));

    bool isEqual = true;
    for (int i = 0; i < controlBits.size(); i++) {
        if (controlBits[i] != convertedFcs[i]) {
            isEqual = false;
            break;
        }
    }

    FixedDataInfo info;

    if (isEqual) {
        info.data = data;
        info.controlBitsBefore = convertedFcs;
        info.controlBitsAfter = convertedFcs;
        info.errorPosition = -1;
        return info;
    }
    else {
        QString bin = getBinaryRepresentation(data.toUtf8());

        int pos = calcPosByBits(controlBits, convertedFcs, controlBits.size() - 1);
        int pos2 = getWithoutBits(pos);

        if (pos2 > bin.size()) {
            info.data = QString("Double error detected: out of bound");
            info.controlBitsBefore = controlBits;
            info.controlBitsAfter = controlBits;
            info.errorPosition = pos2;
            return info;
        }

        bin[pos2 - 1] = (bin[pos2 - 1] == '0') ? '1' : '0';

        std::vector<int> controlBits2 = getControlBits(bin);

        if (convertedFcs[controlBits.size() - 1] != controlBits2[controlBits.size() - 1]) {
            info.data = QString("Double error detected");
            info.controlBitsBefore = controlBits;
            info.controlBitsAfter = controlBits2;
            info.errorPosition = pos2;
            return info;
        }
        else {
            info.data = bitsToBytes(bin);
            info.controlBitsBefore = controlBits;
            info.controlBitsAfter = controlBits2;
            info.errorPosition = pos2;
            return info;
        }
    }
}

QList<Packet::FixedDataInfo> Packet::checkPacketsDataIntegrity(const QList<Packet> &packets) {
    QByteArray mergedData;
    for (const auto& p : packets) {
        mergedData.append(p.getData());
    }

    QString deStuffedData = Unstuffing(mergedData);
    int64_t totalDataSize = deStuffedData.size(), offset = 0;
    QString packetData;
    QList<FixedDataInfo> result;
    FixedDataInfo info;
    int p = 0;

    while (totalDataSize > 0) {
        if (totalDataSize > packetDataFieldSize) {
            packetData = deStuffedData.mid(offset, packetDataFieldSize);
        }
        else {
            packetData = deStuffedData.mid(offset, totalDataSize);
        }

        info = findAndFixError(packetData, packets[p].fcs);
        p++;

        result.append(info);
        totalDataSize -= packetDataFieldSize;
        offset += packetDataFieldSize;
    }

    return result;
}

QString generateError(const QByteArray& bitString) {
    std::srand(std::time(nullptr));

    QString modifiedString = getBinaryRepresentation(bitString);

    int probability = std::rand() % 100;

    auto getRandomNonFirstBitIndex = [&](int size) -> int {
        int index;
        do {
            index = std::rand() % size;
        } while (index % 8 == 0);
        return index;
    };

    if (probability < 60) {
        int bitToInvert = getRandomNonFirstBitIndex(bitString.size());
        modifiedString[bitToInvert] = (bitString[bitToInvert] == '0') ? '1' : '0';
    }
    else if (probability < 85) {
        int firstBitToInvert = getRandomNonFirstBitIndex(bitString.size());
        int secondBitToInvert;

        do {
            secondBitToInvert = getRandomNonFirstBitIndex(bitString.size());
        } while (secondBitToInvert == firstBitToInvert);

        modifiedString[firstBitToInvert] = (bitString[firstBitToInvert] == '0') ? '1' : '0';
        modifiedString[secondBitToInvert] = (bitString[secondBitToInvert] == '0') ? '1' : '0';
    }

    return bitsToBytes(modifiedString);
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

        if (totalDataSize > packetDataFieldSize) {
            packet.data = staffedData.mid(offset, packetDataFieldSize);
            packet.fcs = getControlBitsFCS(getBinaryRepresentation(packet.data));
        }
        else {
            packet.data = staffedData.mid(offset, totalDataSize);
            packet.fcs = getControlBitsFCS(getBinaryRepresentation(packet.data));
            packet.data.append(QByteArray((packetDataFieldSize - totalDataSize), '\0'));
        }

        packets.append(packet);
        totalDataSize -= packetDataFieldSize;
        offset += packetDataFieldSize;
    }

    return packets;
}

bool Packet::transmitPackets(QSerialPort *port, QList<Packet> &packets) {
    if (port->isOpen()) {
        for (auto& p : packets) {
            p.data = generateError(p.data).toUtf8();
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

        const int packetSize = 29;

        for (int i = 0; i < receivedData.size(); i += packetSize) {
            Packet packet;

            QByteArray flagBytes = receivedData.mid(i, 8);
            packet.flag = *reinterpret_cast<const uint64_t*>(flagBytes.constData());

            QByteArray destinationBytes = receivedData.mid(i + 8, 4);
            packet.destinationAddress = *reinterpret_cast<const uint32_t*>(destinationBytes.constData());

            QByteArray sourceBytes = receivedData.mid(i + 12, 4);
            packet.sourceAddress = *reinterpret_cast<const uint32_t*>(sourceBytes.constData());

            packet.data = receivedData.mid(i + 16, 11);

            QByteArray fcsBytes = receivedData.mid(i + 27, 2);
            packet.fcs = *reinterpret_cast<const uint16_t*>(fcsBytes.constData());

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

void Packet::generateBusyBusStatus() {
    std::random_device device;
    std::mt19937 generator(device());
    std::bernoulli_distribution distribution(0.5f);

    CommonBus::isBusy = distribution(generator);
}

void Packet::generateCollisionStatus() {
    std::random_device device;
    std::mt19937 generator(device());
    std::bernoulli_distribution distribution(0.3f);

    CommonBus::isCollisionDetected = distribution(generator);
}

int Packet::generateWaitTime(const uint32_t attempt) {
    static constexpr uint8_t bitInterval = 0x52;

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<> distribution(0, std::pow(2, (attempt > 10 ? 10 : attempt)) - 1);

    return 512 * bitInterval * distribution(generator);
}

std::vector<uint16_t> Packet::transmitPacketsWithCollision(QSerialPort *port, QList<Packet> &packets) {
    std::vector<uint16_t> packetsCollisions(packets.size());

    if (port->isOpen()) {
        for (int i = 0; i < packets.size(); i++) {
            packets[i].data = generateError(packets[i].data).toUtf8();
            QByteArray data = serializePacket(packets[i]);

            for (int j = 0; j < data.size(); j++) {
                generateBusyBusStatus();
                while (CommonBus::isBusy) {
                    generateBusyBusStatus();

                    std::this_thread::sleep_for(std::chrono::microseconds(10));
                }

                QByteArray a;
                a += data[j];
                port->write(a);
                port->waitForBytesWritten(1000);
                std::this_thread::sleep_for(std::chrono::milliseconds(20));

                uint16_t attempts = 0;
                generateCollisionStatus();
                while (CommonBus::isCollisionDetected) {
                    if (attempts == 16) break;

                    std::this_thread::sleep_for(std::chrono::nanoseconds(generateWaitTime(attempts)));
                    attempts++;

                    while (CommonBus::isBusy) {
                        generateBusyBusStatus();

                        std::this_thread::sleep_for(std::chrono::microseconds(10));
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                    generateCollisionStatus();
                }

                packetsCollisions[i] = attempts;
            }
        }
        return packetsCollisions;
    } else {
        return packetsCollisions;
    }
}
