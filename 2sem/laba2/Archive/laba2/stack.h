#pragma once

typedef struct StackNode {
	char* word;
	void* data; //указатель на данные элемента (в нашем случае кол-во повторений слова)
	struct StackNode* nextElement;
} StackNode;

StackNode* pushStackNode(StackNode* topOfStack);
StackNode* popStackNode(StackNode* topOfStack);
void setStackNodeWord(StackNode* topOfStack, char* word);
void setStackNodeData(StackNode* topOfStack, void* data, size_t size);
void freeStack(StackNode* topOfStack);