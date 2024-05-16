#include "ring.h"

void push(Node** head, Node** tail) 
{
    if (*head != NULL) 
    {
        Node *temp = (Node*)malloc(sizeof(Node));
        temp->message = (Message*)malloc(sizeof(Message));
        init_mes(temp->message);
        temp->next = *head;
        temp->prev = *tail;
        (*tail)->next = temp;
        (*head)->prev = temp;
        *tail = temp;
    } 
    else 
    {
        *head = (Node*)malloc(sizeof(Node));
        (*head)->message = (Message*)malloc(sizeof(Message));
        init_mes((*head)->message);
        (*head)->prev = *head;
        (*head)->next = *head;
        *tail = *head;
    }
}

void pop(Node** head, Node** tail) 
{
    if (*head != NULL) 
    {
        if (*head != *tail) 
        {
            Node *temp = *head;
            (*tail)->next = (*head)->next;
            *head = (*head)->next;
            (*head)->prev = *tail;
            free(temp);
        } else 
        {
            free(*head);
            *head = NULL;
            *tail = NULL;
        }
    }
}

uint16_t hash(uint8_t* data, size_t len) {
    uint16_t hash = 5381;
    int num;

    for (size_t i = 0; i < len; i++) {
        num = data[i];
        hash = ((hash << 5) + hash) + num; //hash * 33 + num
    }

    return hash;
}

void init_mes(Message* message) 
{
    srand(time(NULL));
    const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%%^&*().";

    message->type = rand() % 256;
    message->size = 0;
    while (message->size == 0) {
        message->size = rand() % 257;
    }
    
    for (size_t i = 0; i < message->size; i++) 
    {
        message->data[i] = letters[rand() % 74];
    }

    message->hash = hash(message->data, message->size);
}

void print_mes(Message* mes) 
{
    printf("Type: %d, Hash: %d, Size: %d, Message: %s\n", mes->type, mes->hash, mes->size, mes->data);
}