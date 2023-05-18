#include "menu.h"

void pause(void) {
	printf("Press any key to continue...\n");
	_getch();
}

void menuInformation(void) {
	printf("Caesar breaker By Pavel Kazachenko\n");
	printf("---------------MENU---------------\n");
	printf("1) Decrypt\n");
	printf("2) Exit\n");
	printf("----------------------------------\n");
	printf("Your choice: ");
}

void mainMenu(void) {
	FreqDict* dictionaryNotEnc = NULL;
	FreqDict* dictionaryEnc = NULL;
	FreqDict mostFrequentWord;
	int userInput;
	char* pathNotEnc = (char*)malloc(sizeof(char) * MAX_PATH_LENGTH);
	char* pathEnc = (char*)malloc(sizeof(char) * MAX_PATH_LENGTH);
	initFreqDict(&dictionaryEnc);
	initFreqDict(&dictionaryNotEnc);
	printf("Hello, this programm will break the caesar cipher\n");
	printf("You need two files: One with any decrypted text and one with crypted text\n\n");
	pause();
	while (1) {
		system("cls");
		menuInformation();
		while (((scanf(" %d", &userInput)) != 1 || getchar() != '\n') || (userInput < 1 || userInput > 2)) {
			printf("Invalid input. Please, enter correct number: ");
			rewind(stdin);
		}
		if (userInput == BREAK) {
			system("cls");
			printf("--------------Not encrypted file--------------\n\n");
			freqAnalysis(&dictionaryNotEnc, &pathNotEnc);
			system("cls");
			printf("----------------Encrypted file----------------\n\n");
			freqAnalysis(&dictionaryEnc, &pathEnc);
			system("cls");
			mostFrequentWord = findMostPopular(dictionaryNotEnc);
			qsort(dictionaryEnc, ALPHABET_SIZE, sizeof(FreqDict), compareFreq);
			checkAnalysis(mostFrequentWord, dictionaryEnc, pathEnc);
			nullFreqDict(&dictionaryNotEnc);
			nullFreqDict(&dictionaryEnc);
		}
		else if (userInput == EXIT){
			free(dictionaryNotEnc);
			free(dictionaryEnc);
			free(pathNotEnc);
			free(pathEnc);
			system("cls");
			printf("Bye!");
			exit(0);
		}
		else {
			printf("Unexpected error. Try again");
			exit(1);
		}
	}
}