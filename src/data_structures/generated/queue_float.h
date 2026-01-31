
#ifndef QUEUE_float_H
#define QUEUE_float_H

#include <stdlib.h>
#include <stdio.h>

typedef struct QueueNode_float {
    float data;
    struct QueueNode_float *next;
} QueueNode_float;

typedef struct {
    QueueNode_float *front;
    QueueNode_float *back;
    size_t size;
} Queue_float;

static inline Queue_float *queue_float_create(void) {
    Queue_float *q = malloc(sizeof(*q));
    if (!q) { perror("malloc"); exit(EXIT_FAILURE); }
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

static inline void queue_float_destroy(Queue_float *q) {
    QueueNode_float *curr = q->front;
    while (curr) {
        QueueNode_float *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(q);
}

static inline void queue_float_enqueue(Queue_float *q, float value) {
    QueueNode_float *node = malloc(sizeof(*node));
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

static inline float queue_float_dequeue(Queue_float *q) {
    if (!q->front) { fprintf(stderr, "Queue empty\n"); exit(EXIT_FAILURE); }
    QueueNode_float *node = q->front;
    float val = node->data;
    q->front = node->next;
    if (!q->front) q->back = NULL;
    free(node);
    q->size--;
    return val;
}

static inline float queue_float_peek(Queue_float *q) {
    if (!q->front) { fprintf(stderr, "Queue empty\n"); exit(EXIT_FAILURE); }
    return q->front->data;
}

static inline float queue_float_query(Queue_float *q, size_t index) {
    if (index >= q->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    QueueNode_float *curr = q->front;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline int queue_float_empty(Queue_float *q) { return q->size == 0; }
static inline size_t queue_float_size(Queue_float *q) { return q->size; }

#endif
