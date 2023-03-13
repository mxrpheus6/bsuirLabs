typedef enum {
	FALSE,
	TRUE
} Bool;

typedef struct WordFrequency {
	char* word;
	int frequency;
	int length;
	int size;
} WordFrequency;

typedef struct Dictionary {
	char* originalWord;
	char* changeWord;
} Dictionary;

void printStructArray(WordFrequency* array, int size);
void printDictionary(Dictionary* array, int size);