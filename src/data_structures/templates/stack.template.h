
#ifndef STACK_{{TYPE_NAME}}_H
#define STACK_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>
{{TYPE_INCLUDES}}

typedef struct StackNode_{{TYPE_NAME}} {
    {{TYPE}} data;
    struct StackNode_{{TYPE_NAME}} *next;
} StackNode_{{TYPE_NAME}};

typedef struct Stack_{{TYPE_NAME}}{
    StackNode_{{TYPE_NAME}} *top;
    size_t size;
} Stack_{{TYPE_NAME}};

static inline Stack_{{TYPE_NAME}} *stack_{{TYPE_NAME}}_create(void) {
    Stack_{{TYPE_NAME}} *s = malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(EXIT_FAILURE); }
    s->top = NULL;
    s->size = 0;
    return s;
}

static inline void stack_{{TYPE_NAME}}_destroy(Stack_{{TYPE_NAME}} *s) {
    while (s->top) {
        StackNode_{{TYPE_NAME}} *tmp = s->top;
        s->top = tmp->next;
        free(tmp);
    }
    free(s);
}

static inline void stack_{{TYPE_NAME}}_push(
    Stack_{{TYPE_NAME}} *s, {{TYPE}} value
) {
    StackNode_{{TYPE_NAME}} *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = s->top;
    s->top = node;
    s->size++;
}

static inline {{TYPE}} stack_{{TYPE_NAME}}_pop(
    Stack_{{TYPE_NAME}} *s
) {
    if (!s->top) {
        fprintf(stderr, "Stack empty\n");
        exit(EXIT_FAILURE);
    }
    StackNode_{{TYPE_NAME}} *node = s->top;
    {{TYPE}} val = node->data;
    s->top = node->next;
    free(node);
    s->size--;
    return val;
}

static inline {{TYPE}} stack_{{TYPE_NAME}}_peek(
    Stack_{{TYPE_NAME}} *s
) {
    if (!s->top) {
        fprintf(stderr, "Stack empty\n");
        exit(EXIT_FAILURE);
    }
    return s->top->data;
}

static inline size_t stack_{{TYPE_NAME}}_size(Stack_{{TYPE_NAME}} *s) {
    return s->size;
}

static inline int stack_{{TYPE_NAME}}_empty(Stack_{{TYPE_NAME}} *s) {
    return s->size == 0;
}

#endif
