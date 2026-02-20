#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
    int size;
} Queue;


Node *createNode(int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->next = NULL;
    }
    return newNode;
}

Queue *createQueue() {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = NULL;
        q->rear  = NULL;
        q->size  = 0;
    }
    return q;
}

bool isEmpty(Queue *q) {
    return q->front == NULL;
}

// Add an element to the rear of the queue
bool enqueue(Queue *q, int value) {
    Node *temp = createNode(value);
    if (temp == NULL) {
        return false;
    }
    if (isEmpty(q)) {
        q->front = temp;
        q->rear  = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->size++;
    return true;
}

// Remove and return the front element
bool dequeue(Queue *q, int *out) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return false;
    }
    Node *temp = q->front;
    *out = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return true;
}

// Return the front element without removing it
bool peek(Queue *q, int *out) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return false;
    }
    *out = q->front->data;
    return true;
}

// Return the rear element without removing it
bool peekRear(Queue *q, int *out) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return false;
    }
    *out = q->rear->data;
    return true;
}

int getSize(Queue *q) {
    return q->size;
}

void printQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    Node *current = q->front;
    printf("Front -> ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("<- Rear\n");
}

void freeQueue(Queue *q) {
    Node *current = q->front;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    q->front = NULL;
    q->rear  = NULL;
    q->size  = 0;
    free(q);
}


int main() {
    Queue *q = createQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);

    printQueue(q);
    printf("Size: %d\n", getSize(q));

    int val;
    if (peek(q, &val))
        printf("Front: %d\n", val);
    if (peekRear(q, &val))
        printf("Rear:  %d\n", val);

    dequeue(q, &val);
    printf("Dequeued: %d\n", val);

    printQueue(q);
    printf("Size: %d\n", getSize(q));

    freeQueue(q);
    return 0;
}
