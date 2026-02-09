#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct list{
    Node* head;
} LinkedList;

Node *createNode(int value){
    Node *newNode = (Node*) (malloc(sizeof(Node)));
    if (newNode != NULL){
        newNode->data = value;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}

bool insertFront(LinkedList *list, int value){
    Node *temp = createNode(value);
    if (temp == NULL){
        return false;
    }
    temp->next = list->head;
    if (list->head != NULL){
        list->head->prev = temp;
    }
    list->head = temp;
    return true;
}

bool insertEnd(LinkedList *list, int value){
    Node *temp = createNode(value);
    Node *current = list->head;
    if (temp == NULL){
        return false;
    }
    while (current->next != NULL){
        current = current->next;
    }
    temp->prev = current;
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

bool printListBackwards(LinkedList *list){
    Node *current = list->head;
    if (current == NULL){
        return false;
    }
    while (current->next != NULL){
        current = current->next;
    }
    while (current != NULL){
        printf("%d ", current->data);
        current = current->prev;
    }
    return true;
}

bool deleteNode(LinkedList *list, int value){
    Node *current = list->head;
    
    // Empty list
    if (current == NULL){
        return false;
    }
    
    // Deleting head node
    if (current->data == value){
        list->head = current->next;
        if (list->head != NULL){
            list->head->prev = NULL;
        }
        free(current);
        return true;
    }
    
    // Search for the node
    while (current != NULL && current->data != value){
        current = current->next;
    }
    
    // Node not found
    if (current == NULL){
        return false;
    }
    
    // Delete middle or last node
    current->prev->next = current->next;
    if (current->next != NULL){
        current->next->prev = current->prev;
    }
    free(current);
    return true;
}

int main(void){
    LinkedList list;
    list.head = createNode(1);
    insertFront(&list, 0);
    insertEnd(&list, 7);
    printList(&list);
    return 0;
}