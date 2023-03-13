void fillDictionaryArray(struct WordFrequency** arrayOfWords, FILE* pointer, struct Dictionary** arrayOfChanges, int amountOfWords, int* sizeOfDictionary);
void pushDictionaryToFile(struct Dictionary** arrayOfChanges, FILE** pointer, int sizeOfDictionary);
void archiveFile(FILE* pointerOg, FILE* pointerArch, Dictionary* array, int sizeOfDictionary);