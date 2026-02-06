#include "mesh.h"
#include "raylib.h"

int main(void) {
  const int screenWidth = 1600;
  const int screenHeight = 900;

  InitWindow(screenWidth, screenHeight, "Raylib Hello World");

  SetTargetFPS(60);

  mesh *new = mesh_load("resources/meshes/monkey.3d");
  if (new == NULL)
    printf("3D File failed to load\n");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, Raylib!", 250, 200, 30, DARKGRAY);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
