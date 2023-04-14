struct binaryTree {
	char* data;
	struct binaryTree* left;
	struct binaryTree* right;
};

struct binaryTree* createNode(char* data);
void push(struct binaryTree** tree, char* answer);
void printDepth(struct binaryTree* tree);