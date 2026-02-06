
#include "mesh.h"
#include "linkedlist_face.h"
#include <stdio.h>
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
mesh *mesh_load(char *fileName) {
  FILE *meshFile = fopen(fileName, "r");
  if (meshFile == NULL)
    return NULL;

  mesh *new = mesh_create();

  char readMeshFileBuffer[128];
  int bufferNextIndex = 0;
  char readCharacter;
  while ((readCharacter = fgetc(meshFile)) != EOF) {

    if (readCharacter == '\n') {
      readMeshFileBuffer[bufferNextIndex] = '\0';
      printf("%s\n", readMeshFileBuffer);

      bufferNextIndex = 0;
    } else {
      readMeshFileBuffer[bufferNextIndex] = (char)readCharacter;
      bufferNextIndex++;
    }
  }

  return new;
}
