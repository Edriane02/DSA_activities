#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 4

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;  // index of first free cell
} VHeap;

typedef int List; // head of the list (index)

// Initialize virtual heap
void initialize(VHeap* V) {
    for (int i = 0; i < MAX - 1; i++) {
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
    V->avail = 0; // first free cell
}

// Allocate a cell
int allocSpace(VHeap* V) {
    int idx = V->avail;
    if (idx != -1) {
        V->avail = V->H[idx].next;
    }
    return idx;
}

// Deallocate a cell
void deallocSpace(VHeap* V, int index) {
    if (index >= 0 && index < MAX) {
        V->H[index].next = V->avail;
        V->avail = index;
    }
}

// Insert at the beginning
void insertFirst(int* L, VHeap* V, int elem) {
    int newNode = allocSpace(V);
    if (newNode == -1) {
        printf("No available space!\n");
        return;
    }
    V->H[newNode].elem = elem;
    V->H[newNode].next = *L;
    *L = newNode;
}

// Insert at the end
void insertLast(int* L, VHeap* V, int elem) {
    int newNode = allocSpace(V);
    if (newNode == -1) {
        printf("No available space!\n");
        return;
    }
    V->H[newNode].elem = elem;
    V->H[newNode].next = -1;

    if (*L == -1) {
        *L = newNode;
    } else {
        int curr = *L;
        while (V->H[curr].next != -1) {
            curr = V->H[curr].next;
        }
        V->H[curr].next = newNode;
    }
}

// Insert in sorted order
void insertSorted(int* L, VHeap* V, int elem) {
    int newNode = allocSpace(V);
    if (newNode == -1) {
        printf("No available space!\n");
        return;
    }
    V->H[newNode].elem = elem;

    int *trav = L;
    while (*trav != -1 && V->H[*trav].elem < elem) {
        trav = &V->H[*trav].next;
    }
    V->H[newNode].next = *trav;
    *trav = newNode;
}

// Delete first occurrence
void delete(int* L, VHeap* V, int elem) {
    int *trav = L;
    while (*trav != -1 && V->H[*trav].elem != elem) {
        trav = &V->H[*trav].next;
    }
    if (*trav != -1) {
        int delNode = *trav;
        *trav = V->H[delNode].next;
        deallocSpace(V, delNode);
    }
}

// Delete all occurrences
void deleteAllOccurrence(int* L, VHeap* V, int elem) {
    int *trav = L;
    while (*trav != -1) {
        if (V->H[*trav].elem == elem) {
            int delNode = *trav;
            *trav = V->H[delNode].next;
            deallocSpace(V, delNode);
        } else {
            trav = &V->H[*trav].next;
        }
    }
}

// Display list
void display(int L, VHeap V) {
    if (L == -1) {
        printf("List is empty.\n");
        return;
    }
    printf("List elements: ");
    for (int curr = L; curr != -1; curr = V.H[curr].next) {
        printf("%d ", V.H[curr].elem);
    }
    printf("\n");
}


int main() {
    VHeap vh;
    List L = -1;

    initialize(&vh);

    insertFirst(&L, &vh, 10);
    insertFirst(&L, &vh, 5);
    insertLast(&L, &vh, 20);
    insertSorted(&L, &vh, 15);

    display(L, vh);

    delete(&L, &vh, 10);
    display(L, vh);

    insertLast(&L, &vh, 15);
    insertLast(&L, &vh, 15);
    display(L, vh);

    deleteAllOccurrence(&L, &vh, 15);
    display(L, vh);

    return 0;
}