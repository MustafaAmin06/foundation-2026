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
    
    // Handle empty list
    if (list->head == NULL){
        list->head = temp;
        return true;
    }
    
    // Traverse to the last node
    Node *current = list->head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = temp;
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


int main(void){
    LinkedList list;
    list.head = createNode(10);
    (list.head)->next = createNode(5);
    insert(&list, 0);
    insertLast(&list, 9);
    printList(&list);
    return 0;
}