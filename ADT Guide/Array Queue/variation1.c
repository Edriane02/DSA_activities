#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List *list;
    int front;
    int rear;
} Queue;

// Initialize the queue
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q != NULL) {
        q->list = (List*)malloc(sizeof(List));
        q->list->count = 0;
        q->front = -1;
        q->rear = -1;
    }
    return q;
}

// Check if queue is full
bool isFull(Queue* q) {
    return (q->list->count == MAX);
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    return (q->list->count == 0);
}

// Enqueue operation
bool enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue overflow! Cannot enqueue %d.\n", value);
        return false;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->list->items[q->rear] = value;
    q->list->count++;
    return true;
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }

    int value = q->list->items[q->front];

    if (q->list->count == 1) {  // last element
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    q->list->count--;
    return value;
}

// Peek front element
int frontVal(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Nothing at front.\n");
        return -1;
    }
    return q->list->items[q->front];
}

// Display elements
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements (front to rear):\n");
    int i, idx;
    for (i = 0, idx = q->front; i < q->list->count; i++) {
        printf("%d ", q->list->items[idx]);
        idx = (idx + 1) % MAX;
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

    free(q->list);
    free(q);
    return 0;
}