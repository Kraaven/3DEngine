#ifndef VECTOR_{{TYPE_NAME}}_H
#define VECTOR_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t size;
    size_t capacity;
    {{TYPE}} *data;
} Vector_{{TYPE_NAME}};

static inline Vector_{{TYPE_NAME}} *vector_{{TYPE_NAME}}_create(void) {
    Vector_{{TYPE_NAME}} *v = malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(EXIT_FAILURE); }
    v->size = 0;
    v->capacity = 8;
    v->data = malloc(sizeof({{TYPE}}) * v->capacity);
    if (!v->data) { perror("malloc"); exit(EXIT_FAILURE); }
    return v;
}

static inline void vector_{{TYPE_NAME}}_destroy(Vector_{{TYPE_NAME}} *v) {
    free(v->data);
    free(v);
}

static inline void vector_{{TYPE_NAME}}_push(Vector_{{TYPE_NAME}} *v, {{TYPE}} value) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof({{TYPE}}) * v->capacity);
        if (!v->data) { perror("realloc"); exit(EXIT_FAILURE); }
    }
    v->data[v->size++] = value;
}

static inline {{TYPE}} vector_{{TYPE_NAME}}_get(Vector_{{TYPE_NAME}} *v, size_t index) {
    if (index >= v->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    return v->data[index];
}

static inline void vector_{{TYPE_NAME}}_set(Vector_{{TYPE_NAME}} *v, size_t index, {{TYPE}} value) {
    if (index >= v->size) { fprintf(stderr, "Index out of bounds\n"); exit(EXIT_FAILURE); }
    v->data[index] = value;
}

static inline size_t vector_{{TYPE_NAME}}_size(Vector_{{TYPE_NAME}} *v) { return v->size; }
static inline int vector_{{TYPE_NAME}}_empty(Vector_{{TYPE_NAME}} *v) { return v->size == 0; }

#endif
