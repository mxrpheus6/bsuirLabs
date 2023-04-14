#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

struct binaryTree* createNode(char* data) {
	struct binaryTree* newNode = (struct binaryTree*)malloc(sizeof(struct binaryTree));
	if (newNode == NULL) {
		printf("Memory allocation failed. Try again.");
		exit(1);
	}
	newNode->data = (char*)malloc(strlen(data) + 1);
	strcpy(newNode->data, data);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct binaryTree* show(struct binaryTree** tree) {
	char answer;

	if ((*tree)->left == NULL && (*tree)->right == NULL) {
		return *tree;
	}

	printf("%s\nAnswer (y\\n): ", (*tree)->data);
	scanf_s("%c", &answer);
	rewind(stdin);
	if (answer == 'y')
		show(&(*tree)->left);
	else if (answer == 'n')
		show(&(*tree)->right);
}

void push(struct binaryTree** tree, char* answer) {
	char playerNew[256];
	char playerOld[256];
	char question[256];

	struct binaryTree* temp = show(tree);
	printf("Is it %s?\n", temp->data);
	scanf_s("%c", answer);
	rewind(stdin);
	if (*answer == 'y') {
		printf("Haha i won u fucking bitch");
		exit(666);
	}
	else if (*answer == 'n') {
		printf("damn i think i've lost. who is it?\n");

		fgets(playerNew, 256, stdin);
		strcpy(playerOld, temp->data);
		printf("otlichie?\n");
		fgets(question, 256, stdin);
		playerNew[strlen(playerNew) - 1] = '\0';
		question[strlen(question) - 1] = '\0';

		temp->left = createNode(playerNew);
		temp->right = createNode(playerOld);
		temp->data = (char*)realloc(temp->data, strlen(temp->data) + 1);
		strcpy(temp->data, question);

		printf("So, fuck you.\n");
		system("cls");
	}
}

void printDepth(struct binaryTree* tree) {
	if (tree == NULL) {
		printf("Tree is empty.");
		return;
	}
	else {
		printf("%s", tree->data);
		if (tree->left != NULL) {
			printDepth(tree->left);
		}
		if (tree->right != NULL) {
			printDepth(tree->right);
		}
	}
}