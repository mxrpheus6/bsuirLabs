#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <windows.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <dshow.h>
#include <string>

#pragma comment(lib, "Strmiids.lib")

std::vector<int> cameraIndexes;

void GetAvailableCameraIndex() {
    cv::VideoCapture testCamera;
    for (int i = 0; i < 10; i++) {
        testCamera.open(i);
        if (testCamera.isOpened()) {
            cameraIndexes.push_back(i);
            testCamera.release();
        }
    }
}

void parseVIDPID(const std::wstring& devicePath, std::wstring& vid, std::wstring& pid) {
    size_t vidPos = devicePath.find(L"vid_");
    size_t pidPos = devicePath.find(L"pid_");

    if (vidPos != std::wstring::npos && pidPos != std::wstring::npos) {
        vid = devicePath.substr(vidPos + 4, 4);

        pid = devicePath.substr(pidPos + 4, 4);
    }
}

void parseUsbIds(const std::wstring& vid, const std::wstring& pid, std::wstring& vidResult, std::wstring& pidResult) {
    std::wifstream usbIdsFile(L"usb.ids");
    if (!usbIdsFile.is_open()) {
        vidResult = L"N/A";
        pidResult = L"N/A";
        return;
    }

    std::wstring line;
    bool vidFound = false;

    while (std::getline(usbIdsFile, line)) {
        if (line.empty() || line[0] == L'#') {
            continue;
        }

        if (!vidFound && !line.empty() && line[0] == L' ') {
            continue;
        }

        size_t vidPos = line.find(vid);
        if (vidPos != std::wstring::npos) {
            vidFound = true;
            vidResult = line.substr(6);
            pidResult = L"N/A";
            continue;
        }

        if (vidFound) {
            size_t pidPos = line.find(pid);
            if (pidPos != std::wstring::npos) {
                pidResult = line.substr(10);
                break;
            }

            size_t newVidPos = line.find(L"VID_");
            if (newVidPos != std::wstring::npos) {
                break;
            }
        }
    }

    if (!vidFound) {
        vidResult = L"N/A";
    }

    usbIdsFile.close();
}

void parseUsbIdsOpt(const std::wstring& vid, const std::wstring& pid, std::wstring& vidResult, std::wstring& pidResult) {
    std::wifstream usbIdsFile(L"usb.ids");
    if (!usbIdsFile.is_open()) {
        vidResult = L"N/A";
        pidResult = L"N/A";
        return;
    }

    std::wstring line;
    bool vidFound = false;

    while (std::getline(usbIdsFile, line)) {
        if (line.empty() || line[0] == L'#') {
            continue;
        }

        if (vidFound && line[0] != L' ') {
            pidResult = L"N/A";
            break;
        }

        size_t vidPos = line.find(vid);
        if (vidPos != std::wstring::npos) {
            vidFound = true;
            vidResult = line.substr(6);
            continue;
        }

        if (vidFound) {
            size_t pidPos = line.find(pid);
            if (pidPos != std::wstring::npos) {
                pidResult = line.substr(10);
                break;
            }
        }
    }

    if (!vidFound) {
        vidResult = L"N/A";
    }

    usbIdsFile.close();
}

