#include <stdio.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} Etype, *EPtr;

void initializeStatic(EPtr L) {
    L->count = 0;
}

bool insertPosStatic(EPtr L, int data, int pos) {

    int i;

    if (pos < 0 || pos > L->count || L->count == MAX) return false;
    for (i = L->count; i > pos; i--) {
        L->elem[i] = L->elem[i - 1];
    }

    L->elem[pos] = data;
    L->count++;
    return true;
}

bool deletePosStatic(EPtr L, int pos) {
    int i;
    if (pos < 0 || pos > L->count) return false;
    for (i = pos; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }

    L->count--;
    return true;
}

int locateStatic(EPtr L, int data) {
    int i;
    for (i = 0; i < L->count; i++) {
        if (L->elem[i] == data) return i;
    }
    return -1;
}

int retrieveStatic(EPtr L, int pos) {
    if (pos < 0 || pos > L->count) return -1;
    return L->elem[pos];
}

bool insertSortedStatic(EPtr L, int data) {
    int i;
    if (L->count == MAX) return false;

    for( i = L->count - 1; i >= 0 && L->elem[i] > data; i--){
        L->elem[i + 1] = L->elem[i];
    }

    
    L->elem[i + 1] = data;
    L->count++;
    return true;
}

void displayStatic(EPtr L) {
    int i;
    printf("List contents: ");
    for (i = 0; i < L->count; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("(count: %d)\n", L->count);
}

int main() {
    Etype L;  // Changed from StaticList S to Etype L
    initializeStatic(&L);
    
    printf("Testing Static List Implementation\n");
    printf("========================\n");
    
    // Test insertions
    insertPosStatic(&L, 3, 0);
    printf("After inserting 3 at position 0: ");
    displayStatic(&L);
    
    insertPosStatic(&L, 1, 1);
    printf("After inserting 1 at position 1: ");
    displayStatic(&L);
    
    insertSortedStatic(&L, 2);
    printf("After inserting 2 in sorted order: ");
    displayStatic(&L);
    
    // Additional tests
    printf("\nTesting other operations:\n");
    printf("Location of element 2: %d\n", locateStatic(&L, 2));
    printf("Element at position 1: %d\n", retrieveStatic(&L, 1));
    
    deletePosStatic(&L, 0);
    printf("After deleting element at position 0: ");
    displayStatic(&L);
    
    return 0;
}

