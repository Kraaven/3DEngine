
#ifndef LL_{{TYPE_NAME}}_H
#define LL_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>

typedef struct LLNode_{{TYPE_NAME}} {
    {{TYPE}} data;
    struct LLNode_{{TYPE_NAME}} *next;
} LLNode_{{TYPE_NAME}};

typedef struct {
    LLNode_{{TYPE_NAME}} *head;
    size_t size;
} LinkedList_{{TYPE_NAME}};

static inline LinkedList_{{TYPE_NAME}} *ll_{{TYPE_NAME}}_create(void) {
    LinkedList_{{TYPE_NAME}} *list = malloc(sizeof(*list));
    if (!list) { perror("malloc"); exit(EXIT_FAILURE); }
    list->head = NULL;
    list->size = 0;
    return list;
}

static inline void ll_{{TYPE_NAME}}_destroy(LinkedList_{{TYPE_NAME}} *list) {
    LLNode_{{TYPE_NAME}} *curr = list->head;
    while (curr) {
        LLNode_{{TYPE_NAME}} *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(list);
}

static inline void ll_{{TYPE_NAME}}_push_front(LinkedList_{{TYPE_NAME}} *list, {{TYPE}} value) {
    LLNode_{{TYPE_NAME}} *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = list->head;
    list->head = node;
    list->size++;
}

static inline {{TYPE}} ll_{{TYPE_NAME}}_pop_front(LinkedList_{{TYPE_NAME}} *list) {
    if (!list->head) { fprintf(stderr, "List empty\n"); exit(EXIT_FAILURE); }
    LLNode_{{TYPE_NAME}} *node = list->head;
    {{TYPE}} val = node->data;
    list->head = node->next;
    free(node);
    list->size--;
    return val;
}

static inline {{TYPE}} ll_{{TYPE_NAME}}_peek_front(LinkedList_{{TYPE_NAME}} *list) {
    if (!list->head) { fprintf(stderr, "List empty\n"); exit(EXIT_FAILURE); }
    return list->head->data;
}

static inline {{TYPE}} ll_{{TYPE_NAME}}_query(LinkedList_{{TYPE_NAME}} *list, size_t index) {
    if (index >= list->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    LLNode_{{TYPE_NAME}} *curr = list->head;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline size_t ll_{{TYPE_NAME}}_size(LinkedList_{{TYPE_NAME}} *list) { return list->size; }
static inline int ll_{{TYPE_NAME}}_empty(LinkedList_{{TYPE_NAME}} *list) { return list->size == 0; }

#endif
