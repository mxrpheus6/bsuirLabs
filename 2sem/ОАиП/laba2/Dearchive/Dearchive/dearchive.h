void dearchiveFile(FILE* pointerOg, FILE* pointerArch, struct Dictionary** array, int* sizeOfDictionary);
void changeWords(char** buf, const char* word, const char* changedWord, int* index);
void processText(struct Dictionary** array, int* sizeOfDictionary, char* word, char* bufFromFile, int* beginIndex, char* changedWord, int* index);