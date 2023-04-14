#include <stdio.h>

#include "tree.h"

int main(void) {
	struct binaryTree* tree = NULL;
	char answer;
	tree = createNode("Michael Jordan");
	while (1) {
		push(&tree, &answer);
	}
	printDepth(tree);
}