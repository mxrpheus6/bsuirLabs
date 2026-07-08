#include <iostream>
#include <fstream>
#include <Winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <locale.h>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")
using namespace std;

enum FileType { UNKNOWN, MP3, PNG, MP4, TXT };

// Function to identify file type based on magic number
FileType identifyFileType(const char* buffer)
{
    // MP3: Magic number 0xFF 0xFB (ID3 tag)
    if (buffer[0] == (char)0xFF && buffer[1] == (char)0xFB)
        return MP3;

    // PNG: Magic number 0x89 0x50 0x4E 0x47
    if (buffer[0] == (char)0x89 && buffer[1] == (char)0x50 && buffer[2] == (char)0x4E && buffer[3] == (char)0x47)
        return PNG;

    // MP4: Magic number starts with 0x00 0x00 0x00 0x18 0x66 0x74 0x79 0x70
    if (buffer[0] == (char)0x00 && buffer[1] == (char)0x00 && buffer[2] == (char)0x00 && buffer[3] == (char)0x18 &&
        buffer[4] == (char)0x66 && buffer[5] == (char)0x74 && buffer[6] == (char)0x79 && buffer[7] == (char)0x70)
        return MP4;

    // TXT: Text file (simplified check, you can use more sophisticated methods)
    return TXT; // Default to TXT if no match
}

int recvAll(int socket, char* buffer, int dataSize, int flags = 0) {
    int totalBytesRead = 0; // Общее количество считанных байт
    while (totalBytesRead < dataSize) {
        int bytesRead = recv(socket, buffer + totalBytesRead, dataSize - totalBytesRead, flags);
        if (bytesRead <= 0) {
            // Если recv вернул 0 или меньше, значит произошла ошибка или соединение закрыто
            return bytesRead;
        }
        totalBytesRead += bytesRead;
    }
    return totalBytesRead;
}

int getFile(SOCKET clientSocket) {
    // Получение длины имени файла
    int fileNameLength;
    if (recv(clientSocket, reinterpret_cast<char*>(&fileNameLength), sizeof(fileNameLength), 0) <= 0)
        return -1;

    // Получение имени файла
    char* fileNameBuffer = new char[fileNameLength + 1];
    memset(fileNameBuffer, 0, fileNameLength + 1);
    if (recvAll(clientSocket, fileNameBuffer, fileNameLength, 0) <= 0) {
        delete[] fileNameBuffer;
        return -1;
    }
    std::string fileName(fileNameBuffer);
    delete[] fileNameBuffer;

    // Получение размера файла
    char fileSize[20];
    memset(fileSize, '\0', 20);
    if (recvAll(clientSocket, fileSize, 20, 0) <= 0)
        return -1;
    int dataSize = atoi(fileSize);

    if (dataSize <= 0)
        return 0;

    std::cout << "Receiving file: " << fileName << " (" << dataSize << " bytes)" << std::endl;

    // Определение типа файла
    char buffer[1024];
    FileType fileType = UNKNOWN;
    std::ofstream outputFile;

    if (recvAll(clientSocket, buffer, 1024, 0) > 0) {
        fileType = identifyFileType(buffer);
    }

    // Формирование пути для сохранения файла
    std::string filePath = "D:/" + fileName;
    outputFile.open(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
    if (dataSize < 1024) {
        outputFile.write(buffer, dataSize);
        dataSize = 0;
    }
    else {
        outputFile.write(buffer, 1024);
        dataSize -= 1024;
    }

    // Чтение оставшейся части файла
    while (dataSize > 0) {
        int bytesToRead = (1024 < dataSize) ? 1024 : dataSize;
        int bytes = recvAll(clientSocket, buffer, bytesToRead, 0);
        if (bytes <= 0) break;
        outputFile.write(buffer, bytes);
        dataSize -= bytes;
    }
    outputFile.close();

    // Открытие файла в соответствующем приложении
    switch (fileType) {
    case MP3:
        system(("start \"\" \"" + filePath + "\"").c_str());
        break;
    case PNG:
        system(("start \"\" \"" + filePath + "\"").c_str());
        break;
    case MP4:
        system(("start \"\" \"" + filePath + "\"").c_str());
        break;
    case TXT:
        system(("start \"\" \"" + filePath + "\"").c_str());
        break;
    default:
        std::cout << "File received and saved, but unsupported type!" << std::endl;
        break;
    }

    return 0;
}

SOCKET initServerSocket()
{
    SOCKADDR_BTH sockaddrBthServer = { 0 };
    sockaddrBthServer.addressFamily = AF_BTH;
    sockaddrBthServer.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sockaddrBthServer.port = 6;

    SOCKET serverSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    bind(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthServer), sizeof(sockaddrBthServer));

    int addrLen = sizeof(sockaddrBthServer);
    getsockname(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthServer), &addrLen);

    return serverSocket;
}

SOCKET initClientSocket(SOCKET serverSocket)
{
    SOCKADDR_BTH sockaddrBthClient = { 0 };
    int clientAddrSize = sizeof(sockaddrBthClient);
    SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthClient), &clientAddrSize);

    return clientSocket;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = initServerSocket();
    listen(serverSocket, SOMAXCONN);
    cout << "Server is ready to accept connections." << endl;

    while (true)
    {
        cout << "Waiting for a connection..." << endl;
        SOCKET clientSocket = initClientSocket(serverSocket);
        cout << "Client connected." << endl;

        while (true)
        {
            int result = getFile(clientSocket);
            if (result == -1)
                break;
        }

        cout << "File transfer completed." << endl << endl;
        closesocket(clientSocket);
    }

    cout << "Server shutting down." << endl;
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
