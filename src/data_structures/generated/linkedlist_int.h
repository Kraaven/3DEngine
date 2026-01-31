
#ifndef LL_int_H
#define LL_int_H

#include <stdlib.h>
#include <stdio.h>

typedef struct LLNode_int {
    int data;
    struct LLNode_int *next;
} LLNode_int;

typedef struct {
    LLNode_int *head;
    size_t size;
} LinkedList_int;

static inline LinkedList_int *ll_int_create(void) {
    LinkedList_int *list = malloc(sizeof(*list));
    if (!list) { perror("malloc"); exit(EXIT_FAILURE); }
    list->head = NULL;
    list->size = 0;
    return list;
}

static inline void ll_int_destroy(LinkedList_int *list) {
    LLNode_int *curr = list->head;
    while (curr) {
        LLNode_int *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(list);
}

static inline void ll_int_push_front(LinkedList_int *list, int value) {
    LLNode_int *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = list->head;
    list->head = node;
    list->size++;
}

static inline int ll_int_pop_front(LinkedList_int *list) {
    if (!list->head) { fprintf(stderr, "List empty\n"); exit(EXIT_FAILURE); }
    LLNode_int *node = list->head;
    int val = node->data;
    list->head = node->next;
    free(node);
    list->size--;
    return val;
}

static inline int ll_int_peek_front(LinkedList_int *list) {
    if (!list->head) { fprintf(stderr, "List empty\n"); exit(EXIT_FAILURE); }
    return list->head->data;
}

static inline int ll_int_query(LinkedList_int *list, size_t index) {
    if (index >= list->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    LLNode_int *curr = list->head;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline size_t ll_int_size(LinkedList_int *list) { return list->size; }
static inline int ll_int_empty(LinkedList_int *list) { return list->size == 0; }

#endif
