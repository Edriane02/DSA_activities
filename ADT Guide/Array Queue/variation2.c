#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

// Initialize the queue
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = 1; // sacrificial space before front
        q->rear = 0;
    }
    return q;
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    return (q->front == (q->rear + 1) % MAX);
}

// Check if queue is full
bool isFull(Queue* q) {
    return (q->front == (q->rear + 2) % MAX);
}

// Enqueue operation
bool enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue overflow! Cannot enqueue %d.\n", value);
        return false;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    return true;
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    return value;
}

// Peek at the front element
int frontVal(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Nothing at front.\n");
        return -1;
    }
    return q->items[q->front];
}

// Display elements
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements (front to rear):\n");
    int i = q->front;
    while (i != (q->rear + 1) % MAX) {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}


int main() {
    Queue* q = initialize();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);

    display(q);

    printf("Front: %d\n", frontVal(q));
    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));

    display(q);

    enqueue(q, 50);
    enqueue(q, 60);
    display(q);

    free(q);
    return 0;
}