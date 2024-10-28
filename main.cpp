#include "raylib.h"
#include "mainMenu.h"
#include "ustawienia.h"
#include "gamestate.h"
#include <stdlib.h>

// !!
// Gdzie dodać nowy "stan gry"?
// gamestate.h
StanEkranu stanGry = MAIN_MENU;
// !!

void Rysowanie();
void Update();

int main() {
    InitWindow(800, 450, "Labirynty i Quizy");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    while (!WindowShouldClose())
    {
        Update();
        BeginDrawing();
        Rysowanie();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void Update() {
    switch (stanGry) {
        case MAIN_MENU:
            menu::updateMainMenu();
            break;
        case USTAWIENIA:
            ustawienia::updateSettings();
            break;
        case TWÓRCY: // Też się dziwie, że polskie znaki są tu akceptowalne.
            // update
            break;
        case EXIT:
            CloseWindow();
            exit(0);
            break;
    }
}

// Bardziej zaawansowane rysowanie i update-y lepiej pewnie umieścić w oddzielnych funkcjach
void Rysowanie() {
    switch (stanGry) {
        case MAIN_MENU:
            // jak np. tu zrobiłem
            menu::drawMainMenu();
            break;
        case USTAWIENIA:
            ustawienia::drawSettings();
            // draw
            break;
        case TWÓRCY: // Też się dziwie, że polskie znaki są tu akceptowalne.
            // draw
            break;
    }
}