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


//JG:Nie chcialo mi sie robic na to nowego pliku. Mam nadzieje, ze Wam to nie przeszkada. Ogolnie baza czesto uzywanych zmiennych do ,,globalnego" zasiegu.
class PakietZmiennych {
public:
    char* uzytkownik;//JG:nazwa biezacego uzytkownika
    bool koniec;//JG:czy program ma wyjsc z glownej petli i zakonczyc dzialanie
    float mysz_x;//JG:pozycja X myszy w tej klatce
    float mysz_y;//JG:pozycja Y myszy w tej klatce
    float mysz_pop_x;//JG:pozycja X myszy w poprzedniej klatce
    float mysz_pop_y;//JG:pozycja Y myszy w poprzedniej klatce
    char kurosr_czulosc;//JG:bez tego kursor miga, uzywane by odczekac 1 klatke przed zmiana kursora na doymslny od czasu najechania na cos co np zmienilo go w lapke
    char epizod;//JG:biezacy epizod; zal inta na 4 uzywane liczby
    char epizod_doc;//JG:Sluzy do zmiany epizodu w ustawieniach i z losowania (specjalna funkcja sprawdza czy ep docelowy jest biezacym ep, a jak nie to ustawia biezacy ep i powiazane parametry (w tym grafiki) na docelowy ep.
    char poziom;//JG:
    char poziom_doc;
    double czas;
    double kontrola_czas;
    double limit_czas;
    double kontrola_wynik;
    double wynik;
    double rekord_wlasny;
    double rekord_lokalny;
    double rekord_swiata;
    bool pauza;
    char pauza_czulosc;
    int cofniecia;
    int kontrola_cofniecia;
    int limit_cofniecia;
    char trudnosc_labirynt;
    char trudnosc_pytania;
    /*JG:TRUDNOSCI:
        a)labirynty:
        '0' - poczatkujacy
        'l' - latwy
        'n' - normalny
        't' - trudny
        'm' - mistrzowski
        b)pytania:
        '2' - do klasy 3
        '6' - do klasy 8
        's' - podstawowka + liceum + pare pytan wiedzy hobbistycznej i poziomu akademickiego
    Do ewentualnych zmian.
    */
    float glosnosc;//zmienna pod glosnosc, suwak z rozgrywki podpiety
    
    char wyzwanie;
    double punkty;
    double punkty_wymagane;
    char odp_zaznaczona;
    char ministan;
    int proba;
    int proba_max;
    char* pytanie_opis;
    char* pytanie;
    char* odp_wytlumaczenie;
    char odp_pop;
    
    //JG:TABLICE POD PRZYCISKI TRYBU GRY
    float LAB_zaczep_dec_przycisku[24];//JG:obszary poboru tekstur
    char LAB_czulosc_przycisku[9];//JG:liczniki odliczajace do 0 przed mozliwoscia ponownego klikniecia
    

    PakietZmiennych() {
        uzytkownik = "Rimek Wesolek";
        koniec = false;
        mysz_x = GetMouseX();
        mysz_y = GetMouseY();
        mysz_pop_x = GetMouseX();
        mysz_pop_y = GetMouseY();
        kurosr_czulosc = 0;
        srand(time(NULL));
        epizod_doc = (char)(rand()%4 + 1);
        epizod = 1;
        poziom = 1;
        poziom_doc = 1;
        czas = 0.0;
        kontrola_czas = 0.0;
        limit_czas = 3600.0;
        kontrola_wynik = 0.0;
        wynik = 0.0;
        rekord_wlasny = 100.0;
        rekord_lokalny = 100.0;
        rekord_swiata = 100.0;
        pauza = false;
        pauza_czulosc = 0;
        cofniecia = 0;
        kontrola_cofniecia = 0;
        limit_cofniecia = 20;
        trudnosc_labirynt = '0';
        trudnosc_pytania = '6';
        glosnosc = 50.0f;

        wyzwanie = 'b';
        /*JG:wyzwanie:
        'b' - bezpieczny (pozwala podejsc do quizu drugi raz bez cofania)
        's' - straznik - switch od progu punktowego
        'p' - pulapka - cofa do punktu kontrolnego przy porazce calego quizu
        */
        punkty = 0.0;
        punkty_wymagane = 10.0;
        odp_zaznaczona = 'A';
        ministan = 'q';
        proba = 1;
        proba_max = 5;
        pytanie_opis = "Bladzac w tajemniczym labiryncie w koncu udaje Ci sie odnalezc wyjscie. Czy to juz koniec wedrowki? Czy wreszcie uda Ci sie wydostac i wrocic do swojego swiata? Podchodzisz do drzwi i naciskasz klamke. Zamkniete. Dostrzegasz jednak tajemnicze, wydrazone inskrypcje na drzwiach. Moze to zagadka?\0";
        pytanie = "Ile to 2 * 5 - 7?\nA - 8,\nB - 4,\nC - 3,\nD - 7\0";
        odp_pop = 'C';
        odp_wytlumaczenie = "Z wielka niecierpliwoscia przechodzisz przez otwarte drzwi...\nPoniewaz dwie kupki po 5 jablek to 10 jablek a jak zjemy z tego 7 jablek to zostanie nam ich 3.\0";
        //JG:inicjuje losowe bazy grafik przyciskow po rozpoczeciu gry oraz zeruje ich czulosc
        for (int i = 0; i <24; i++) {
            LAB_zaczep_dec_przycisku[i] = (float)(rand() % 51) * 0.01f * 1000.0f;
        }
        for (int i = 0; i < 9; i++) {
            LAB_czulosc_przycisku[i] = 0;
        }
    }
};

extern StanEkranu stanGry;