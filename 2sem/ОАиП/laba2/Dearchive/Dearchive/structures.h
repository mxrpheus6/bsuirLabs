typedef enum {
	FALSE,
	TRUE
} Bool;


typedef struct Dictionary {
	char* originalWord;
	char* changeWord;
} Dictionary;

void fillDictionaryFromFile(FILE* pointerArch, Dictionary** array, int* size);