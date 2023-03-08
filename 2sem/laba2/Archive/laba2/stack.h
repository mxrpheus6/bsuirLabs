#pragma once

typedef struct StackNode {
	char* name;
	int num; //указатель на данные элемента (в нашем случае кол-во повторений слова)
	struct StackNode* nextElement;
} StackNode;

StackNode* pushStackNode(StackNode* topOfStack);
StackNode* popStackNode(StackNode* topOfStack);
void setStackNodeName(StackNode* topOfStack, char* name);
void setStackNodeNum(StackNode* topOfStack, int num);
void freeStack(StackNode* topOfStack);
StackNode* stackCheck(StackNode* topOfStack, char* string);
void initStackFromFile(StackNode** topOfStack, FILE* pointer);
void printStack(StackNode* topOfStack);