
#ifndef QUEUE_{{TYPE_NAME}}_H
#define QUEUE_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>
{{TYPE_INCLUDES}}

typedef struct QueueNode_{{TYPE_NAME}} {
    {{TYPE}} data;
    struct QueueNode_{{TYPE_NAME}} *next;
} QueueNode_{{TYPE_NAME}};

typedef struct Queue_{{TYPE_NAME}}{
    QueueNode_{{TYPE_NAME}} *head;
    QueueNode_{{TYPE_NAME}} *tail;
    size_t size;
} Queue_{{TYPE_NAME}};

static inline Queue_{{TYPE_NAME}} *queue_{{TYPE_NAME}}_create(void) {
    Queue_{{TYPE_NAME}} *q = malloc(sizeof(*q));
    if (!q) { perror("malloc"); exit(EXIT_FAILURE); }
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

static inline void queue_{{TYPE_NAME}}_destroy(Queue_{{TYPE_NAME}} *q) {
    while (q->head) {
        QueueNode_{{TYPE_NAME}} *tmp = q->head;
        q->head = tmp->next;
        free(tmp);
    }
    free(q);
}

static inline void queue_{{TYPE_NAME}}_enqueue(
    Queue_{{TYPE_NAME}} *q, {{TYPE}} value
) {
    QueueNode_{{TYPE_NAME}} *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = NULL;

    if (q->tail)
        q->tail->next = node;
    else
        q->head = node;

    q->tail = node;
    q->size++;
}

static inline {{TYPE}} queue_{{TYPE_NAME}}_dequeue(
    Queue_{{TYPE_NAME}} *q
) {
    if (!q->head) {
        fprintf(stderr, "Queue empty\n");
        exit(EXIT_FAILURE);
    }
    QueueNode_{{TYPE_NAME}} *node = q->head;
    {{TYPE}} val = node->data;
    q->head = node->next;
    if (!q->head) q->tail = NULL;
    free(node);
    q->size--;
    return val;
}

static inline {{TYPE}} queue_{{TYPE_NAME}}_peek(
    Queue_{{TYPE_NAME}} *q
) {
    if (!q->head) {
        fprintf(stderr, "Queue empty\n");
        exit(EXIT_FAILURE);
    }
    return q->head->data;
}

static inline size_t queue_{{TYPE_NAME}}_size(Queue_{{TYPE_NAME}} *q) {
    return q->size;
}

static inline int queue_{{TYPE_NAME}}_empty(Queue_{{TYPE_NAME}} *q) {
    return q->size == 0;
}

#endif
