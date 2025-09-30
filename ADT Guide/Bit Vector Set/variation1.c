#include <stdio.h>
#include <stdbool.h>

// Each unsigned char = 8 bits, so this set can represent elements {0..7}
typedef unsigned char BitSet;

// Initialize the set (set all bits to 0)
void initialize(BitSet *set) {
    *set = 0;
}

// Insert an element
bool insert(BitSet *set, int element) {
    if (element < 0 || element >= 8) {
        printf("Element %d out of range (0–7).\n", element);
        return false;
    }
    *set |= (1 << element);
    return true;
}

// Delete an element
bool delete(BitSet *set, int element) {
    if (element < 0 || element >= 8) {
        printf("Element %d out of range (0–7).\n", element);
        return false;
    }
    *set &= ~(1 << element);
    return true;
}

// Find an element
bool find(BitSet set, int element) {
    if (element < 0 || element >= 8) {
        return false;
    }
    return (set & (1 << element)) != 0;
}

// Union of two sets
BitSet setUnion(BitSet A, BitSet B) {
    return (A | B);
}

// Intersection of two sets
BitSet setIntersection(BitSet A, BitSet B) {
    return (A & B);
}

// Difference of two sets (A - B)
BitSet setDifference(BitSet A, BitSet B) {
    return (A & ~B);
}

// Display set elements
void display(BitSet set) {
    printf("{ ");
    for (int i = 0; i < 8; i++) {
        if (set & (1 << i)) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}

int main() {
    BitSet A, B;

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
