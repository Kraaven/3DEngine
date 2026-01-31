
#ifndef STACK_{{TYPE_NAME}}_H
#define STACK_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>

typedef struct StackNode_{{TYPE_NAME}} {
    {{TYPE}} data;
    struct StackNode_{{TYPE_NAME}} *next;
} StackNode_{{TYPE_NAME}};

typedef struct {
    StackNode_{{TYPE_NAME}} *head;
    size_t size;
} Stack_{{TYPE_NAME}};

static inline Stack_{{TYPE_NAME}} *stack_{{TYPE_NAME}}_create(void) {
    Stack_{{TYPE_NAME}} *s = malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(EXIT_FAILURE); }
    s->head = NULL;
    s->size = 0;
    return s;
}

static inline void stack_{{TYPE_NAME}}_destroy(Stack_{{TYPE_NAME}} *s) {
    StackNode_{{TYPE_NAME}} *curr = s->head;
    while (curr) {
        StackNode_{{TYPE_NAME}} *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(s);
}

static inline void stack_{{TYPE_NAME}}_push(Stack_{{TYPE_NAME}} *s, {{TYPE}} value) {
    StackNode_{{TYPE_NAME}} *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = s->head;
    s->head = node;
    s->size++;
}

static inline {{TYPE}} stack_{{TYPE_NAME}}_pop(Stack_{{TYPE_NAME}} *s) {
    if (!s->head) { fprintf(stderr, "Stack empty\n"); exit(EXIT_FAILURE); }
    StackNode_{{TYPE_NAME}} *node = s->head;
    {{TYPE}} val = node->data;
    s->head = node->next;
    free(node);
    s->size--;
    return val;
}

static inline {{TYPE}} stack_{{TYPE_NAME}}_peek(Stack_{{TYPE_NAME}} *s) {
    if (!s->head) { fprintf(stderr, "Stack empty\n"); exit(EXIT_FAILURE); }
    return s->head->data;
}

static inline {{TYPE}} stack_{{TYPE_NAME}}_query(Stack_{{TYPE_NAME}} *s, size_t index) {
    if (index >= s->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    StackNode_{{TYPE_NAME}} *curr = s->head;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline int stack_{{TYPE_NAME}}_empty(Stack_{{TYPE_NAME}} *s) { return s->size == 0; }
static inline size_t stack_{{TYPE_NAME}}_size(Stack_{{TYPE_NAME}} *s) { return s->size; }

#endif
