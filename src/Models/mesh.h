#ifndef MESH
#define MESH

#include "linkedlist_face.h"

typedef struct mesh {
  LinkedList_face *faces;
} mesh;

mesh *mesh_create();
mesh *mesh_load(char *fileName);

#endif // !MESH
