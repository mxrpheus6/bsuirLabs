#include "menu.h"

void menuInformation(void) {
	printf("LABA5 By Pavel Kazachenko\n");
	printf("---------MENU---------\n");
	printf("1) Enter domen\n");
	printf("2) Print cache\n");
	printf("3) Exit\n");
	printf("----------------------\n");
	printf("Your choice: ");
}

void mainMenu(Cache* cache) {
	int userInput;
	char* temp = malloc(STRING_SIZE);
	char* cacheSearchResult = (char*)malloc(STRING_SIZE);
	while (1) {
		menuInformation();
		while (((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n') || (userInput < 1 || userInput > 3)) {
			printf("Invalid input. Please, enter correct number: ");
			rewind(stdin);
		}
		switch (userInput) {
		case 1:
			printf("Input domain: ");
			fgets(temp, STRING_SIZE, stdin);
			temp[strlen(temp) - 1] = '\0';

			cacheSearchResult = cacheSearch(cache, temp);

			if (cacheSearchResult != NULL)
				printf("Found IP-adress: %s\n\n", cacheSearchResult);
			//Sleep(4000);
			system("cls");
			break;
		case 2:
			printf("\nCache:\n");
			printCache(cache);
			//Sleep(5000);
			system("cls");
			break;
		case 3:
			system("cls");
			printf("Bye!");
			freeDoubleLinkedList(cache);
			exit(0);
			break;
		default:
			break;
		}
	}
}