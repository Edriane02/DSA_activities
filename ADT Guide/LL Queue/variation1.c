#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialize the queue
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = NULL;
        q->rear = NULL;
    }
    return q;
}

// Check if queue is full (never full in LL implementation)
bool isFull(Queue* q) {
    return false; // unless memory runs out
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    return (q->front == NULL);
}

// Enqueue operation (insert at rear)
bool enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Cannot enqueue %d.\n", value);
        return false;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return true;
}

// Dequeue operation (remove from front)
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }

    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL; // queue became empty
    }

    free(temp);
    return value;
}

// Peek at the front element
int frontVal(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Nothing at front.\n");
        return -1;
    }
    return q->front->data;
}

// Display elements
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements (front to rear):\n");
    Node* curr = q->front;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    Queue* q = initialize();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    display(q);

    printf("Front: %d\n", frontVal(q));

    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));

    display(q);

    enqueue(q, 40);
    enqueue(q, 50);

    display(q);

    free(q); // only free the Queue struct (nodes freed on dequeue)
    return 0;
}