void EnumerateDirectShowDevices() {
    CoInitialize(NULL);

    ICreateDevEnum* pDevEnum = NULL;
    IEnumMoniker* pEnum = NULL;
    int camIndex = 0;

    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
    if (SUCCEEDED(hr)) {
        std::vector<std::wstring> audioDevicePaths;
        IEnumMoniker* pAudioEnum = NULL;

        hr = pDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &pAudioEnum, 0);
        if (SUCCEEDED(hr) && pAudioEnum) {
            IMoniker* pAudioMoniker = NULL;
            while (pAudioEnum->Next(1, &pAudioMoniker, NULL) == S_OK) {
                IPropertyBag* pAudioPropBag;
                hr = pAudioMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pAudioPropBag));
                if (SUCCEEDED(hr)) {
                    VARIANT var;
                    VariantInit(&var);
                    hr = pAudioPropBag->Read(L"DevicePath", &var, 0);
                    if (SUCCEEDED(hr)) {
                        audioDevicePaths.push_back(var.bstrVal);
                        VariantClear(&var);
                    }
                    pAudioPropBag->Release();
                }
                pAudioMoniker->Release();
            }
            pAudioEnum->Release();
        }

        hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
        if (SUCCEEDED(hr) && pEnum) {
            IMoniker* pMoniker = NULL;
            while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
                IPropertyBag* pPropBag;
                hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
                if (SUCCEEDED(hr)) {
                    std::wstringstream filename;
                    filename << L"cam" << camIndex++ << L".txt";
                    std::wofstream outFile(filename.str());
                    if (!outFile.is_open()) {
                        pPropBag->Release();
                        pMoniker->Release();
                        continue;
                    }

                    VARIANT var;
                    VariantInit(&var);

                    hr = pPropBag->Read(L"FriendlyName", &var, 0);
                    if (SUCCEEDED(hr)) {
                        outFile << L"Device Name: " << var.bstrVal << std::endl;
                        VariantClear(&var);
                    }

                    hr = pPropBag->Read(L"DevicePath", &var, 0);
                    if (SUCCEEDED(hr)) {
                        std::wstring devicePath = var.bstrVal;
                        outFile << L"Device Path: " << devicePath << std::endl;

                        std::wstring vid, pid, vName, pName;
                        parseVIDPID(devicePath, vid, pid);
                        outFile << L"Vendor ID: " << vid << std::endl;
                        outFile << L"Product ID: " << pid << std::endl;

                        auto start = std::chrono::high_resolution_clock::now();
                        parseUsbIdsOpt(vid, pid, vName, pName);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> duration = end - start;
                        outFile << L"Vendor Name: " << vName << std::endl;
                        outFile << L"Product Name: " << pName << std::endl;
                        outFile << L"Time taken by parseUsbIdsOpt: " << duration.count() << L" seconds" << std::endl;

                        bool hasMicrophone = std::any_of(audioDevicePaths.begin(), audioDevicePaths.end(),
                            [&](const std::wstring& audioPath) {
                                return devicePath.find(audioPath) != std::wstring::npos;
                            });

                        if (hasMicrophone) {
                            outFile << L"Microphone: Present" << std::endl;
                        }
                        else {
                            outFile << L"Microphone: Not Present" << std::endl;
                        }

                        VariantClear(&var);
                    }

                    outFile.close();
                    pPropBag->Release();
                }
                pMoniker->Release();
            }
            pEnum->Release();
        }
        pDevEnum->Release();
    }
    CoUninitialize();
}


