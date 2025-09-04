#include <stdio.h>
#include <stdbool.h>
#define MAX 100

typedef struct {
    int elem[MAX];
    int count;
} StaticList;

void initializeStatic(StaticList *L) {
    L->count = 0;
}

bool insertPosStatic(StaticList *L, int data, int pos) {
    int i;
    if (pos < 0 || pos > L->count || L->count == MAX) return false;
    for (i = L->count; i > pos; i--) {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[pos] = data;
    L->count++;
    return true;
}

bool deletePosStatic(StaticList *L, int pos) {
    int i;
    if (pos < 0 || pos >= L->count) return false;
    for (i = pos; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    L->count--;
    return true;
}

int locateStatic(StaticList *L, int data) {
    int i;
    for (i = 0; i < L->count; i++) {
        if (L->elem[i] == data) return i;
    }
    return -1;
}

int retrieveStatic(StaticList *L, int pos) {
    if (pos < 0 || pos >= L->count) return -1;
    return L->elem[pos];
}

bool insertSortedStatic(StaticList *L, int data) {
    int i;
    if (L->count == MAX) return false;
    i = L->count - 1;
    while (i >= 0 && L->elem[i] > data) {
        L->elem[i + 1] = L->elem[i];
        i--;
    }
    L->elem[i + 1] = data;
    L->count++;
    return true;
}

void displayStatic(StaticList *L) {
    int i;
    for (i = 0; i < L->count; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

int main() {
    StaticList S;
    initializeStatic(&S);
    insertPosStatic(&S, 3, 0);
    insertPosStatic(&S, 1, 1);
    insertSortedStatic(&S, 2);
    displayStatic(&S);
    return 0;
}

