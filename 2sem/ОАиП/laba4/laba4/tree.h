struct binaryTree {
	char* data;
	struct binaryTree* left;
	struct binaryTree* right;
};

struct binaryTree* createNode(char* data, FILE* logPointer);
void push(struct binaryTree** tree, char* answer, FILE* logPointer);
void serialize(struct binaryTree** tree, FILE* fp);
void deserialize(struct binaryTree** tree, FILE* fp, FILE* logPointer);
void deleteTree(struct binaryTree** tree);