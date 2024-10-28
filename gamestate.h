#pragma once
enum StanEkranu {
    MAIN_MENU = 0,
    USTAWIENIA,
    TWÓRCY,
    // Dodajcie tutaj nowe stany, jak je utworzycie.
    // Przez stan mam na myśli inne "menu", np
    // gdy Miłosz zrobi menu instrukcji, doda tu stan
    // i może go nazwie INSTRUKCJA
    // potem dodać do switcha w Rysowanie() i Update(), na dole pod mainem,
    EXIT // Na koniec - wyjście.
};

extern StanEkranu stanGry;