#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 8
typedef bool Set[ARRAY_SIZE];

// Initialize set (all false)
void initialize(Set set) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        set[i] = false;
    }
}

// Insert element
bool insert(Set set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Element %d out of range (0–%d)\n", element, ARRAY_SIZE - 1);
        return false;
    }
    set[element] = true;
    return true;
}

// Delete element
bool delete(Set set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Element %d out of range (0–%d)\n", element, ARRAY_SIZE - 1);
        return false;
    }
    set[element] = false;
    return true;
}

// Find element
bool find(Set set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        return false;
    }
    return set[element];
}

// Union of two sets -> result in C
void setUnion(Set A, Set B, Set C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] || B[i];
    }
}

// Intersection of two sets -> result in C
void setIntersection(Set A, Set B, Set C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] && B[i];
    }
}

// Difference of two sets (A - B) -> result in C
void setDifference(Set A, Set B, Set C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] && !B[i];
    }
}

// Display set contents
void display(Set set) {
    printf("{ ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (set[i]) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}


int main() {
    Set A, B, C;

    initialize(A);
    initialize(B);
    initialize(C);

    insert(A, 1);
    insert(A, 3);
    insert(A, 5);

    insert(B, 3);
    insert(B, 4);
    insert(B, 7);

    printf("Set A: ");
    display(A);

    printf("Set B: ");
    display(B);

    setUnion(A, B, C);
    printf("Union: ");
    display(C);

    setIntersection(A, B, C);
    printf("Intersection: ");
    display(C);

    setDifference(A, B, C);
    printf("Difference (A - B): ");
    display(C);

    printf("Find 5 in A? %s\n", find(A, 5) ? "Yes" : "No");
    printf("Find 7 in A? %s\n", find(A, 7) ? "Yes" : "No");

    delete(A, 3);
    printf("Set A after deleting 3: ");
    display(A);

    return 0;
}
