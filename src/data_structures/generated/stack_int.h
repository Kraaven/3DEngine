
#ifndef STACK_int_H
#define STACK_int_H

#include <stdlib.h>
#include <stdio.h>

typedef struct StackNode_int {
    int data;
    struct StackNode_int *next;
} StackNode_int;

typedef struct {
    StackNode_int *head;
    size_t size;
} Stack_int;

static inline Stack_int *stack_int_create(void) {
    Stack_int *s = malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(EXIT_FAILURE); }
    s->head = NULL;
    s->size = 0;
    return s;
}

static inline void stack_int_destroy(Stack_int *s) {
    StackNode_int *curr = s->head;
    while (curr) {
        StackNode_int *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(s);
}

static inline void stack_int_push(Stack_int *s, int value) {
    StackNode_int *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = s->head;
    s->head = node;
    s->size++;
}

static inline int stack_int_pop(Stack_int *s) {
    if (!s->head) { fprintf(stderr, "Stack empty\n"); exit(EXIT_FAILURE); }
    StackNode_int *node = s->head;
    int val = node->data;
    s->head = node->next;
    free(node);
    s->size--;
    return val;
}

static inline int stack_int_peek(Stack_int *s) {
    if (!s->head) { fprintf(stderr, "Stack empty\n"); exit(EXIT_FAILURE); }
    return s->head->data;
}

static inline int stack_int_query(Stack_int *s, size_t index) {
    if (index >= s->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    StackNode_int *curr = s->head;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline int stack_int_empty(Stack_int *s) { return s->size == 0; }
static inline size_t stack_int_size(Stack_int *s) { return s->size; }

#endif
