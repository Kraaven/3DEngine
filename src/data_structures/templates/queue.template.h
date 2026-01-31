
#ifndef QUEUE_{{TYPE_NAME}}_H
#define QUEUE_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>

typedef struct QueueNode_{{TYPE_NAME}} {
    {{TYPE}} data;
    struct QueueNode_{{TYPE_NAME}} *next;
} QueueNode_{{TYPE_NAME}};

typedef struct {
    QueueNode_{{TYPE_NAME}} *front;
    QueueNode_{{TYPE_NAME}} *back;
    size_t size;
} Queue_{{TYPE_NAME}};

static inline Queue_{{TYPE_NAME}} *queue_{{TYPE_NAME}}_create(void) {
    Queue_{{TYPE_NAME}} *q = malloc(sizeof(*q));
    if (!q) { perror("malloc"); exit(EXIT_FAILURE); }
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

static inline void queue_{{TYPE_NAME}}_destroy(Queue_{{TYPE_NAME}} *q) {
    QueueNode_{{TYPE_NAME}} *curr = q->front;
    while (curr) {
        QueueNode_{{TYPE_NAME}} *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(q);
}

static inline void queue_{{TYPE_NAME}}_enqueue(Queue_{{TYPE_NAME}} *q, {{TYPE}} value) {
    QueueNode_{{TYPE_NAME}} *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = NULL;
    if (!q->back) {
        q->front = node;
        q->back = node;
    } else {
        q->back->next = node;
        q->back = node;
    }
    q->size++;
}

static inline {{TYPE}} queue_{{TYPE_NAME}}_dequeue(Queue_{{TYPE_NAME}} *q) {
    if (!q->front) { fprintf(stderr, "Queue empty\n"); exit(EXIT_FAILURE); }
    QueueNode_{{TYPE_NAME}} *node = q->front;
    {{TYPE}} val = node->data;
    q->front = node->next;
    if (!q->front) q->back = NULL;
    free(node);
    q->size--;
    return val;
}

static inline {{TYPE}} queue_{{TYPE_NAME}}_peek(Queue_{{TYPE_NAME}} *q) {
    if (!q->front) { fprintf(stderr, "Queue empty\n"); exit(EXIT_FAILURE); }
    return q->front->data;
}

static inline {{TYPE}} queue_{{TYPE_NAME}}_query(Queue_{{TYPE_NAME}} *q, size_t index) {
    if (index >= q->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    QueueNode_{{TYPE_NAME}} *curr = q->front;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline int queue_{{TYPE_NAME}}_empty(Queue_{{TYPE_NAME}} *q) { return q->size == 0; }
static inline size_t queue_{{TYPE_NAME}}_size(Queue_{{TYPE_NAME}} *q) { return q->size; }

#endif
