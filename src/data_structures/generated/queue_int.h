
#ifndef QUEUE_int_H
#define QUEUE_int_H

#include <stdlib.h>
#include <stdio.h>

typedef struct QueueNode_int {
    int data;
    struct QueueNode_int *next;
} QueueNode_int;

typedef struct {
    QueueNode_int *front;
    QueueNode_int *back;
    size_t size;
} Queue_int;

static inline Queue_int *queue_int_create(void) {
    Queue_int *q = malloc(sizeof(*q));
    if (!q) { perror("malloc"); exit(EXIT_FAILURE); }
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

static inline void queue_int_destroy(Queue_int *q) {
    QueueNode_int *curr = q->front;
    while (curr) {
        QueueNode_int *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(q);
}

static inline void queue_int_enqueue(Queue_int *q, int value) {
    QueueNode_int *node = malloc(sizeof(*node));
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

static inline int queue_int_dequeue(Queue_int *q) {
    if (!q->front) { fprintf(stderr, "Queue empty\n"); exit(EXIT_FAILURE); }
    QueueNode_int *node = q->front;
    int val = node->data;
    q->front = node->next;
    if (!q->front) q->back = NULL;
    free(node);
    q->size--;
    return val;
}

static inline int queue_int_peek(Queue_int *q) {
    if (!q->front) { fprintf(stderr, "Queue empty\n"); exit(EXIT_FAILURE); }
    return q->front->data;
}

static inline int queue_int_query(Queue_int *q, size_t index) {
    if (index >= q->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    QueueNode_int *curr = q->front;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

static inline int queue_int_empty(Queue_int *q) { return q->size == 0; }
static inline size_t queue_int_size(Queue_int *q) { return q->size; }

#endif
