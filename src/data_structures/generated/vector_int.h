#ifndef VECTOR_int_H
#define VECTOR_int_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t size;
  size_t capacity;
  int *data;
} Vector_int;

static inline Vector_int *vector_int_create(void) {
  Vector_int *v = malloc(sizeof(*v));
  if (!v) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  v->size = 0;
  v->capacity = 8;
  v->data = malloc(sizeof(int) * v->capacity);
  if (!v->data) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  return v;
}

static inline void vector_int_destroy(Vector_int *v) {
  free(v->data);
  free(v);
}

static inline void vector_int_push(Vector_int *v, int value) {
  if (v->size == v->capacity) {
    v->capacity *= 2;
    v->data = realloc(v->data, sizeof(int) * v->capacity);
    if (!v->data) {
      perror("realloc");
      exit(EXIT_FAILURE);
    }
  }
  v->data[v->size++] = value;
}

static inline int vector_int_get(Vector_int *v, size_t index) {
  if (index >= v->size) {
    fprintf(stderr, "Index out of bounds\n");
    exit(EXIT_FAILURE);
  }
  return v->data[index];
}

static inline void vector_int_set(Vector_int *v, size_t index, int value) {
  if (index >= v->size) {
    fprintf(stderr, "Index out of bounds\n");
    exit(EXIT_FAILURE);
  }
  v->data[index] = value;
}

static inline size_t vector_int_size(Vector_int *v) { return v->size; }
static inline int vector_int_empty(Vector_int *v) { return v->size == 0; }

#endif
