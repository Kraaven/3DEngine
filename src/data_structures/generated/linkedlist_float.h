
#ifndef LL_float_H
#define LL_float_H

#include <stdlib.h>
#include <stdio.h>

typedef struct LLNode_float {
    float data;
    struct LLNode_float *next;
} LLNode_float;

typedef struct {
    LLNode_float *head;
    size_t size;
} LinkedList_float;

static inline LinkedList_float *ll_float_create(void) {
    LinkedList_float *list = malloc(sizeof(*list));
    if (!list) { perror("malloc"); exit(EXIT_FAILURE); }
    list->head = NULL;
    list->size = 0;
    return list;
}

static inline void ll_float_destroy(LinkedList_float *list) {
    LLNode_float *curr = list->head;
    while (curr) {
        LLNode_float *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(list);
}

static inline void ll_float_push_front(LinkedList_float *list, float value) {
    LLNode_float *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = list->head;
    list->head = node;
    list->size++;
}

static inline float ll_float_pop_front(LinkedList_float *list) {
    if (!list->head) { fprintf(stderr, "List empty\n"); exit(EXIT_FAILURE); }
    LLNode_float *node = list->head;
    float val = node->data;
    list->head = node->next;
    free(node);
    list->size--;
    return val;
}

static inline float ll_float_peek_front(LinkedList_float *list) {
    if (!list->head) { fprintf(stderr, "List empty\n"); exit(EXIT_FAILURE); }
    return list->head->data;
}

static inline float ll_float_query(LinkedList_float *list, size_t index) {
    if (index >= list->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    LLNode_float *curr = list->head;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline size_t ll_float_size(LinkedList_float *list) { return list->size; }
static inline int ll_float_empty(LinkedList_float *list) { return list->size == 0; }

#endif
