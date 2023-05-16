#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "tree.h"
#include "files.h"
#include "logs.h"

void menuInformation(void) {
	printf("LABA4 By Pavel Kazachenko\n");
	printf("---------MENU---------\n");
	printf("1) Play Akinator\n");
	printf("2) Save tree to file\n");
	printf("3) Import tree from file\n");
	printf("4) Exit\n");
	printf("----------------------\n");
	printf("Your choice: ");
}

void mainMenu(struct binaryTree** tree) {
	int userInput;
	char answer;
	char* temp = (char*)malloc(256);
	char* fileName = (char*)malloc(256);
	FILE* fp;
	FILE* logPointer;
	createLog(&logPointer);
	while (1) {
		menuInformation();
		while (((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n') || (userInput < 0 || userInput > 4)) {
			printf("Invalid input. Please, enter correct number: ");
			createMessage(&logPointer, "[WARN] User entered invalid input in menu");
			rewind(stdin);
		}
		switch (userInput) {
		case 1:
			createMessage(&logPointer, "[INFO] User choosed 1 option in menu");
			if (*tree == NULL) {
				printf("Who will be the first person in our game?\nAnswer: ");
				//fgets(temp, 256, stdin);
				//temp[strlen(temp) - 1] = '\0';
				getString(temp);
				while (atoi(temp) == 1) {
					createMessage(&logPointer, "[WARN] User entered reserved word");
					printf("It's a reserved word. Enter correct object: ");
					getString(temp);
				}
				*tree = createNode(temp, logPointer);
				createAddMessage(&logPointer, "[INFO] Object user added to tree: ", temp);
				free(temp);
				temp = NULL;
			}
			push(tree, &answer, logPointer);
			break;
		case 2:
			createMessage(&logPointer, "[INFO] User choosed 2 option in menu");
			getPath(&fp, fileName, "w", logPointer);
			serialize(tree, fp);
			createAddMessage(&logPointer, "[INFO] User saved base as file: ", fileName);
			printf("Saving...");
			//Sleep(2000);
			system("cls");
			fclose(fp);
			break;
		case 3:
			createMessage(&logPointer, "[INFO] User choosed 3 option in menu");
			deleteTree(tree);
			*tree = NULL;
			getPath(&fp, fileName, "r", logPointer);
			deserialize(tree, fp, logPointer);
			createAddMessage(&logPointer, "[INFO] User imported base from file: ", fileName);
			printf("Importing...");
			//Sleep(2000);
			system("cls");
			fclose(fp);
			break;
		case 4:
			createMessage(&logPointer, "[INFO] User exit");
			system("cls");
			printf("Bye : (");
			if (temp != NULL) {
				free(temp);
			}
			free(fileName);
			fclose(logPointer);
			exit(0);
			break;
		default:
			break;
		}
	}
}