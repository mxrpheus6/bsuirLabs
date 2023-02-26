#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

#include "parser.h"
#include "structeres.h"
#include "memory.h"

typedef enum { 
    MEMORY = 34,
    RAM = 36,
    BATTERY = 40
} ParseTypes;

char** parseName(FILE* pointer) {
    char* buf = (char*)calloc(255, sizeof(char));
    char** result = (char**)calloc(60, sizeof(char*));
    for (int i = 0; i < 60; i++) {
        result[i] = (char*)calloc(255, sizeof(char));
    }
    int i;
    int j = 0;
    int k;
    int pos;
    int counter;
    while (fgets(buf, 255, pointer) != NULL && !feof(pointer)) {
        char* start = strstr(buf, "result__name");
        if (start != NULL) {
            i = 0;
            k = 0;
            counter = 0;
            while (buf[i] != '>') {
                i++;
            }
            i++;
            i += 17;
            while (buf[i] != '/') {
                result[j][k] = buf[i];
                i++;
                k++;
            }
            result[j] = (char*)realloc(result[j], strlen(result[j]) - counter + 1);
            result[j][k - counter] = '\0';
            j++;
        }
    }
    free(buf);
    rewind(pointer);
    return result;
}

float* parseDiag(FILE* pointer) {
    char* buf = (char*)calloc(255, sizeof(char));
    char* bigBuf = (char*)calloc(4096, sizeof(char));
    char* temp;
    float* result = (float*)calloc(60, sizeof(float));
    int i;
    int j;
    int k = 0;
    int counter;
    while (fgets(buf, 255, pointer) != NULL && !feof(pointer)) {
        char* start = strstr(buf, "result__attrs");
        if (start != NULL) {
            fgets(bigBuf, 4096, pointer);
            i = 0;
            j = 0;
            counter = 0;
            while (bigBuf[i] != '&') {
                if (bigBuf[i] == '>') {
                    counter = 0;
                }
                else {
                    counter++;
                }
                i++;
            }
            i -= counter;
            temp = (char*)calloc(counter, sizeof(char));
            while (bigBuf[i] != '&') {
                temp[j] = bigBuf[i];
                i++;
                j++;
            }
            temp = (char*)realloc(temp, counter * sizeof(char));
            temp[j] = '\0';
            result[k] = atof(temp);
            k++;
        }
    }
    free(buf);
    free(bigBuf);
    rewind(pointer);
    return result;
}

int* parseInt(FILE* pointer, int len) {
    char* buf = (char*)calloc(255, sizeof(char));
    char* bigBuf = (char*)calloc(4096, sizeof(char));
    char* temp = (char*)calloc(8, sizeof(char));
    int* result = (int*)calloc(60, sizeof(int));
    int i;
    int j;
    int k = 0;
    int flag;
    int counterOut;

    while (fgets(buf, 255, pointer) != NULL && !feof(pointer)) {
        char* start = strstr(buf, "result__attrs");
        if (start != NULL) {
            flag = 0;
            i = 0;
            j = 0;
            fgets(bigBuf, 4096, pointer);
            char* cutBuf = strstr(bigBuf, "result__attr_var  cr-result__attr_odd");
            while (flag != 1) {
                counterOut = 0;
                while (cutBuf[i] != '>') {
                    i++;
                }
                while (cutBuf[i] != '<') {
                    i++;
                    counterOut++;
                }
                if (counterOut == len) {
                    i += 35;
                    if (cutBuf[i] > 47 && cutBuf[i] < 58) {
                        while (cutBuf[i] != '<') {
                            temp[j] = cutBuf[i];
                            i++;
                            j++;
                        }
                        result[k] = atoi(temp);
                        flag = 1;
                        k++;
                    }
                    else {
                        i += 20;
                        while (cutBuf[i] != '<') {
                            temp[j] = cutBuf[i];
                            i++;
                            j++;
                        }

                        result[k] = atoi(temp);
                        flag = 1;
                        k++;

                    }
                }
            }
        }
    }
    free(buf);
    free(bigBuf);
    rewind(pointer);
    return result;
}

void parse(Smartphone** array, FILE* pointer, int* size) {
    int i;
    i = *size;
    (*size) += 60;
    if (*array == NULL) {
        *array = (Smartphone*)malloc((*size) * sizeof(Smartphone));
    }
    else {
        *array = (Smartphone*)realloc(*array, (*size) * sizeof(Smartphone));
    }
    char** name = parseName(pointer);
    float* diag = parseDiag(pointer);
    int* memory = parseInt(pointer, MEMORY);
    int* ram = parseInt(pointer, RAM);
    int* battery = parseInt(pointer, BATTERY);
    for ( ; i < *size; i++) {
        charMemoryAllocate(&(*array)[i].name);
        (*array)[i].name = name[i];
        (*array)[i].screenSize = diag[i];
        (*array)[i].memory = memory[i];
        (*array)[i].ram = ram[i];
        (*array)[i].battery = battery[i];
    }
}
