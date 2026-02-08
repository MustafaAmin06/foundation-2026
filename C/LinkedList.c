#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct list {
    Node* head;
} LinkedList;


Node *createNode(int value){
    Node *newNode = (Node*) (malloc(sizeof(Node)));
    if (newNode != NULL){
        newNode->data = value;
        newNode->next = NULL;
    }
    return newNode;
}

bool insert(LinkedList *list, int value) {
    Node *temp = createNode(value);
    if (temp != NULL){
        temp->next = list->head;
        list->head = temp;
    } else {
        return false;
    }
    return true;
}

bool insertLast(LinkedList *list, int value){
    Node *temp = createNode(value);
    if (temp == NULL){
        return false;
    }
    if (list->head == NULL){
        list->head = temp;
        return true;
    }
    Node *current = list->head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = temp;
    return true;
}

bool pop(LinkedList *list, int value){
    Node *current = list->head;
    Node *prev = NULL;
    if (list->head->data == value){
        list->head = list->head->next;
        current->next = NULL;
        free(current);
        return true;
    }
    while (current != NULL && current->data != value){
        prev = current;
        current = current->next;
    }
    if (current == NULL){
        printf("Value not found");
        return false;
    }
    prev->next = current->next;
    free(current);
    return true;
}


void printList(LinkedList *list){
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(LinkedList *list){
    Node *current = list->head;
    Node *temp_next = NULL;
    while (current != NULL){
        temp_next = current->next;
        free(current);
        current = temp_next;
    }
    list->head = NULL;
}

int main(void){
    LinkedList list;
    list.head = createNode(10);
    (list.head)->next = createNode(5);
    insert(&list, 0);
    insertLast(&list, 9);
    pop(&list, 0);
    printList(&list);
    return 0;
}