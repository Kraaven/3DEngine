#ifndef VECTOR_float_H
#define VECTOR_float_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t size;
    size_t capacity;
    float *data;
} Vector_float;

static inline Vector_float *vector_float_create(void) {
    Vector_float *v = malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(EXIT_FAILURE); }
    v->size = 0;
    v->capacity = 8;
    v->data = malloc(sizeof(float) * v->capacity);
    if (!v->data) { perror("malloc"); exit(EXIT_FAILURE); }
    return v;
}

static inline void vector_float_destroy(Vector_float *v) {
    free(v->data);
    free(v);
}

static inline void vector_float_push(Vector_float *v, float value) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(float) * v->capacity);
        if (!v->data) { perror("realloc"); exit(EXIT_FAILURE); }
    }
    v->data[v->size++] = value;
}

static inline float vector_float_get(Vector_float *v, size_t index) {
    if (index >= v->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    return v->data[index];
}

static inline void vector_float_set(Vector_float *v, size_t index, float value) {
    if (index >= v->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    v->data[index] = value;
}

static inline size_t vector_float_size(Vector_float *v) { return v->size; }
static inline int vector_float_empty(Vector_float *v) { return v->size == 0; }

#endif
