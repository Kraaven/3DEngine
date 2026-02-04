
#ifndef VECTOR_{{TYPE_NAME}}_H
#define VECTOR_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
{{TYPE_INCLUDES}}

typedef struct Vector_{{TYPE_NAME}}{
    {{TYPE}} *data;
    size_t size;
    size_t capacity;
} Vector_{{TYPE_NAME}};

static inline Vector_{{TYPE_NAME}} *
vector_{{TYPE_NAME}}_create(size_t initial_capacity)
{
    Vector_{{TYPE_NAME}} *v = malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(EXIT_FAILURE); }

    v->size = 0;
    v->capacity = initial_capacity ? initial_capacity : 4;
    v->data = malloc(v->capacity * sizeof(*v->data));
    if (!v->data) { perror("malloc"); exit(EXIT_FAILURE); }

    return v;
}

static inline void
vector_{{TYPE_NAME}}_destroy(Vector_{{TYPE_NAME}} *v)
{
    free(v->data);
    free(v);
}

static inline void
vector_{{TYPE_NAME}}_reserve(Vector_{{TYPE_NAME}} *v, size_t new_capacity)
{
    if (new_capacity <= v->capacity) return;

    {{TYPE}} *new_data = realloc(v->data, new_capacity * sizeof(*v->data));
    if (!new_data) { perror("realloc"); exit(EXIT_FAILURE); }

    v->data = new_data;
    v->capacity = new_capacity;
}

static inline void
vector_{{TYPE_NAME}}_push_back(Vector_{{TYPE_NAME}} *v, {{TYPE}} value)
{
    if (v->size >= v->capacity)
        vector_{{TYPE_NAME}}_reserve(v, v->capacity * 2);

    v->data[v->size++] = value;
}

static inline {{TYPE}}
vector_{{TYPE_NAME}}_pop_back(Vector_{{TYPE_NAME}} *v)
{
    if (v->size == 0) {
        fprintf(stderr, "Vector empty\n");
        exit(EXIT_FAILURE);
    }
    return v->data[--v->size];
}

static inline {{TYPE}}
vector_{{TYPE_NAME}}_get(const Vector_{{TYPE_NAME}} *v, size_t index)
{
    if (index >= v->size) {
        fprintf(stderr, "Vector index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return v->data[index];
}

static inline void
vector_{{TYPE_NAME}}_set(Vector_{{TYPE_NAME}} *v, size_t index, {{TYPE}} value)
{
    if (index >= v->size) {
        fprintf(stderr, "Vector index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    v->data[index] = value;
}

static inline {{TYPE}} *
vector_{{TYPE_NAME}}_data(Vector_{{TYPE_NAME}} *v)
{
    return v->data;
}

static inline size_t
vector_{{TYPE_NAME}}_size(const Vector_{{TYPE_NAME}} *v)
{
    return v->size;
}

static inline size_t
vector_{{TYPE_NAME}}_capacity(const Vector_{{TYPE_NAME}} *v)
{
    return v->capacity;
}

static inline int
vector_{{TYPE_NAME}}_empty(const Vector_{{TYPE_NAME}} *v)
{
    return v->size == 0;
}

static inline void
vector_{{TYPE_NAME}}_clear(Vector_{{TYPE_NAME}} *v)
{
    v->size = 0;
}

#endif
