#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "parser.h"

//void fileParse() {
//    setlocale(LC_ALL, "ru_RU.UTF-8");
//    FILE* filePointer;
//    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
//    wchar_t* bigBuf = (wchar_t*)calloc(2048, sizeof(wchar_t));
//    wchar_t* bigBufPointer;
//    wchar_t test[200];
//    wchar_t testChar;
//    int i = 0;
//    fopen_s(&filePointer, "D:/Work/html.txt", "r, ccs=UTF-8");
//    if (filePointer == NULL) {
//        printf("Ошибка. Не удается открыть файл.");
//    }
//    for (int i = 0; i < 1270; i++) {
//        fgetws(buf, 255, filePointer);
//    }
//    while (fgetws(buf, 255, filePointer)) {
//        wchar_t* start = wcsstr(buf, L"lseparator_catalog");
//        if (start != NULL) {
//            while (wcsstr(buf, L"</li>") == NULL) {
//                fgetws(buf, 255, filePointer);
//                wchar_t* temp = wcsstr(buf, L"result__name");
//                if (temp != NULL) {
//                    i = 0;
//                    while (buf[i] != '>') {
//                        i++;
//                    }
//                    i++;
//                    while (buf[i] != '<') {
//                        wprintf(L"%c", buf[i]);
//                        i++;
//                    }
//                    printf("\n");
//                }
//                temp = wcsstr(buf, L"result__attrs");
//                if (temp != NULL) {
//                    fgetws(bigBuf, 2048, filePointer);
//                    bigBuf = wcsstr(bigBuf, L"Диагональ экрана");
//                    bigBuf = wcsstr(bigBuf, L"cr-result__attr_odd");
//                    bigBuf = wcsstr(bigBuf, L">");
//                    i = 1;
//                    while (bigBuf[i] != '&') {
//                        wprintf(L"%c", bigBuf[i]);
//                        i++;
//                    }
//                    printf("\n");
//                }
//            }
//            }
//        }
//    fclose(filePointer);
//    free(buf);
//}

//void fileParse() {
//    setlocale(LC_ALL, "ru_RU.UTF-8");
//    FILE* filePointer;
//    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
//    wchar_t* bigBuf = (wchar_t*)calloc(10000, sizeof(wchar_t));
//    wchar_t test[200];
//    wchar_t testChar;
//    int i = 0;
//    int counter;
//    fopen_s(&filePointer, "D:/Work/html.txt", "r, ccs=UTF-8");
//    if (filePointer == NULL) {
//        printf("Ошибка. Не удается открыть файл.");
//    }
//    for (int i = 0; i < 1270; i++) {
//        fgetws(buf, 255, filePointer);
//    }
//    while (fgetws(buf, 255, filePointer) != NULL && !feof(filePointer)) {
//        wchar_t* start = wcsstr(buf, L"lseparator_catalog");
//        if (start != NULL) {
//            while (wcsstr(buf, L"</li>") == NULL) {
//                fgetws(buf, 255, filePointer);
//                wchar_t* temp = wcsstr(buf, L"result__name");
//                if (temp != NULL) {
//                    i = 0;
//                    while (buf[i] != '>') {
//                        i++;
//                    }
//                    i++;
//                    while (buf[i] != '<') {
//                        wprintf(L"%c", buf[i]);
//                        i++;
//                    }
//                    printf("\n");
//                }
//                wchar_t* temp1 = wcsstr(buf, L"result__attrs");
//                if (temp1 != NULL) {
//                    fgetws(bigBuf, 10000, filePointer);
//                    while (1) {
//                        //bigBuf = wcsstr(bigBuf, L"Диагональ экрана");
//                        wchar_t* temp2 = wcsstr(bigBuf, L"Диагональ экрана");
//                        i = 0;
//                        counter = 0;
//                        while (temp2[i] != '&') {
//                            if (temp2[i] == '>') {
//                                counter = 0;
//                            }
//                            else {
//                                counter++;
//                            }
//                            i++;
//                        }
//                        i -= counter;
//                        while (temp2[i] != '&') {
//                            wprintf(L"%c", temp2[i]);
//                            i++;
//                        }
//                        printf("\n");
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    fclose(filePointer);
//    free(bigBuf);
//    free(buf);
//}

void parseName(FILE* pointer) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
    int i = 0;
    for (int i = 0; i < 1270; i++) {
        fgetws(buf, 255, pointer);
    }
    while (fgetws(buf, 255, pointer) != NULL && !feof(pointer)) {
        wchar_t* start = wcsstr(buf, L"lseparator_catalog");
        if (start != NULL) {
            while (wcsstr(buf, L"</li>") == NULL) {
                fgetws(buf, 255, pointer);
                wchar_t* temp = wcsstr(buf, L"result__name");
                if (temp != NULL) {
                    i = 0;
                    while (buf[i] != '>') {
                        i++;
                    }
                    i++;
                    while (buf[i] != '<') {
                        wprintf(L"%c", buf[i]);
                        i++;
                    }
                    printf("\n");
                }
            }
        }
    }
    free(buf);
    rewind(pointer);
}

