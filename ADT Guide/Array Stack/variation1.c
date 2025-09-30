#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

// Initialize the stack
Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = -1;
    }
    return s;
}

// Check if stack is full
bool isFull(Stack* s) {
    return (s->top == MAX - 1);
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return (s->top == -1);
}

// Push an element onto the stack
bool push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow! Cannot push %d.\n", value);
        return false;
    }
    s->items[++(s->top)] = value;
    return true;
}

// Pop an element from the stack
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow! Cannot pop.\n");
        return -1; // Or handle error differently
    }
    return s->items[(s->top)--];
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

// Display the stack contents
void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = s->top; i >= 0; i--) {
        printf("%d\n", s->items[i]);
    }
}


int main() {
    Stack* s = initialize();

    push(s, 10);
    push(s, 20);
    push(s, 30);
    push(s, 34);

    display(s);

    printf("Peek: %d\n", peek(s));
    printf("Pop: %d\n", pop(s));
    printf("Pop: %d\n", pop(s));

    display(s);

    printf("Top index: %d\n", top(s));

    free(s); // Free allocated memory
    return 0;
}
