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
        printf("You dont have any nodes");
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

void reverseList(LinkedList *list){
    if (list == NULL|| list->head == NULL || list->head->next == NULL){
        return;
    }
    Node *p = list->head;
    Node *c = list->head->next;
    Node *n = list->head->next->next;
    p->next = NULL;
    while(n != NULL){
        c->next = p;
        p = c;
        c = n;
        n = n->next;
    }
    c->next = p;
    list->head = c;
}

int main(void){
    LinkedList list;
    list.head = createNode(0);
    for (int i = 1; i <= 10; i++) {
        insertLast(&list, i);
    }
    printList(&list);
    reverseList(&list);
    printList(&list);
    freeList(&list);
    return 0;
}