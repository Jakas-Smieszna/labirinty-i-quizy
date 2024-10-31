#include "Grafika.h"
#include "mainMenu.h"
#include "gra_labirynt.h"
#include "ustawienia.h"
#include "gamestate.h"
#include <stdlib.h>

// !!
// Gdzie dodać nowy "stan gry"?
// gamestate.h
StanEkranu stanGry = GRA_LABIRYNT;
// !!

void UstawEkran0(Image ikona);
void Rysowanie(GRAFIKI* grafiki, PakietZmiennych* zmienne);
void Update(PakietZmiennych* zmienne, GRAFIKI* grafiki);

int main() {
    InitWindow(800, 450, "Labirynty i Quizy");
    PakietZmiennych Zmienne;
    GRAFIKI GRAFIKI;
    UstawEkran0(GRAFIKI.ikona);

    while (!WindowShouldClose() && !Zmienne.koniec)
    {
        Update(&Zmienne, &GRAFIKI);
        BeginDrawing();
        Rysowanie(&GRAFIKI, &Zmienne);
        EndDrawing();
    }
    GRAFIKI.D_GRAFIKI();
    CloseWindow();
    return 0;
}

void Update(PakietZmiennych* zmienne, GRAFIKI* grafiki) {
    if (zmienne->epizod != zmienne->epizod_doc) {
        zmienne->epizod = zmienne->epizod_doc;
        grafiki->aktualizuj_tlo(zmienne->epizod);
    }
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
            zmienne->koniec = true;
           /* CloseWindow();//JG: lepiej wyjsc z petli, by nie ominac zwalniania pamieci
            exit(0);*/
            break;
        case GRA_LABIRYNT:
            // JJJ
            zmienne->czas = zmienne->czas + 0.01;
            break;
    }
}

// Bardziej zaawansowane rysowanie i update-y lepiej pewnie umieścić w oddzielnych funkcjach
void Rysowanie(GRAFIKI* grafiki, PakietZmiennych* zmienne) {
    switch (stanGry) {
        case MAIN_MENU:
            // jak np. tu zrobiłem
            menu::drawMainMenu(grafiki);
            break;
        case USTAWIENIA:
            ustawienia::drawSettings();
            // draw
            break;
        case TWÓRCY: // Też się dziwie, że polskie znaki są tu akceptowalne.
            // draw
            break;
        case GRA_LABIRYNT:
            // JJJ
            labirynt::drawLabirynt(grafiki, zmienne);
            break;
    }
}

void UstawEkran0(Image ikona) {
    SetTargetFPS(100);//JG:ustawia liczbe klatek na sekunde na 100
    SetWindowIcon(ikona);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(640, 360);
    SetWindowMaxSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
}