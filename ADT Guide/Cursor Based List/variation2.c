#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

typedef int List; // In Variation 2, this is the index of the header node

/*------------------- Virtual Heap Operations -------------------*/

// Initialize the virtual heap
void initializeVH(VHeap *V) {
    int i;
    for (i = 0; i < MAX - 1; i++) {
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
    V->avail = 0;
}

// Allocate a space in the heap
int allocSpace(VHeap *V) {
    int idx = V->avail;
    if (idx != -1) {
        V->avail = V->H[idx].next;
    }
    return idx;
}

// Deallocate a space in the heap
void deallocSpace(VHeap *V, int index) {
    if (index >= 0 && index < MAX) {
        V->H[index].next = V->avail;
        V->avail = index;
    }
}

/*------------------- List Operations -------------------*/

// Initialize a list with a header node
void initList(List *L, VHeap *V) {
    *L = allocSpace(V);
    if (*L != -1) {
        V->H[*L].next = -1; // Empty list, header points to none
    }
}

// Insert at the beginning (after header)
int insertFirst(List L, VHeap *V, int elem) {
    int newNode = allocSpace(V);
    if (newNode == -1) return 0;

    V->H[newNode].elem = elem;
    V->H[newNode].next = V->H[L].next;
    V->H[L].next = newNode;

    return 1;
}

// Insert at the end
int insertLast(List L, VHeap *V, int elem) {
    int newNode = allocSpace(V);
    if (newNode == -1) return 0;

    V->H[newNode].elem = elem;
    V->H[newNode].next = -1;

    int curr = L;
    while (V->H[curr].next != -1) {
        curr = V->H[curr].next;
    }
    V->H[curr].next = newNode;
    return 1;
}

// Delete an element
int deleteElem(List L, VHeap *V, int elem) {
    int prev = L;
    int curr = V->H[L].next;

    while (curr != -1 && V->H[curr].elem != elem) {
        prev = curr;
        curr = V->H[curr].next;
    }

    if (curr == -1) return 0; // Not found

    V->H[prev].next = V->H[curr].next;
    deallocSpace(V, curr);

    return 1;
}

// Display list
void display(List L, VHeap V) {
    int curr = V.H[L].next;
    printf("{ ");
    while (curr != -1) {
        printf("%d ", V.H[curr].elem);
        curr = V.H[curr].next;
    }
    printf("}\n");
}

/*------------------- Example -------------------*/
int main() {
    VHeap V;
    List L;

    initializeVH(&V);
    initList(&L, &V);

    insertFirst(L, &V, 10);
    insertLast(L, &V, 20);
    insertFirst(L, &V, 5);
    display(L, V);

    deleteElem(L, &V, 10);
    display(L, V);

    return 0;
}
