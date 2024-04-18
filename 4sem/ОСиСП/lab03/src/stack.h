#include <sys/types.h>

typedef struct Node {
    pid_t pid;
    struct Node *next;
} Node;

Node* create_node(pid_t pid);
void push_stack(Node** head, pid_t pid);
pid_t pop_stack(Node** head);
void print_stack(Node* head);
void clear_stack(Node** head);
pid_t get_pid_at_index(Node* head, int index);