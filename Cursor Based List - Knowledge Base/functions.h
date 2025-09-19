#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// initVHeap

// alloc

// dealloc

// insertArticle

// viewArticles

// searchArticle

// deleteArticle


// Initialize the Virtual Heap
void initVHeap(VHeap *vh) {
    int i;
    for (i = 0; i < MAX_SIZE - 1; i++) {
        vh->H[i].next = i + 1;
    }
    vh->H[MAX_SIZE - 1].next = -1;
    vh->avail = 0;
}

// Allocate a cell
int alloc(VHeap *vh) {
    int idx = vh->avail;
    if (idx != -1) {
        vh->avail = vh->H[idx].next;
    }
    return idx;
}

// Deallocate a cell
void dealloc(VHeap *vh, int idx) {
    if (idx >= 0 && idx < MAX_SIZE) {
        vh->H[idx].next = vh->avail;
        vh->avail = idx;
    }
}

// Insert new article
int insertArticle(VHeap *vh, int *list, Article a, int pos) {
    int newNode = alloc(vh);
    if (newNode == -1) {
        printf("Error: Heap is full. Cannot insert new article.\n");
        return 0;
    }

    vh->H[newNode].article = a;
    vh->H[newNode].next = -1;

    // Empty list
    if (*list == -1) {
        *list = newNode;
        return 1;
    }

    // Insert at beginning
    if (pos == 0) {
        vh->H[newNode].next = *list;
        *list = newNode;
        return 1;
    }

    // Insert at end
    if (pos == -1) {
        int temp = *list;
        while (vh->H[temp].next != -1) {
            temp = vh->H[temp].next;
        }
        vh->H[temp].next = newNode;
        return 1;
    }

    // Insert at position
    int prev = *list;
    int i;
    for (i = 0; i < pos - 1 && prev != -1; i++) {
        prev = vh->H[prev].next;
    }

    if (prev == -1) {
        printf("Invalid position!\n");
        dealloc(vh, newNode);
        return 0;
    }

    vh->H[newNode].next = vh->H[prev].next;
    vh->H[prev].next = newNode;
    return 1;
}

// View all articles
void viewArticles(VHeap vh, int list) {
    if (list == -1) {
        printf("The knowledge base is empty.\n");
        return;
    }

    int curr = list;
    printf("\n--- List of Articles ---\n");
    while (curr != -1) {
        printf("ID: %d | Title: %s\n", vh.H[curr].article.id, vh.H[curr].article.title);
        curr = vh.H[curr].next;
    }
    printf("------------------------\n\n");
}

// Search for article
void searchArticle(VHeap vh, int list, int id) {
    int curr = list;
    while (curr != -1) {
        if (vh.H[curr].article.id == id) {
            printf("\n--- Article Found ---\n");
            printf("ID: %d\n", vh.H[curr].article.id);
            printf("Title: %s\n", vh.H[curr].article.title);
            printf("Content: %s\n", vh.H[curr].article.content);
            printf("---------------------\n\n");
            return;
        }
        curr = vh.H[curr].next;
    }
    printf("Article with ID %d not found.\n\n", id);
}

// Delete an article by ID
int deleteArticle(VHeap *vh, int *list, int id) {
    if (*list == -1) {
        printf("The knowledge base is empty.\n");
        return 0;
    }

    int curr = *list;
    int prev = -1;

    while (curr != -1 && vh->H[curr].article.id != id) {
        prev = curr;
        curr = vh->H[curr].next;
    }

    if (curr == -1) {
        printf("Article with ID %d not found.\n\n", id);
        return 0;
    }

    if (prev == -1) { // delete head
        *list = vh->H[curr].next;
    } else {
        vh->H[prev].next = vh->H[curr].next;
    }

    dealloc(vh, curr);
    printf("Article with ID %d deleted successfully.\n\n", id);

    return 1;
}