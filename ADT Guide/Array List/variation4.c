#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LENGTH 10

typedef struct {
    int *elem;
    int count;
    int max;
} DynamicList;

void initializeDynamic(DynamicList *L) {
    L->elem = (int*) malloc(LENGTH * sizeof(int));
    L->count = 0;
    L->max = LENGTH;
}

void resize(DynamicList *L) {
    L->max *= 2;
    L->elem = (int*) realloc(L->elem, L->max * sizeof(int));
}

bool insertPos(DynamicList *L, int data, int pos) {
    int i;
    if (pos < 0 || pos > L->count) return false;
    if (L->count == L->max) resize(L);
    for (i = L->count; i > pos; i--) {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[pos] = data;
    L->count++;
    return true;
}

bool deletePos(DynamicList *L, int pos) {
    int i;
    if (pos < 0 || pos >= L->count) return false;
    for (i = pos; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    L->count--;
    return true;
}

int locate(DynamicList *L, int data) {
    int i;
    for (i = 0; i < L->count; i++) {
        if (L->elem[i] == data) return i;
    }
    return -1;
}

int retrieve(DynamicList *L, int pos) {
    if (pos < 0 || pos >= L->count) return -1;
    return L->elem[pos];
}

bool insertSorted(DynamicList *L, int data) {
    int i;
    if (L->count == L->max) resize(L);
    i = L->count - 1;
    while (i >= 0 && L->elem[i] > data) {
        L->elem[i + 1] = L->elem[i];
        i--;
    }
    L->elem[i + 1] = data;
    L->count++;
    return true;
}

void display(DynamicList *L) {
    int i;
    for (i = 0; i < L->count; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

void makeNULL(DynamicList *L) {
    free(L->elem);
    L->elem = NULL;
    L->count = 0;
    L->max = 0;
}

int main() {
    DynamicList L;
    initializeDynamic(&L);
    insertPos(&L, 4, 0);
    insertPos(&L, 6, 1);
    insertSorted(&L, 5);
    display(&L);
    makeNULL(&L);
    return 0;
}

