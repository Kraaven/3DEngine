
#ifndef STACK_float_H
#define STACK_float_H

#include <stdlib.h>
#include <stdio.h>

typedef struct StackNode_float {
    float data;
    struct StackNode_float *next;
} StackNode_float;

typedef struct {
    StackNode_float *head;
    size_t size;
} Stack_float;

static inline Stack_float *stack_float_create(void) {
    Stack_float *s = malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(EXIT_FAILURE); }
    s->head = NULL;
    s->size = 0;
    return s;
}

static inline void stack_float_destroy(Stack_float *s) {
    StackNode_float *curr = s->head;
    while (curr) {
        StackNode_float *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(s);
}

static inline void stack_float_push(Stack_float *s, float value) {
    StackNode_float *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = s->head;
    s->head = node;
    s->size++;
}

static inline float stack_float_pop(Stack_float *s) {
    if (!s->head) { fprintf(stderr, "Stack empty\n"); exit(EXIT_FAILURE); }
    StackNode_float *node = s->head;
    float val = node->data;
    s->head = node->next;
    free(node);
    s->size--;
    return val;
}

static inline float stack_float_peek(Stack_float *s) {
    if (!s->head) { fprintf(stderr, "Stack empty\n"); exit(EXIT_FAILURE); }
    return s->head->data;
}

static inline float stack_float_query(Stack_float *s, size_t index) {
    if (index >= s->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    StackNode_float *curr = s->head;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline int stack_float_empty(Stack_float *s) { return s->size == 0; }
static inline size_t stack_float_size(Stack_float *s) { return s->size; }

#endif
