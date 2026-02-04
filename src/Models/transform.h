#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vectors.h"

typedef struct LinkedList_transform LinkedList_transform;

typedef struct transform {
  vec3 position;
  vec3 rotation;
  vec3 scale;

  struct transform *parent;
  LinkedList_transform *children;
} transform;

transform *transform_create(void);
transform *transform_create_desc(vec3 pos, vec3 rot, vec3 scl);
void transform_destroy(transform *tr);

void SetChild(transform *parent, transform *child);
void AbandonParent(transform *child);

#endif