void parseDiag(FILE* pointer) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
    wchar_t* bigBuf = (wchar_t*)calloc(10000, sizeof(wchar_t));
    int i = 0;
    int counter;
    for (int i = 0; i < 1270; i++) {
        fgetws(buf, 255, pointer);
    }
    while (fgetws(buf, 255, pointer) != NULL && !feof(pointer)) {
        wchar_t* start = wcsstr(buf, L"result__attrs");
        if (start != NULL) {
            fgetws(bigBuf, 10000, pointer);
            while (1) {
                wchar_t* temp2 = wcsstr(bigBuf, L"Диагональ экрана");
                i = 0;
                counter = 0;
                while (temp2[i] != '&') {
                    if (temp2[i] == '>') {
                        counter = 0;
                    }
                    else {
                        counter++;
                    }
                    i++;
                }
                i -= counter;
                while (temp2[i] != '&') {
                    wprintf(L"%c", temp2[i]);
                    i++;
                }
                printf("\n");
                break;
            }
        }
    }
    free(buf);
    free(bigBuf);
    rewind(pointer);
}

void parseRam(FILE* pointer) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
    wchar_t* bigBuf = (wchar_t*)calloc(10000, sizeof(wchar_t));
    int i = 0;
    int counter;
    for (int i = 0; i < 1270; i++) {
        fgetws(buf, 255, pointer);
    }
    while (fgetws(buf, 255, pointer) != NULL && !feof(pointer)) {
        wchar_t* start = wcsstr(buf, L"result__attrs");
        if (start != NULL) {
            fgetws(bigBuf, 10000, pointer);
            while (1) {
                wchar_t* temp2 = wcsstr(bigBuf, L"Оперативная память");
                temp2 = wcsstr(temp2, L"result__attr_val");
                i = 0;
                counter = 0;
                while (temp2[i] != '<') {
                    if (temp2[i] == '>') {
                        counter = 0;
                    }
                    else {
                        counter++;
                    }
                    i++;
                }
                i -= counter;
                while (temp2[i] != ' ') {
                    wprintf(L"%c", temp2[i]);
                    i++;
                }
                printf("\n");
                break;
            }
        }
    }
    free(buf);
    free(bigBuf);
    rewind(pointer);
}

void parseMemory(FILE* pointer) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
    wchar_t* bigBuf = (wchar_t*)calloc(10000, sizeof(wchar_t));
    int i = 0;
    int counter;
    for (int i = 0; i < 1270; i++) {
        fgetws(buf, 255, pointer);
    }
    while (fgetws(buf, 255, pointer) != NULL && !feof(pointer)) {
        wchar_t* start = wcsstr(buf, L"result__attrs");
        if (start != NULL) {
            fgetws(bigBuf, 10000, pointer);
            while (1) {
                wchar_t* temp2 = wcsstr(bigBuf, L"Постоянная память");
                temp2 = wcsstr(temp2, L"result__attr_val");
                i = 0;
                counter = 0;
                while (temp2[i] != '<') {
                    if (temp2[i] == '>') {
                        counter = 0;
                    }
                    else {
                        counter++;
                    }
                    i++;
                }
                i -= counter;
                while (temp2[i] != ' ') {
                    wprintf(L"%c", temp2[i]);
                    i++;
                }
                printf("\n");
                break;
            }
        }
    }
    free(buf);
    free(bigBuf);
    rewind(pointer);
}

void parseCameraResolution(FILE* pointer) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
    wchar_t* bigBuf = (wchar_t*)calloc(10000, sizeof(wchar_t));
    int i = 0;
    int counter;
    for (int i = 0; i < 1270; i++) {
        fgetws(buf, 255, pointer);
    }
    while (fgetws(buf, 255, pointer) != NULL && !feof(pointer)) {
        wchar_t* start = wcsstr(buf, L"result__attrs");
        if (start != NULL) {
            fgetws(bigBuf, 10000, pointer);
            while (1) {
                wchar_t* temp2 = wcsstr(bigBuf, L"Разрешение камеры");
                temp2 = wcsstr(temp2, L"result__attr_val");
                i = 0;
                counter = 0;
                while (temp2[i] != '<') {
                    if (temp2[i] == '>') {
                        counter = 0;
                    }
                    else {
                        counter++;
                    }
                    i++;
                }
                i -= counter;
                while (temp2[i] != ' ') {
                    wprintf(L"%c", temp2[i]);
                    i++;
                }
                printf("\n");
                break;
            }
        }
    }
    free(buf);
    free(bigBuf);
    rewind(pointer);
}

void parseBattery(FILE* pointer) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t* buf = (wchar_t*)calloc(255, sizeof(wchar_t));
    wchar_t* bigBuf = (wchar_t*)calloc(10000, sizeof(wchar_t));
    int i = 0;
    int counter;
    for (int i = 0; i < 1270; i++) {
        fgetws(buf, 255, pointer);
    }
    while (fgetws(buf, 255, pointer) != NULL && !feof(pointer)) {
        wchar_t* start = wcsstr(buf, L"result__attrs");
        if (start != NULL) {
            fgetws(bigBuf, 10000, pointer);
            while (1) {
                wchar_t* temp2 = wcsstr(bigBuf, L"Емкость аккумулятора");
                temp2 = wcsstr(temp2, L"result__attr_val");
                i = 0;
                counter = 0;
                while (temp2[i] != '<') {
                    if (temp2[i] == '>') {
                        counter = 0;
                    }
                    else {
                        counter++;
                    }
                    i++;
                }
                i -= counter;
                while (temp2[i] != '&') {
                    wprintf(L"%c", temp2[i]);
                    i++;
                }
                printf("\n");
                break;
            }
        }
    }
    free(buf);
    free(bigBuf);
    rewind(pointer);
}