#include "files.h"

int fileOpen(FILE** pointer, char* path, char* mode) {
	*pointer = fopen(path, mode);

	if (*pointer == NULL) {
		printf("Error openning file. File does not exist.\n\n");
		return FALSE;
	}

	if (strcmp("r", mode) == 0) {
		fseek(*pointer, 0L, SEEK_END);
		long int fileSize = ftell(*pointer);
		fseek(*pointer, 0L, SEEK_SET);
		if (fileSize < MIN_FILE_SIZE) {
			printf("Error openning file. File size is less than 50 bytes.\n\n");
			return FALSE;
		}
	}

	return TRUE;
}

char* openByPath(FILE** pointer) {
	int result;
	char* path = (char*)malloc(MAX_PATH_LENGTH);

	do {
		printf("Enter path (minimal file size is 50 bytes): ");
		scanf("%s", path);
		rewind(stdin);
		path[strlen(path)] = '\0';
	} while (fileOpen(pointer, path, "r") == FALSE);

	return path;
}

void createDecryptedFile(FILE** pointer) {
	char path[MAX_PATH_LENGTH];
	printf("Enter path for decrypted text: ");
	scanf("%s", path);
	while ((*pointer = fopen(path, "w")) == NULL) {
		printf("Invalid input. Enter correct path: ");
		scanf("%s", path);
	}
}

void decryptFile(FILE* pointerEnc, int shift) {
	FILE* newFilePointer;
	char buffer[BUFFER_SIZE];
	fseek(pointerEnc, 0L, SEEK_SET);

	createDecryptedFile(&newFilePointer);

	while (fgets(buffer, BUFFER_SIZE, pointerEnc) != NULL) {
		caesaerCipher(buffer, shift, DECRYPT);
		fputs(buffer, newFilePointer);
	}

	fclose(newFilePointer);
}

void checkAnalysis(FreqDict mostPopularNotEnc, FreqDict* arrayEnc, char* pathEnc) {
	FILE* pointerEnc;
	FreqDict tempDict;
	int i;
	int shift;
	char symbol;
	char choice = '\0';
	char symbolStr[2];
	char buffer[MIN_FILE_SIZE + 1];
	fileOpen(&pointerEnc, pathEnc, "r");

	for (i = 0; i < ALPHABET_SIZE; i++) {
		system("cls");
		fseek(pointerEnc, 0L, SEEK_SET);
		tempDict = arrayEnc[i];
		shift = abs(mostPopularNotEnc.symbol - tempDict.symbol);
		if (shift == 0) {
			printf("Text that is breaking is already decrypted...");
			//Sleep(5000);
			break;
		}
		buffer[0] = '\0';
		while ((symbol = fgetc(pointerEnc)) != EOF) {
			if (!isprint(symbol)) {
				strcat(buffer, " ");
				continue;
			}
			symbolStr[0] = symbol;
			symbolStr[1] = '\0';
			strcat(buffer, symbolStr);

			if (strlen(buffer) == MIN_FILE_SIZE) {
				buffer[strlen(buffer)] = '\0';
				break;
			}	
		}
		caesaerCipher(buffer, shift, DECRYPT);
		printf("Does it look like decrypted text?\n---------------------------------\n%s\n\n", buffer);
		printf("Your choice (y\\n): ");
		while (scanf("%c", &choice) != 1 || getchar() != '\n' || (choice != 'y' && choice != 'n')) {
			printf("Invalid input. You have to choose y or n: ");
			rewind(stdin);
		}
		if (choice == 'y') {
			printf("\nCongrats! Key of the text is %d\n\n", shift);
			decryptFile(pointerEnc, shift);
			printf("\nSuccessfully decrypted!");
			//Sleep(5000);
			break;
		}
	}
	if (choice == 'n' && i == ALPHABET_SIZE) {
		printf("You're probably skipped right variant. Please, try again...");
		//Sleep(5000);
	}
	fclose(pointerEnc);
}