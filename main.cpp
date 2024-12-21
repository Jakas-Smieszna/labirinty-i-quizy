#include "Grafika.h"
#include "mainMenu.h"
#include "gra_labirynt.h"
#include "gra_quiz.h"
#include "ustawienia.h"
#include "credits.h"
#include "gamestate.h"
#include "instrukcja.h"
#include "wybor_uzytkownika.h"
#include <stdlib.h>
#include "wybor_poziomu.h"
#include "Podsumowanie.h"

// !!
// Gdzie dodać nowy "stan gry"?
// gamestate.h
StanEkranu stanGry = MAIN_MENU;
// !!
GRAFIKI* grafiki = nullptr;
PakietZmiennych* zmienne = new PakietZmiennych;
Theme EpisodeTheme = Theme();

void UstawEkran0(Image ikona);
void Rysowanie();
void Update();

int main() {
    InitWindow(1080, 720, "Labirynty i Quizy");
    grafiki = new GRAFIKI;
    UstawEkran0(grafiki->ikona);
    while (!WindowShouldClose() && !zmienne->koniec)
    {
        Update();
        BeginDrawing();
        Rysowanie();
        EndDrawing();
    }
    grafiki->D_GRAFIKI();
    zmienne->poziomik.D_Poziom();
    zmienne->D_Zmienne();
    CloseWindow();
    return 0;
}

void Update() {
    if (zmienne->epizod != zmienne->epizod_doc) {
        zmienne->epizod = zmienne->epizod_doc;
        grafiki->aktualizuj_tlo(zmienne->epizod);
        EpisodeTheme.Update(zmienne->epizod);
    }
    switch (stanGry) {
        case MAIN_MENU:
            menu::updateMainMenu();
            break;
        case WYBOR_POZIOMU:
            wybor_poziomu::updateLevelMenu();
            break;
        case USTAWIENIA:
            ustawienia::updateSettings();
            break;
        case TWORCY: // Też się dziwie, że polskie znaki są tu akceptowalne.
            // update
            credits::updateCredits();
            break;
        case INSTRUKCJA:
           instrukcja::updateInstruction();
            break;
        case WYBOR_UZYTKOWNIKA:
           wybor_uzytkownika::updateUserMenu();
           break;
        case EXIT:
            zmienne->koniec = true;
           /* CloseWindow();//JG: lepiej wyjsc z petli, by nie ominac zwalniania pamieci
            exit(0);*/
            break;
        case GRA_LABIRYNT:
            // JJJ
            labirynt::updateLabirynt(&(grafiki->tlo));
            break;
        case GRA_QUIZ:
            // JJJ
            quiz::updateQuiz(&(grafiki->tlo));
            break;
        case PODSUMOWANIE:
            // JJJ
            podsumowanie::updatePodsumowanie(&(grafiki->tlo));
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
        case WYBOR_POZIOMU:
            wybor_poziomu::drawLevelMenu();
            // draw
            break;
        case USTAWIENIA:
            ustawienia::drawSettings();
            // draw
            break;
        case TWORCY: // Też się dziwie, że polskie znaki są tu akceptowalne.
            credits::drawCredits();
            // draw
            break;
        case WYBOR_UZYTKOWNIKA:
           wybor_uzytkownika::drawUserMenu();
           break;
        case GRA_LABIRYNT:
            // JJJ
            labirynt::drawLabirynt();
            break;
        case GRA_QUIZ:
            // JJJ
            quiz::drawQuiz();
            break;
        case PODSUMOWANIE:
            // JJJ
            podsumowanie::drawPodsumowanie();
            break;
        case INSTRUKCJA:
           instrukcja::drawInstruction();
           break;
    }
}

void UstawEkran0(Image ikona) {//JG:ustawia podstawowe ustawienia okna, klatek etc
    SetTargetFPS(100);//JG:ustawia liczbe klatek na sekunde na 100
    //SetMouseCursor(10);
    SetWindowIcon(ikona);//JG:ustawia ikone okna i paska zadan
    SetWindowState(FLAG_WINDOW_RESIZABLE);//to co bylo wczesniej - mozliwosc zmiany wymiarow okna
    SetWindowMinSize(640, 360);//JG:minimalne wymiary okna
    SetWindowMaxSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));//JG:maksymalne wymiary okna - na podstawie wymiarow biezacego monitora
}