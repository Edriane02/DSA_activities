#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Stack structure
typedef struct Stack {
    Node* top;
} Stack;

// Initialize the stack
Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = NULL;
    }
    return s;
}

// Check if stack is full (always false for LL implementation)
bool isFull(Stack* s) {
    return false; // unless memory runs out
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return (s->top == NULL);
}

// Push a value onto the stack
bool push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Cannot push %d.\n", value);
        return false;
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    return true;
}

// Pop a value from the stack
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow! Cannot pop.\n");
        return -1;
    }
    Node* temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);
    return value;
}

// Peek at the top element
int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return s->top->data;
}

// Display stack contents
void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    Node* curr = s->top;
    while (curr != NULL) {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
}

int main() {
    Stack* s = initialize();

    push(s, 10);
    push(s, 20);
    push(s, 30);

    display(s);

    printf("Peek: %d\n", peek(s));
    printf("Pop: %d\n", pop(s));
    printf("Pop: %d\n", pop(s));

    display(s);

    free(s); // Free stack structure (nodes already freed by pop)
    return 0;
}