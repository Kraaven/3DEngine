
#include "mesh.h"
#include "linkedlist_face.h"
#include <stdlib.h>

mesh *mesh_create() {
  mesh *new = malloc(sizeof(mesh));
  new->faces = ll_face_create();
  return new;
}

void mesh_destroy(mesh *meshObject) {

  while (meshObject->faces->size > 0) {
    free(ll_face_pop_front(meshObject->faces));
  }
  ll_face_destroy(meshObject->faces);
  free(meshObject);
}
// mesh *mesh_load() {}
