#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Node* create_node(pid_t pid) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->pid = pid;
    node->next = NULL;
    return node;
}

void push_stack(Node** head, pid_t pid) {
    if (head == NULL) {
        exit(EXIT_FAILURE);
    }
    if (*head == NULL) {
        *head = create_node(pid);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = create_node(pid);
}

pid_t pop_stack(Node** head) {
    if (head == NULL) {
        exit(EXIT_FAILURE);
    }
    if (*head == NULL) {
        printf("Nothing to delete. Head is NULL");
        return EXIT_FAILURE;
    }
    
    Node* temp = *head;
    Node* prev = NULL;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    pid_t pid = temp->pid;
    if (prev == NULL) {
        *head = NULL;
    }
    else {
        prev->next = NULL;
    }

    free(temp);
    return pid;
}

void print_stack(Node* head) {
    if (head == NULL) {
        return;
    }

    int child_counter = 0;
    printf("Child%d PID: %d\n", child_counter++, head->pid);
    while (head->next != NULL) {
        head = head->next;
        printf("Child%d PID: %d\n", child_counter++, head->pid);
    }
}

void clear_stack(Node** head) {
    if (head == NULL) {
        return;
    }
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

pid_t get_pid_at_index(Node* head, int index) {
    int counter = 0;
    while (counter < index) {
        head = head->next;
        counter++;
    }
    if (head == NULL) {
        printf("Index out of bounds\n");
        return -1;
    } else {
        return head->pid;
    }
}