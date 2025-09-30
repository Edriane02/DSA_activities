#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// List structure
typedef struct {
    Node *head;
    int count;
} List;

// Initialize a new list
List initialize() {
    List list;
    list.head = NULL;
    list.count = 0;
    return list;
}

// Empty the list (free all nodes)
void empty(List *list) {
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}

// Insert at beginning
bool insertFirst(List *list, int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) return false;

    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
    return true;
}

// Insert at end
bool insertLast(List *list, int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) return false;

    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->count++;
    return true;
}

// Insert at specific position
bool insertPos(List *list, int data, int index) {
    if (index < 0 || index > list->count) return false;

    if (index == 0) {
        return insertFirst(list, data);
    } else if (index == list->count) {
        return insertLast(list, data);
    } else {
        Node *newNode = (Node*) malloc(sizeof(Node));
        if (!newNode) return false;

        newNode->data = data;
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        list->count++;
        return true;
    }
}

// Delete from start
bool deleteStart(List *list) {
    if (list->head == NULL) return false;

    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->count--;
    return true;
}

// Delete from end
bool deleteLast(List *list) {
    if (list->head == NULL) return false;

    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
    } else {
        Node *current = list->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
    list->count--;
    return true;
}

// Delete at specific position
bool deletePos(List *list, int index) {
    if (index < 0 || index >= list->count) return false;

    if (index == 0) {
        return deleteStart(list);
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
        list->count--;
        return true;
    }
}

// Retrieve data at index
int retrieve(List list, int index) {
    if (index < 0 || index >= list.count) {
        printf("Invalid index!\n");
        return -1;
    }
    Node *current = list.head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

// Locate index of a value
int locate(List list, int data) {
    Node *current = list.head;
    int index = 0;
    while (current) {
        if (current->data == data) return index;
        current = current->next;
        index++;
    }
    return -1;
}

// Display list
void display(List list) {
    Node *current = list.head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Example usage
int main() {
    List myList = initialize();

    insertFirst(&myList, 5);
    insertFirst(&myList, 6);
    insertLast(&myList, 7);
    insertPos(&myList, 8, 1);

    printf("List after insertions: ");
    display(myList);

    deleteStart(&myList);
    deleteLast(&myList);
    deletePos(&myList, 1);

    printf("List after deletions: ");
    display(myList);

    printf("Retrieve index 0: %d\n", retrieve(myList, 0));
    printf("Locate value 5: %d\n", locate(myList, 5));

    empty(&myList);
    return 0;
}
