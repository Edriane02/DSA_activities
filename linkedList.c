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

// Function prototypes
List* initialize();
bool empty(List *list);
bool insertFirst(List *list, int data);
bool insertLast(List *list, int data);
bool insertPos(List *list, int data, int index);
bool deleteStart(List *list);
bool deleteLast(List *list);
bool deletePos(List *list, int index);
bool retrieve(List *list, int index, int *outData);
int locate(List *list, int data);
void display(List *list);

// Initialize a new list
List* initialize() {
    List *list = (List*) malloc(sizeof(List));
    if (!list) return NULL;
    list->head = NULL;
    list->count = 0;
    return list;
}

// Free all nodes
bool empty(List *list) {
    if (!list) return false;
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
    return true;
}

// Insert at beginning
bool insertFirst(List *list, int data) {
    if (!list) return false;
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
    if (!list) return false;
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

// Insert at position
bool insertPos(List *list, int data, int index) {
	int i;
	
    if (!list || index < 0 || index > list->count) return false;

    if (index == 0) return insertFirst(list, data);
    if (index == list->count) return insertLast(list, data);

    Node *newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) return false;

    newNode->data = data;

    Node *current = list->head;
    for (i = 0; i < index - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    list->count++;
    return true;
}

// Delete from start
bool deleteStart(List *list) {
    if (!list || list->head == NULL) return false;

    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->count--;
    return true;
}

// Delete from end
bool deleteLast(List *list) {
    if (!list || list->head == NULL) return false;

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

// Delete at position
bool deletePos(List *list, int index) {
	
	int i;
	
    if (!list || index < 0 || index >= list->count) return false;

    if (index == 0) return deleteStart(list);

    Node *current = list->head;
    for (i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->count--;
    return true;
}

// Retrieve data at index (output via pointer)
bool retrieve(List *list, int index, int *outData) {
	
	int i;
	
    if (!list || index < 0 || index >= list->count) return false;

    Node *current = list->head;
    for (i = 0; i < index; i++) {
        current = current->next;
    }
    *outData = current->data;
    return true;
}

// Locate index of data
int locate(List *list, int data) {
    if (!list) return -1;

    Node *current = list->head;
    int index = 0;
    while (current) {
        if (current->data == data) return index;
        current = current->next;
        index++;
    }
    return -1;
}

// Display list contents
void display(List *list) {
    if (!list) return;
    Node *current = list->head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Example usage
int main() {
    List *list = initialize();

    insertFirst(list, 5);
    insertFirst(list, 6);
    insertLast(list, 7);
    insertPos(list, 8, 1);

    printf("List after insertions: ");
    display(list);

    deleteStart(list);
    deleteLast(list);
    deletePos(list, 1);

    printf("List after deletions: ");
    display(list);

    int value;
    if (retrieve(list, 0, &value))
        printf("Retrieve index 0: %d\n", value);
    else
        printf("Retrieve failed!\n");

    printf("Locate value 5: %d\n", locate(list, 5));

    empty(list);
    free(list);

    return 0;
}

