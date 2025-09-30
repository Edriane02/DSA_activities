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
    Node* front; // points to last node
    Node* rear;  // points to first node
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

// Check if queue is empty
bool isEmpty(Queue* q) {
    return (q->rear == NULL);
}

// Check if queue is full (LL queue never full unless memory fails)
bool isFull(Queue* q) {
    return false;
}

// Enqueue: insert at REAR (beginning of list)
bool enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Cannot enqueue %d.\n", value);
        return false;
    }
    newNode->data = value;
    newNode->next = q->rear;

    q->rear = newNode;

    if (q->front == NULL) { // first element
        q->front = newNode;
    }
    return true;
}

// Dequeue: remove from FRONT (end of list)
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }

    Node* temp = q->rear;

    // If only one node
    if (q->rear == q->front) {
        int value = temp->data;
        q->rear = q->front = NULL;
        free(temp);
        return value;
    }

    // Traverse until node before front
    while (temp->next != q->front) {
        temp = temp->next;
    }

    int value = q->front->data;
    free(q->front);
    q->front = temp;
    q->front->next = NULL;
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

// Display queue elements (from rear → front)
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements (rear to front):\n");
    Node* curr = q->rear;
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
    display(q);

    enqueue(q, 40);
    display(q);

    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));
    display(q);

    free(q);
    return 0;
}
