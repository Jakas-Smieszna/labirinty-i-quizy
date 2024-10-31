#pragma once
#include <ctime>
#include <cstdlib>
#include <string>

enum StanEkranu {
    MAIN_MENU = 0,
    USTAWIENIA,
    TWÓRCY,
    // Dodajcie tutaj nowe stany, jak je utworzycie.
    // Przez stan mam na myśli inne "menu", np
    // gdy Miłosz zrobi menu instrukcji, doda tu stan
    // i może go nazwie INSTRUKCJA
    // potem dodać do switcha w Rysowanie() i Update(), na dole pod mainem,
    DO_LABIRYNT = 7,
    GRA_LABIRYNT = 8,
    Z_LABIRYNT = 9,
    DO_QUIZ = 10,
    GRA_QUIZ = 11,
    Z_QUIZ = 12,
    EXIT // Na koniec - wyjście.
};

class PakietZmiennych {
public:
    char* uzytkownik;
    bool koniec;
    char epizod;
    char epizod_doc;
    char poziom;
    char poziom_doc;
    double czas;
    double kontrola_czas;
    double kontrola_wynik;
    double wynik;
    double rekord_wlasny;
    double rekord_lokalny;
    double rekord_swiata;
    bool pauza;
    int cofniecia;
    int kontrola_cofniecia;
    

    PakietZmiennych() {
        uzytkownik = "Rimek Wesolek";
        koniec = false;
        srand(time(NULL));
        epizod_doc = (char)(rand()%4 + 1);
        epizod = 1;
        poziom = 1;
        poziom_doc = 1;
        czas = 0.0;
        kontrola_czas = 0.0;
        kontrola_wynik = 0.0;
        wynik = 0.0;
        rekord_wlasny = 100.0;
        rekord_lokalny = 100.0;
        rekord_swiata = 100.0;
        pauza = true;
        cofniecia = 0;
        kontrola_cofniecia = 0;
    }
};

extern StanEkranu stanGry;