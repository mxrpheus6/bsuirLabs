int charASCII(char symbol);
int deliCheck(char symbol);
int wordIndex(const char* string, int* index);
char* getWordFromTxt(const char* string, int beginIndex);
char* getChangeForWord(struct Dictionary** array, const char* string, const int* size);