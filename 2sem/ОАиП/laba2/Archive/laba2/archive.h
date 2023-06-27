void fillDictionaryArray(struct WordFrequency** arrayOfWords, struct Dictionary** arrayOfChanges, int amountOfWords, int* sizeOfDictionary);
void pushDictionaryToFile(struct Dictionary** arrayOfChanges, FILE** pointer, int sizeOfDictionary);
void processText(Dictionary** array, int* sizeOfDictionary, char* word, char* bufFromFile, int* beginIndex, char* changedWord, int* index);
void changeWords(char** buf, const char* word, const char* changedWord, int* index);
void archiveFile(FILE* pointerOg, FILE* pointerArch, Dictionary** array, int* sizeOfDictionary);