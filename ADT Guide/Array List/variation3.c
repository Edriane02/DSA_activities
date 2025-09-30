#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LENGTH 10

typedef struct {
    int *elem;
    int count;
    int max;
} DynamicList;

DynamicList initializeDynamicByValue(DynamicList L) {
    L.elem = (int*) malloc(LENGTH * sizeof(int));
    L.count = 0;
    L.max = LENGTH;
    return L;
}

DynamicList resizeByValue(DynamicList L) {
    L.max *= 2;
    L.elem = (int*) realloc(L.elem, L.max * sizeof(int));
    return L;
}

DynamicList insertPosByValue(DynamicList L, int data, int pos) {
    int i;
    if (pos < 0 || pos > L.count) return L;
    if (L.count == L.max) L = resizeByValue(L);
    for (i = L.count; i > pos; i--) {
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[pos] = data;
    L.count++;
    return L;
}

DynamicList deletePosByValue(DynamicList L, int pos) {
    int i;
    if (pos < 0 || pos >= L.count) return L;
    for (i = pos; i < L.count - 1; i++) {
        L.elem[i] = L.elem[i + 1];
    }
    L.count--;
    return L;
}

int locateByValue(DynamicList L, int data) {
    int i;
    for (i = 0; i < L.count; i++) {
        if (L.elem[i] == data) return i;
    }
    return -1;
}

DynamicList insertSortedByValue(DynamicList L, int data) {
    int i;
    if (L.count == L.max) L = resizeByValue(L);
    i = L.count - 1;
    while (i >= 0 && L.elem[i] > data) {
        L.elem[i + 1] = L.elem[i];
        i--;
    }
    L.elem[i + 1] = data;
    L.count++;
    return L;
}

void displayByValue(DynamicList L) {
    int i;
    for (i = 0; i < L.count; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int main() {
    DynamicList D;
    D = initializeDynamicByValue(D);
    D = insertPosByValue(D, 10, 0);
    D = insertPosByValue(D, 5, 1);
    D = insertSortedByValue(D, 7);
    displayByValue(D);
    free(D.elem);
    return 0;
}

