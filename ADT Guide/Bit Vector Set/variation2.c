#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int field : 8;  // can store 8 elements (0–7)
} Set;

// Initialize the set (clear all bits)
void initialize(Set *set) {
    set->field = 0;
}

// Insert an element
bool insert(Set *set, int element) {
    if (element < 0 || element >= 8) {
        printf("Element %d out of range (0–7)\n", element);
        return false;
    }
    set->field |= (1 << element);
    return true;
}

// Delete an element
bool delete(Set *set, int element) {
    if (element < 0 || element >= 8) {
        printf("Element %d out of range (0–7)\n", element);
        return false;
    }
    set->field &= ~(1 << element);
    return true;
}

// Find an element
bool find(Set set, int element) {
    if (element < 0 || element >= 8) {
        return false;
    }
    return (set.field & (1 << element)) != 0;
}

// Union of two sets
Set setUnion(Set A, Set B) {
    Set result;
    result.field = A.field | B.field;
    return result;
}

// Intersection of two sets
Set setIntersection(Set A, Set B) {
    Set result;
    result.field = A.field & B.field;
    return result;
}

// Difference of two sets (A - B)
Set setDifference(Set A, Set B) {
    Set result;
    result.field = A.field & ~(B.field);
    return result;
}

// Display the set
void display(Set set) {
    printf("{ ");
    for (int i = 0; i < 8; i++) {
        if (set.field & (1 << i)) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}

int main() {
    Set A, B;

    initialize(&A);
    initialize(&B);

    insert(&A, 1);
    insert(&A, 3);
    insert(&A, 5);

    insert(&B, 3);
    insert(&B, 4);
    insert(&B, 7);

    printf("Set A: ");
    display(A);

    printf("Set B: ");
    display(B);

    printf("Union: ");
    display(setUnion(A, B));

    printf("Intersection: ");
    display(setIntersection(A, B));

    printf("Difference (A - B): ");
    display(setDifference(A, B));

    printf("Find 5 in A? %s\n", find(A, 5) ? "Yes" : "No");
    printf("Find 7 in A? %s\n", find(A, 7) ? "Yes" : "No");

    delete(&A, 3);
    printf("Set A after deleting 3: ");
    display(A);

    return 0;
}
