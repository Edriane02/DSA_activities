#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;   // starts at MAX, moves left as elements are added
} Stack;

// Initialize the stack
Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = MAX;  // empty
    }
    return s;
}

// Check if stack is full
bool isFull(Stack* s) {
    return (s->top == 0);
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return (s->top == MAX);
}

// Push an element (move left)
bool push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow! Cannot push %d.\n", value);
        return false;
    }
    s->items[--(s->top)] = value;  // move left then insert
    return true;
}

// Pop an element (move right)
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow! Cannot pop.\n");
        return -1;
    }
    return s->items[(s->top)++];
}

// Peek at the top element
int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return s->items[s->top];
}

// Get the index of top
int top(Stack* s) {
    return s->top;
}

// Display stack contents
void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = s->top; i < MAX; i++) {
        printf("%d\n", s->items[i]);
    }
}

int main() {
    Stack* s = initialize();

    push(s, 100);
    push(s, 200);
    push(s, 300);

    display(s);

    printf("Peek: %d\n", peek(s));
    printf("Pop: %d\n", pop(s));
    printf("Pop: %d\n", pop(s));

    display(s);

    free(s);
    return 0;
}

