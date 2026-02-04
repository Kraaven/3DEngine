
#include "transform.h"
#include "linkedlist_transform.h"
#include <stdlib.h>

transform *transform_create(void) {
  transform *tr = malloc(sizeof(transform));

  tr->position = (vec3){0, 0, 0};
  tr->rotation = (vec3){0, 0, 0};
  tr->scale = (vec3){1, 1, 1};

  tr->parent = NULL;
  tr->children = ll_transform_create();

  return tr;
}
transform *transform_create_desc(vec3 pos, vec3 rot, vec3 scl) {

  transform *tr = transform_create();

  tr->position = pos;
  tr->rotation = rot;
  tr->scale = scl;

  return tr;
}
void transform_destroy(transform *tr) {

  if (tr->parent != NULL) {
    ll_transform_delete_value(tr->parent->children, tr);
  }

  while (tr->children->size > 0) {
    transform_destroy(ll_transform_pop_front(tr->children));
  }

  free(tr);
}

void SetChild(transform *parent, transform *child) {
  AbandonParent(child);
  ll_transform_push_front(parent->children, child);
  child->parent = parent;
  ll_transform_push_front(parent->children, child);
}

void AbandonParent(transform *child) {
  if (child->parent == NULL)
    return;
  ll_transform_delete_value(child->parent->children, child);
}