void saveCameraInfoToFile() {
    for (int index : cameraIndexes) {
        cv::VideoCapture camera(index);
        if (!camera.isOpened()) {
            MessageBox(NULL, L"ERROR: Could not open camera", L"Error", MB_ICONERROR | MB_OK);
            return;
        }

        std::stringstream infoFilename;
        infoFilename << "cam" << index << ".txt";

        std::string filename = infoFilename.str();

        std::ofstream outFile(filename, std::ios::app);

        if (!outFile.is_open()) {
            std::cerr << "Could not open file for writing!" << std::endl;
            return;
        }

        camera.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
        camera.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
        int width = static_cast<int>(camera.get(cv::CAP_PROP_FRAME_WIDTH));
        int height = static_cast<int>(camera.get(cv::CAP_PROP_FRAME_HEIGHT));
        double fps = camera.get(cv::CAP_PROP_FPS);
        double brightness = camera.get(cv::CAP_PROP_BRIGHTNESS);
        double contrast = camera.get(cv::CAP_PROP_CONTRAST);
        double saturation = camera.get(cv::CAP_PROP_SATURATION);
        double gamma = camera.get(cv::CAP_PROP_GAMMA);
        double focus = camera.get(cv::CAP_PROP_FOCUS);
        double pan = camera.get(cv::CAP_PROP_PAN);
        double tilt = camera.get(cv::CAP_PROP_TILT);
        double roll = camera.get(cv::CAP_PROP_ROLL);
        double autoExposure = camera.get(cv::CAP_PROP_AUTO_EXPOSURE);
        double whiteBalanceBlueU = camera.get(cv::CAP_PROP_WHITE_BALANCE_BLUE_U);
        double whiteBalanceRedV = camera.get(cv::CAP_PROP_WHITE_BALANCE_RED_V);
        int bufferSize = static_cast<int>(camera.get(cv::CAP_PROP_BUFFERSIZE));
        int codec = static_cast<int>(camera.get(cv::CAP_PROP_FOURCC));
        int frameCount = static_cast<int>(camera.get(cv::CAP_PROP_FRAME_COUNT));
        int format = static_cast<int>(camera.get(cv::CAP_PROP_FORMAT));
        double exposure = camera.get(cv::CAP_PROP_EXPOSURE);
        double gain = camera.get(cv::CAP_PROP_GAIN);
        double hue = camera.get(cv::CAP_PROP_HUE);
        double sharpness = camera.get(cv::CAP_PROP_SHARPNESS);
        double zoom = camera.get(cv::CAP_PROP_ZOOM);
        double isoSpeed = camera.get(cv::CAP_PROP_ISO_SPEED);
        double backlight = camera.get(cv::CAP_PROP_BACKLIGHT);
        double temperature = camera.get(cv::CAP_PROP_TEMPERATURE);
        double autofocus = camera.get(cv::CAP_PROP_AUTOFOCUS);
        double rectification = camera.get(cv::CAP_PROP_RECTIFICATION);
        int bitrate = static_cast<int>(camera.get(cv::CAP_PROP_BITRATE));
        int mode = static_cast<int>(camera.get(cv::CAP_PROP_MODE));
        int monochrome = static_cast<int>(camera.get(cv::CAP_PROP_MONOCHROME));

        outFile << "Camera Resolution:" << width << "x" << height << std::endl;
        outFile << "FPS:" << fps << std::endl;
        outFile << "Brightness:" << brightness << std::endl;
        outFile << "Contrast:" << contrast << std::endl;
        outFile << "Saturation:" << saturation << std::endl;
        outFile << "Gamma:" << gamma << std::endl;
        outFile << "Focus:" << focus << std::endl;
        outFile << "Pan:" << pan << std::endl;
        outFile << "Tilt:" << tilt << std::endl;
        outFile << "Roll:" << roll << std::endl;
        outFile << "Auto Exposure:" << autoExposure << std::endl;
        outFile << "White Balance Blue U:" << whiteBalanceBlueU << std::endl;
        outFile << "White Balance Red V:" << whiteBalanceRedV << std::endl;
        outFile << "Buffer Size:" << bufferSize << std::endl;
        outFile << "Codec:" << codec << std::endl;
        outFile << "Frame Count:" << frameCount << std::endl;
        outFile << "Format:" << format << std::endl;
        outFile << "Exposure:" << exposure << std::endl;
        outFile << "Gain:" << gain << std::endl;
        outFile << "Hue:" << hue << std::endl;
        outFile << "Sharpness:" << sharpness << std::endl;
        outFile << "Zoom:" << zoom << std::endl;
        outFile << "ISO Speed:" << isoSpeed << std::endl;
        outFile << "Backlight:" << backlight << std::endl;
        outFile << "Temperature:" << temperature << std::endl;
        outFile << "Auto Focus:" << autofocus << std::endl;
        outFile << "Rectification:" << rectification << std::endl;
        outFile << "Bitrate:" << bitrate << std::endl;
        outFile << "Mode:" << mode << std::endl;
        outFile << "Monochrome:" << monochrome << std::endl;

        outFile.close();
        camera.release();
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    GetAvailableCameraIndex();
    if (cameraIndexes.size() == 0) {
        MessageBox(NULL, L"ERROR: No available cameras", L"Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    EnumerateDirectShowDevices();
    saveCameraInfoToFile();

    int width = 1920;
    int height = 1080;

    auto lastCaptureTime = std::chrono::steady_clock::now();

    cv::Mat frame;

    while (1) {
        auto nowCaptureTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(nowCaptureTime - lastCaptureTime).count() >= 60 - cameraIndexes.size()) {
            lastCaptureTime = nowCaptureTime;
            for (int index : cameraIndexes) {
                cv::VideoCapture camera(index);
                if (!camera.isOpened()) {
                    MessageBox(NULL, L"ERROR: Could not open camera", L"Error", MB_ICONERROR | MB_OK);
                    return 1;
                }

                camera.set(cv::CAP_PROP_FRAME_WIDTH, width);
                camera.set(cv::CAP_PROP_FRAME_HEIGHT, height);

                camera >> frame;
                if (frame.empty()) {
                    MessageBox(NULL, L"ERROR: Empty frame", L"Error", MB_ICONERROR | MB_OK);
                    return 1;
                }

                std::string verText = "OpenCV ver: 4.9.0";
                std::string resText = "Resolution: " + 
                                      std::to_string(static_cast<int>(camera.get(cv::CAP_PROP_FRAME_WIDTH))) + "x" + 
                                      std::to_string(static_cast<int>(camera.get(cv::CAP_PROP_FRAME_HEIGHT)));
                cv::putText(frame, verText, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
                cv::putText(frame, resText, cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);

                auto now = std::chrono::system_clock::now();
                auto time = std::chrono::system_clock::to_time_t(now);
                std::tm localTime;
                localtime_s(&localTime, &time);

                std::stringstream photoFilenameStream;
                photoFilenameStream << "cam" << index << "-"
                    << std::put_time(&localTime, "%Y-%m-%dT%H-%M-%S")
                    << ".jpg";

                std::string photoFilename = photoFilenameStream.str();

                cv::imwrite(photoFilename, frame);
                camera.release();
                frame.release();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
    }

    return 0;
}