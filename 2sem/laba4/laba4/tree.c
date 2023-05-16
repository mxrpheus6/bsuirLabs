#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "logs.h"

#define NULL_MARKER 1
#define BUF_SIZE 256

struct binaryTree* createNode(const char* data, FILE* logPointer) {
	struct binaryTree* newNode = (struct binaryTree*)malloc(sizeof(struct binaryTree));
	if (newNode == NULL) {
		createMessage(&logPointer, "[ERROR] Memory allocation for new node failed");
		printf("Memory allocation failed. Try again.");
		exit(1);
	}
	newNode->data = (char*)malloc(strlen(data) + 1);
	strcpy(newNode->data, data);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct binaryTree* show(struct binaryTree** tree, FILE* logPointer) {
	char answer;

	if ((*tree)->left == NULL && (*tree)->right == NULL) {
		return *tree;
	}
	createAddMessage(&logPointer, "[INFO] User answering question: ", (*tree)->data);
	printf("%s\nAnswer (y\\n): ", (*tree)->data);
	while ((scanf_s(" %c", &answer, 1)) != 1 || getchar() != '\n' || (answer != 'y' && answer != 'n')) {
		createMessage(&logPointer, "[WARN] User entered invalid input while answering (y\\n)");
		printf("Invalid input. Please, enter correct answer (y\\n): ");
		rewind(stdin);
	}
	if (answer == 'y') {
		createMessage(&logPointer, "[INFO] User choosed 'y'");
		show(&(*tree)->left, logPointer);
	}
	else if (answer == 'n') {
		createMessage(&logPointer, "[INFO] User choosed 'n'");
		show(&(*tree)->right, logPointer);
	}
		
}

void push(struct binaryTree** tree, char* answer, FILE* logPointer) {
	char* playerNew = (char*)malloc(256);
	char* playerOld = (char*)malloc(256);
	char* question = (char*)malloc(256);

	struct binaryTree* temp = show(tree, logPointer);
	printf("Is it %s?\nAnswer (y\\n): ", temp->data);
	createAddMessage(&logPointer, "[INFO] Answer of the program is ", temp->data);
	while ((scanf_s(" %c", answer, 1)) != 1 || getchar() != '\n' || (*answer != 'y' && *answer != 'n')) {
		createMessage(&logPointer, "[WARN] User entered invalid input while answering (y\\n)");
		printf("Invalid input. Please, enter correct answer (y\\n): ");
		rewind(stdin);
	}
	if (*answer == 'y') {
		createMessage(&logPointer, "[INFO] Program win");
		printf("Haha now i won you!");
		//Sleep(2000);
		system("cls");
		return;
	}
	else if (*answer == 'n') {
		createMessage(&logPointer, "[INFO] Program lose");
		printf("Damn I think I've lost. Who is it?\n");
		getString(playerNew);
		while (atoi(playerNew) == 1) {
			createMessage(&logPointer, "[WARN] User entered reserved word");
			printf("It's a reserved word. Enter correct object: ");
			getString(playerNew);
		}
		createAddMessage(&logPointer, "[INFO] Object user added to tree: ", playerNew);
		strcpy(playerOld, temp->data);

		printf("Please, write distinctive question for your person: ");
		getString(question);
		while (atoi(question) == 1) {
			createMessage(&logPointer, "[WARN] User entered reserved word");
			printf("It's a reserved word. Enter correct question: ");
			getString(question);
		}
		createAddMessage(&logPointer, "[INFO] Question user added to tree: ", question);

		temp->left = createNode(playerNew, logPointer);
		temp->right = createNode(playerOld, logPointer);
		temp->data = (char*)realloc(temp->data, strlen(question) + 1);
		strcpy(temp->data, question);

		free(question);
		free(playerNew);
		free(playerOld);

		system("cls");
	}
}

void serialize(struct binaryTree** tree, FILE* fp) {
	if (*tree == NULL) {
		fprintf(fp, "%d\n", NULL_MARKER);
		return;
	}
	fprintf(fp, "%s\n", (*tree)->data);
	serialize(&(*tree)->left, fp);
	serialize(&(*tree)->right, fp);
}

void deserialize(struct binaryTree** tree, FILE* fp, FILE* logPointer) {
	char buf[BUF_SIZE];

	if (fgets(buf, BUF_SIZE, fp) == NULL || atoi(buf) == 1)
		return;

	buf[strlen(buf) - 1] = '\0';
	*tree = createNode(buf, logPointer);
	deserialize(&(*tree)->left, fp, logPointer);
	deserialize(&(*tree)->right, fp, logPointer);
}

void deleteTree(struct binaryTree** tree) {
	if (*tree == NULL) {
		return;
	}
	deleteTree(&(*tree)->left);
	deleteTree(&(*tree)->right);
	free((*tree)->data);
	free(*tree);
}