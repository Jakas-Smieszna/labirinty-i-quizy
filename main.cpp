#include "raylib.h"

Texture2D tlo_epizod1 = LoadTexture("Grafika1/Tlo1.png");

int main() {
    InitWindow(1200, 600, "Labirynty i Quizy");
    char okno = 'l';

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(tlo_epizod1, 0.0, 0.0, WHITE);
        if (IsTextureReady(tlo_epizod1)) DrawText("TAK", 100.0, 100.0, 25, BLACK);
        // DrawTexturePro(tlo_epizod1, { 0.0f, 0.0f, 1920.0f, 1080.0f }, { 0.0f, 0.0f, 1200.0f, 600.0f }, { 0.0f, 0.0f}, 0.0f, WHITE);
       /*  switch (okno) {
         case 'l':
         }*/
        EndDrawing();
    }

    UnloadTexture(tlo_epizod1);
    CloseWindow();

    return 0;
}