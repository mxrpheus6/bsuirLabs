#pragma once

#define MAX_PATH_LENGTH 256
#define MIN_FILE_SIZE 25
#define BUFFER_SIZE 1024

int fileOpen(FILE** pointer, char* path, char* mode);

char* openByPath(FILE** pointer);

void createDecryptedFile(FILE** pointer);

void decryptFile(FILE* pointerEnc, int shift);

void checkAnalysis(FreqDict mostPopularNotEnc, FreqDict* arrayEnc, char* pathEnc);