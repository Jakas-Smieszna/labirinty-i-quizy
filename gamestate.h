#pragma once
#include <ctime>
#include <cstdlib>
#include <string>
#include "raylib.h"
#include <vector>
#include "Poziom.h"


//Zdjecia kotka nie jest nasze :D
#define TOL (double)(1e-12)

enum StanEkranu {
    MAIN_MENU = 0,
    WYBOR_POZIOMU,
    USTAWIENIA,
    TWORCY,
    // Dodajcie tutaj nowe stany, jak je utworzycie.
    // Przez stan mam na myśli inne "menu", np
    // gdy Miłosz zrobi menu instrukcji, doda tu stan
    INSTRUKCJA,// i może go nazwie INSTRUKCJA
    WYBOR_UZYTKOWNIKA,
    // potem dodać do switcha w Rysowanie() i Update(), na dole pod mainem,
    GRA_LABIRYNT = 7,//JG:labirynt
    GRA_QUIZ = 8,//JG:quiz
    PODSUMOWANIE = 9,//JG:podsumowanie porazki/zwyciestwa poziomu
    EXIT // Na koniec - wyjście.
};
extern StanEkranu stanGry;

//JG:Nie chcialo mi sie robic na to nowego pliku. Mam nadzieje, ze Wam to nie przeszkada. Ogolnie baza czesto uzywanych zmiennych do ,,globalnego" zasiegu.
class PakietZmiennych {
public:

    Poziom poziomik;//JG:Nasz poziom przechowywany
    int biezacy_etap;//JG:Biezacy etap przechodzonego poziomu (miejsce w tablicy etapow poziomu)
    int biezacy_labirynt;//JG:Indeks biezacego/ostatniego labiryntu w tablicy labiryntow
    int biezacy_quiz;//JG:Indeks biezacego/ostatniego quizu w tablicy quizow

    std::string nazwa_uzytkownika;//MF: Aktualna nazwa uzytkownika
    std::vector<std::string> users;//MF: lista wszystkich uzytkownikow - w przyszlosci mozliwa do edytowania
    bool koniec;//JG:czy program ma wyjsc z glownej petli i zakonczyc dzialanie
    float mysz_x;//JG:pozycja X myszy w tej klatce
    float mysz_y;//JG:pozycja Y myszy w tej klatce
    float mysz_pop_x;//JG:pozycja X myszy w poprzedniej klatce
    float mysz_pop_y;//JG:pozycja Y myszy w poprzedniej klatce

    float plansza_x;//JG:przesuniecie planszy wzdluz x
    float plansza_y;//JG:przesuniecie planszy wzdluz y

    int* L_widzialnosc;//JG:istnieje potrzeba by dane w obiekcie Labirynt byly nienaruszone, wiec modyfikacji podczas rozgrywki musza podlegac ich kopie.
    int* L_widzialnosc_N;//JG:dlugosci powyzszej tablicy dla wszystkich labiryntow
    char* L_etapy_znikania;//JG:istnieje potrzeba by dane w obiekcie Labirynt byly nienaruszone, wiec modyfikacji podczas rozgrywki musza podlegac ich kopie.
    int* L_etapy_znikania_N;//JG:dlugosci powyzszej tablicy dla wszystkich labiryntow
    char* L_zmienne_pomocnicze;//JG:istnieje potrzeba by dane w obiekcie Labirynt byly nienaruszone, wiec modyfikacji podczas rozgrywki musza podlegac ich kopie.
    int* L_zmienne_pomocnicze_N;//JG:dlugosci powyzszej tablicy dla wszystkich labiryntow
    int* L_wiatraki_N;//JG:dlugosci tablic wiatrakow w danym labiryncie
    int* L_wiatraki_przyspieszane_N;//JG:dlugosci tablic etapow_wiatrakow w danym labiryncie
    Jez_dane_dyn* L_jeze_dyn;//JG:dynamiczna tablica odzwierciedlajaca dane dla jezykow ktore sa odczytywane z poziomu przy kazdej probie a nastepnie aktualizowane
    int* L_jeze_dyn_N;//JG:dlugosci powyzszej tablicy dla wszystkich labiryntow
    double L_przesuniecie_kontroli_czasu;//JG:pozwala uzaleznic odliczanie od pewnego momentu czasu

    char kurosr_czulosc;//JG:bez tego kursor miga, uzywane by odczekac 1 klatke przed zmiana kursora na doymslny od czasu najechania na cos co np zmienilo go w lapke
    char epizod;//JG:biezacy epizod; zal inta na 4 uzywane liczby
    char epizod_doc;//JG:Sluzy do zmiany epizodu w ustawieniach i z losowania (specjalna funkcja sprawdza czy ep docelowy jest biezacym ep, a jak nie to ustawia biezacy ep i powiazane parametry (w tym grafiki) na docelowy ep.
    char poziom;//JG:chyba nie zrobimy wiecej niz 5 poziomow na epizod wiec int nie jest tu potrzebny (a poza tym, kto nie lubi czarow?)
    char poziom_doc;//JG:Dziala (nie ma jeszcze funkcji w przeciwienstwie) analogicznie jak epizod_doc tylko dla poziomow
    double czas;//JG:licznik czasu; liczenie na klatke zamiast czasomierzem systemowym jest sprawiedliwsze, bo uwzglednia poslizg zaciec, nierownomiernego tempa realizacji klatek itp
    double kontrola_czas;//JG:czas z punkty kontrolnego, wczytywany przy cofnieciu - wynik i tak sie obnizy z powodu wiekszej liczby cofniec
    double limit_czas;//JG:jesli nie przejdziesz poziomu w wyznaczonym czasie, przegrywasz, chociaz pelni to raczej funkcje ogranicznika dlugosci wyswietlanej liczby niz dodatkowego wyzwania
    double kontrola_wynik;//JG:wynik przywracany po cofnieciu do punktu kontrolnego
    double wynik;//JG:biezacy wynik gracza
    double rekord_wlasny;//JG:najlepszy wynik biezacego gracza na tym poziomie przy biezacych ustawieniach trudnosci
    double rekord_lokalny;//JG:najlepszy wynik dowolnego gracza ze wszystkich dostepnych na urzadzeniu uzytkownikow na tym poziomie przy biezacych ustawieniach trudnosci
    double rekord_swiata;//JG:najlepszy wynik w chmurze (najlepszy na podlaczonym do sieci swiecie) na tym poziomie przy biezacych ustawieniach trudnosci
    bool pauza;//JG:czy pauza aktywna / ruch nieaktywny
    char pauza_czulosc;//JG:odlicza klatki nim mozna bedzie zmienic ustawienie / uzyc przycisku ponownie
    int opoznienie;//JG:zmienna do odliczania klatek po zbiciu gracza
    int cofniecia;//JG:liczba cofniec do punktow kontrolnych podczas biezacej rozgrywki
    int limit_cofniecia;//JG:limit cofniec na poziomie, ktorego wyczzerpanie oznacza porazke
    char trudnosc_labirynt;//JG:trudnosc labiryntow
    char trudnosc_pytania;//JG:zakres pytan
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
    float glosnosc;//JG:zmienna pod glosnosc, suwak z rozgrywki podpiety
    
    char wyzwanie;//JG:poziom konsekwencji za niepowodzenie qizu
    /*JG:wyzwanie:
       'b' - bezpieczny (pozwala podejsc do quizu drugi raz bez cofania)
       's' - straznik - switch od progu punktowego
       'p' - pulapka - cofa do punktu kontrolnego przy porazce calego quizu
       */
    double punkty;//JG:punkty uzyskane za odpowiedzi w czasie biezacego quizu
    double punkty_odpowiedzi[4] = {};//JG:tablica z punktami za odpowiedzi
    double punkty_straznik;//JG:zawiera ilosc punktow po zdobyciu ktorej gracz jest bezpieczny przy porazce quizu (dotyczy wyzwania 's')
    double punkty_wymagane;//JG:punkty wymagane do pomyslnego przejsca quizu
    char odp_zaznaczona;//JG:zaznaczona obecnie odpowiedz (domyslnie A)
    char ministan;//JG:pelni funkcje analogiczna do stanGry, ale na podpoziomie poszczegolnych stanow
    /*QUIZY:
        'q' - faza pytania
        'd' - faza uzyskania wytlumaczenia odpowiedzi po pytaniu
        'u' - ostatnie 'd' quizu gdy ukonczony
    */
    int proba;//JG:numer pytania w biezacym quizie - wsn, ktore to pytanie w serii
    int proba_max;//JG:maksymalna liczba pytan w serii - po wyczerpaniu przegrywasz quiz i ponosisz konsekwencje zalezne od wyzwania; na koncu znak '\0'
    int fabula_quizu_ID;/*JG:ktory typ fabuly do pytania, od tego zalezy min naglowek oraz pozniej przy wczytywaniu z bazy tekst fabularny quizu
        1 - zamkniete drzwi (wyzwanie: 'b')
    */
    char* pytanie_opis;//JG:caly tekst opisu fabularnego pytania
    char* pytanie;//JG:caly tekst pytania z odpowiedziami; dzielony na 5 segmentow - w tym 4 z odpowiedziami i 1 z pytaniem; segmenty oddzielone znakie '\n'; na koncu znak '\0'
    char* odp_opis[5];/*JG: 5 tekstow uzaleznionych od poprawnosci obranej odpowiedzi - fabula
        0 - koniec quizu: zwyciestwo - prog punktowy osiagniety
        1 - etap quizu: najlepsza odpowiedz
        2 - etap quizu: odpowiedz punktowana ale nie w pelni poprawna odpowiedz
        3 - etap quizu: odpowiedz bez punktow
        4 - koniec quizu: niepowodzenie (brak mozliwosci uzyskania progu punktowego w liczbie dostepnych prob)
    */
    char* odp_wytlumaczenie;/*JG:caly tekst wytlumaczenia wraz z opisem fabularnym odzielone na 5 segmentow, analogicznie jak pytanie :
        1. - opis zagadnienia
        2. - opis odpowiedzi A
        3. - opis odpowiedzi B
        4. - opis odpowiedzi C
        5. - opis odpowiedzi D
    */
    char odp_pop;//JG:poprawna odpowiedz
    
    //JG:TABLICE POD PRZYCISKI TRYBU GRY
    float LAB_zaczep_dec_przycisku[30];//JG:obszary poboru tekstur (po 2 na przycisk, 1 dla x, 1 dla y)
    char LAB_czulosc_przycisku[12];//JG:liczniki odliczajace do 0 przed mozliwoscia ponownego klikniecia (po 1 na prycisk, nie wszystkie uzywaja)
    

    PakietZmiennych() {//inicjalizacja zmiennych po uruchmoieniu (wiele ma teraz wartosci testowe)


        L_widzialnosc = NULL;
        L_widzialnosc_N = NULL;
        L_etapy_znikania = NULL;
        L_etapy_znikania_N = NULL;
        L_zmienne_pomocnicze = NULL;
        L_zmienne_pomocnicze_N = NULL;
        L_wiatraki_N = NULL;
        L_wiatraki_przyspieszane_N = NULL;
        L_jeze_dyn = NULL;
        L_jeze_dyn_N = NULL;
        L_przesuniecie_kontroli_czasu = 0.0;


        limit_cofniecia = 25;
        limit_czas = 600.0;
        poziomik.etapy = new char[5] {'l', 'q', 'l', 'q', '='};
        //LABIRYNT 1
        Element* l1_elementy = new Element[20];
        //Jez* l1_jeze = new Jez[3];
        //Wiatrak* l1_wiatraki = new Wiatrak[13];
        int licznik = 0;
        int NOWY_ID_pole = 0;
        int NOWY_ID_wiatrak = 0;
        int NOWY_ID_odbiornik = 0;//JG: ta zmienna moze byc roznie ustawiana przy inicjalizacji poziomu by przypisywac ta sama komorke tablicy odbiornikow roznym elementom
        int NOWY_ID_przyspieszane_wiatraki = 0;
        int NOWY_ID_jeze = 0;
        float obecny_x = 0.0f;
        float obecny_y = 0.0f;
        for (licznik; licznik < 1; licznik++) {
            l1_elementy[licznik].typ_tab = new char[3] {'p', 's', '-'};
            l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            l1_elementy[licznik].x = obecny_x;
            l1_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 16; licznik++) {
            
            if (licznik != 1 && licznik != 9) {
                l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                //l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_pole, NOWY_ID_wiatrak, 0, NOWY_ID_przyspieszane_wiatraki};
                //l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'h';
                //NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                //NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
            }
            else {
                l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_odbiornik};
                NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
            }

            NOWY_ID_pole = NOWY_ID_pole + 1;
            if (licznik == 1
                || (licznik >= 4 && licznik <= 5)
                || (licznik >= 8 && licznik <= 9)
                || (licznik >= 12 && licznik <= 13)) {
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
            }
            else if ((licznik >= 2 && licznik <= 3)
                || (licznik >= 14 && licznik <= 15)) {
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
            }
            else if ((licznik >= 6 && licznik <= 7)
                || (licznik >= 10 && licznik <= 11)) {
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
            }
            l1_elementy[licznik].x = obecny_x;
            l1_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 17; licznik++) {
            l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
            l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
            l1_elementy[licznik].x = obecny_x;
            l1_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 18; licznik++) {
            l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
            l1_elementy[licznik].ID_tab = new int[3] {1, 1, NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
            l1_elementy[licznik].x = obecny_x;
            l1_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 19; licznik++) {
            l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
            l1_elementy[licznik].ID_tab = new int[3] {0, 0, NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            obecny_x = obecny_x - 4 * ODLEGLOSC_MIEDZY_POLAMI;
            l1_elementy[licznik].x = obecny_x;
            l1_elementy[licznik].y = obecny_y;
        }

        /*for (int i = 0; i < 3; i++) {

            l1_jeze[i].okreslnik = 'f';

            l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
            l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
            NOWY_ID_jeze = NOWY_ID_jeze + 1;
            l1_elementy[licznik].x = obecny_x;
            l1_elementy[licznik].y = obecny_y;
            obecny_x = obecny_x + 4 * ODLEGLOSC_MIEDZY_POLAMI;

            licznik++;

        }*/

        for (licznik; licznik < 20; licznik++) {
            l1_elementy[licznik].typ_tab = new char[1] {'='};
        }
        Pole* l1_pola = new Pole[19];

        L_wiatraki_N = new int[2] {0, 0};
        L_wiatraki_przyspieszane_N = new int[2] {0, 0};

        L_jeze_dyn_N = new int[2] {0, 0};

        //int* l1_etapy_wiatraki = new int[13];


        int* l1_widzialnosc = new int[2] {0, 0};

        char* l1_zmienne_pomocnicze = new char[2] {'d', 'd'};

        //LABIRYNT 2
        Element* l2_elementy = new Element[6];
        //Wiatrak* l2_wiatraki = new Wiatrak[2];
        licznik = 0;
        NOWY_ID_pole = 0;
        int NOWY_ID_etapy_znikania = 0;
        int NOWY_ID_widzialnosc = 0;
        int NOWY_ID_znikanie_czas = 0;
        int NOWY_ID_pojawiajace_czas = 0;
        NOWY_ID_odbiornik = 0;
        obecny_x = 0.0f;
        obecny_y = 0.0f;

        for (licznik; licznik < 1; licznik++) {
            l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
            l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            l2_elementy[licznik].x = obecny_x;
            l2_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 2; licznik++) {
            l2_elementy[licznik].typ_tab = new char[8] {'w', 'a', 'o', 'a', 'z', 'a', 'y', '-'};
            l2_elementy[licznik].ID_tab = new int[9] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_pole, NOWY_ID_odbiornik};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            NOWY_ID_odbiornik = NOWY_ID_odbiornik + 0;
            NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
            NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
            NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 2;
            NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 3;
            obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
            l2_elementy[licznik].x = obecny_x;
            l2_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 4; licznik++) {
            //l2_elementy[licznik].typ_tab = new char[4] {'q', 'a', 'p', '-'};
            //l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_pole};
            l2_elementy[licznik].typ_tab = new char[11] {'w', 'a', 'o', 'b', 'd', 'v', 'd', 'a', 'z', 'p', '-'};
            l2_elementy[licznik].ID_tab = new int[11] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_odbiornik, NOWY_ID_znikanie_czas + 1, NOWY_ID_odbiornik, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 2, NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            //NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
            NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
            NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
            NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 3;
            NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 3;
            obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
            l2_elementy[licznik].x = obecny_x;
            l2_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 5; licznik++) {
            l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
            l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
            l2_elementy[licznik].x = obecny_x;
            l2_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 6; licznik++) {
            l2_elementy[licznik].typ_tab = new char[1] {'='};
        }

        Pole* l2_pola = new Pole[5];

        int* l2_widzialnosc = new int[3] {0,0,0};
        L_widzialnosc = NULL;
        L_widzialnosc_N = new int[2] {2,3};

        char* l2_etapy_znikania = new char[3] {1, 1, 1};
        L_etapy_znikania = NULL;
        L_etapy_znikania_N = new int[2] {0, 3};//new int[2] {0, 0};


        char* l2_zmienne_pomocnicze = new char[1] {'b'};
        L_zmienne_pomocnicze = NULL;
        L_zmienne_pomocnicze_N = new int[2] {2, 1};


        double* l2_zapadnie_czas = new double[8] {2.7, 7.8, 3.4, 8.1, 15.0, 4.1, 8.4, 16.0};
        double* l2_pojawiajace_czas = new double[9] {0.7, 5.8, 9.0, 1.4, 6.1, 10.0, 2.1, 6.4, 11.0};

        poziomik.labirynty = new Labirynt[2]{
            Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, NULL, NULL, NULL, NULL, NULL, l1_widzialnosc, NULL),
            Labirynt(l2_elementy, l2_pola, l2_zmienne_pomocnicze, l2_zapadnie_czas, l2_pojawiajace_czas, NULL, NULL, l2_etapy_znikania, l2_widzialnosc, NULL) };

        int* q1_zakresyID = new int[2] {1, 7};
        int* q2_zakresyID = new int[2] {3, 10};
        poziomik.quizy = new Quiz[2]{ 
            Quiz(q1_zakresyID, 'b', 1, 5, 10.0, 0.0), 
            Quiz(q2_zakresyID, 's', 1, 6, 12.0, 6.0) };







        biezacy_etap = 0;
        biezacy_labirynt = 0;
        biezacy_quiz = 0;

        nazwa_uzytkownika = "Uzytkownik1";
        users = { "Uzytkownik1", "Uzytkownik2", "Uzytkownik3", "Uzytkownik4", "Uzytkownik5" };
        koniec = false;
        mysz_x = GetMouseX();
        mysz_y = GetMouseY();
        mysz_pop_x = GetMouseX();
        mysz_pop_y = GetMouseY();

        plansza_x = 0.0f;
        plansza_y = 0.0f;

        kurosr_czulosc = 0;
        srand(time(NULL));
        epizod_doc = (char)(rand() % 4 + 1);//JG:losuje epizod pod tlo po uruchomieniu, dotyczy szaty graficznej, poziomy z dalszych epizodow beda zablokowane w wyborze poziomow
        //epizod_doc = 1; //AG usunalem losowanie bo nie ma sensu losować poziomu trudnosci, niech bedzie lvl 1 diff na poczatku
        epizod = 0;
        poziom = 1;
        poziom_doc = 1;
        czas = 0.0;
        kontrola_czas = 0.0;
        kontrola_wynik = 0.0;
        wynik = 0.0;
        rekord_wlasny = 100.0;
        rekord_lokalny = 100.0;
        rekord_swiata = 100.0;
        pauza = false;
        pauza_czulosc = 0;
        opoznienie = 0;
        cofniecia = 0;
        trudnosc_labirynt = '0';
        trudnosc_pytania = '6';
        glosnosc = 50.0f;

        wyzwanie = 's';

        punkty = 0.0;
        punkty_wymagane = 10.0;
        punkty_straznik = 5.0;
        odp_zaznaczona = 'A';
        ministan = 'q';
        proba = 1;
        proba_max = 5;
        fabula_quizu_ID = 1;
        pytanie_opis = "Bladzac w tajemniczym labiryncie w koncu udaje Ci sie odnalezc wyjscie. Czy to juz koniec wedrowki? Czy wreszcie uda Ci sie wydostac i wrocic do swojego swiata? Podchodzisz do drzwi i naciskasz klamke. Zamkniete. Dostrzegasz jednak tajemnicze, wydrazone inskrypcje na drzwiach. Moze to zagadka?\0";
        pytanie = NULL;
        //pytanie = "Ile to 2 * 5 - 7 ? \nA - 8,\nB - 4,\nC - 3,\nD - 7\0";
        odp_pop = 'C';
        for (int i = 0; i < 4; i++) {
            punkty_odpowiedzi[i] = 0.0;
        }
        //punkty_odpowiedzi[int(odp_pop -'A')] = 5.0;
        //punkty_odpowiedzi[1] = 1.0;//JG:Odpowiedz B, bo najblizsza poprawnej
        odp_opis[0] = "Udało Ci się w pełni rozpracować szyfr! Wypowiadasz magiczne słowa i drzwi otwierają się na tyle, że możesz przejść. Z wielka niecierpliwoscia przechodzisz na drugą stronę...";
        odp_opis[1] = "Wypowiadasz magiczne słowa i drzwi się otwieraja, jednak tylko przez parę sekund.Szpara jest za mała by się prześlizgnąć, więc trzeba próbować dalej.";
        odp_opis[2] = "Wypowiadasz magiczne słowa i naciskasz klamke. Drzwi się otwieraja. Ale tylko przez ułamek sekundy.Trzeba będzie spróbować ponownie.";
        odp_opis[3] = "Wypowiadasz magiczne słowa - rozwiązanie zagadki i naciskasz klamkę, ale drzwi się nie otwierają...";
        odp_opis[4] = "Dość!Kopiesz drzwi z całej siły, jednak ten argument do nich nie przemawia.Za to do komórek nerwowych twojej stopy już tak...";
        odp_wytlumaczenie = NULL;
        //odp_wytlumaczenie = "Poniewaz dwie kupki po 5 jablek to 10 jablek a jak zjemy z tego 7 jablek to zostanie nam ich 3.\nA - niepoprawna (0pkt)\nB - niepoprawna, ale rozni sie tylko o 1 od poprawnej (1pkt)\nC - poprawna (5pkt)\nD - niepoprawna (0pkt)\0";
        //JG:inicjuje losowe bazy grafik przyciskow po rozpoczeciu gry oraz zeruje ich czulosc  
        for (int i = 0; i <30; i++) {
            LAB_zaczep_dec_przycisku[i] = (float)(rand() % 51) * 0.01f * 1000.0f;
        }
        for (int i = 0; i < 12; i++) {
            LAB_czulosc_przycisku[i] = 0;
        }
    }

    void D_Zmienne(){
        
        if (odp_wytlumaczenie != NULL) delete odp_wytlumaczenie;
        if (pytanie != NULL) delete pytanie;
        if (L_widzialnosc != NULL) delete[] L_widzialnosc;
        if (L_widzialnosc_N != NULL) delete[] L_widzialnosc_N;
        if (L_etapy_znikania != NULL) delete[] L_etapy_znikania;
        if (L_etapy_znikania_N != NULL) delete[] L_etapy_znikania_N;
        if (L_zmienne_pomocnicze != NULL) delete[] L_zmienne_pomocnicze;
        if (L_zmienne_pomocnicze_N != NULL) delete[] L_zmienne_pomocnicze_N;
        if (L_wiatraki_N != NULL) delete[] L_wiatraki_N;
        if (L_wiatraki_przyspieszane_N != NULL) delete[] L_wiatraki_przyspieszane_N;
        if (L_jeze_dyn != NULL) delete[] L_jeze_dyn;
        if (L_jeze_dyn_N != NULL) delete[] L_jeze_dyn_N;

    }


    //JG: przestawia dane poziomu z biezacych na nowe. (Lepiej by wygladalo w oddzielnym pliku ale juz latwiej dac to tu - mniej pisania).
    void PRZELADUJ_POZIOM() {

        //Czyszczenie
        poziomik.D_Poziom();
        D_Zmienne();

        odp_wytlumaczenie = NULL;
        pytanie = NULL;
        L_widzialnosc = NULL;
        L_widzialnosc_N = NULL;
        L_etapy_znikania = NULL;
        L_etapy_znikania_N = NULL;
        L_zmienne_pomocnicze = NULL;
        L_zmienne_pomocnicze_N = NULL;
        L_wiatraki_N = NULL;
        L_wiatraki_przyspieszane_N = NULL;
        L_jeze_dyn = NULL;
        L_jeze_dyn_N = NULL;
        L_przesuniecie_kontroli_czasu = 0.0;

        Element* l1_elementy = NULL;
        Element* l2_elementy = NULL;
        Element* l3_elementy = NULL;
        Element* l4_elementy = NULL;
        Element* l5_elementy = NULL;

        int pom = 0;
        int* tab_pom = NULL;

        int NOWY_ID_wiatrak = 0;
        int NOWY_ID_przyspieszane_wiatraki = 0;
        int licznik = 0;
        int NOWY_ID_pole = 0;
        int NOWY_ID_odbiornik = 0;//JG: ta zmienna moze byc roznie ustawiana przy inicjalizacji poziomu by przypisywac ta sama komorke tablicy odbiornikow roznym elementom
        int NOWY_ID_etapy_znikania = 0;
        int NOWY_ID_widzialnosc = 0;
        int NOWY_ID_znikanie_czas = 0;
        int NOWY_ID_pojawiajace_czas = 0;
        int NOWY_ID_jeze = 0;
        
        float obecny_x = 0.0f;
        float obecny_y = 0.0f;

        Pole* l1_pola = NULL;
        Jez* l1_jeze = NULL;
        Wiatrak* l1_wiatraki = NULL;
        int* l1_widzialnosc = NULL;
        char* l1_zmienne_pomocnicze = NULL;
        char* l1_etapy_znikania = NULL;
        double* l1_zapadnie_czas = NULL;
        double* l1_pojawiajace_czas = NULL;
        int* l1_etapy_wiatraki = NULL;

        Pole* l2_pola = NULL;
        Jez* l2_jeze = NULL;
        Wiatrak* l2_wiatraki = NULL;
        int* l2_widzialnosc = NULL;
        char* l2_zmienne_pomocnicze = NULL;
        char* l2_etapy_znikania = NULL;
        double* l2_zapadnie_czas = NULL;
        double* l2_pojawiajace_czas = NULL;
        int* l2_etapy_wiatraki = NULL;

        Pole* l3_pola = NULL;
        Jez* l3_jeze = NULL;
        Wiatrak* l3_wiatraki = NULL;
        int* l3_widzialnosc = NULL;
        char* l3_zmienne_pomocnicze = NULL;
        char* l3_etapy_znikania = NULL;
        double* l3_zapadnie_czas = NULL;
        double* l3_pojawiajace_czas = NULL;
        int* l3_etapy_wiatraki = NULL;

        Pole* l4_pola = NULL;
        Jez* l4_jeze = NULL;
        Wiatrak* l4_wiatraki = NULL;
        int* l4_widzialnosc = NULL;
        char* l4_zmienne_pomocnicze = NULL;
        char* l4_etapy_znikania = NULL;
        double* l4_zapadnie_czas = NULL;
        double* l4_pojawiajace_czas = NULL;
        int* l4_etapy_wiatraki = NULL;

        Pole* l5_pola = NULL;
        Jez* l5_jeze = NULL;
        Wiatrak* l5_wiatraki = NULL;
        int* l5_widzialnosc = NULL;
        char* l5_zmienne_pomocnicze = NULL;
        char* l5_etapy_znikania = NULL;
        double* l5_zapadnie_czas = NULL;
        double* l5_pojawiajace_czas = NULL;
        int* l5_etapy_wiatraki = NULL;

        int* q1_zakresyID = NULL;
        int* q2_zakresyID = NULL;
        int* q3_zakresyID = NULL;
        int* q4_zakresyID = NULL;

        switch (epizod) {
        default:
        case 1://EPIZOD 1

            switch (poziom) {
            default:
            case 1://POZIOM 1 EPIZOD 1

                limit_cofniecia = 25;
                limit_czas = 600.0;
                poziomik.etapy = new char[5] {'l', 'q', 'l', 'q', '='};
                //LABIRYNT 1
                l1_elementy = new Element[20];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_odbiornik = 0;//JG: ta zmienna moze byc roznie ustawiana przy inicjalizacji poziomu by przypisywac ta sama komorke tablicy odbiornikow roznym elementom
                obecny_x = 0.0f;
                obecny_y = 0.0f;
                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', 's', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {

                    if (licznik != 1 && licznik != 9) {
                        l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                        l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    }
                    else {
                        l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                        l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_odbiornik};
                        NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    }

                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    if (licznik == 1
                        || (licznik >= 4 && licznik <= 5)
                        || (licznik >= 8 && licznik <= 9)
                        || (licznik >= 12 && licznik <= 13)) {
                        obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    }
                    else if ((licznik >= 2 && licznik <= 3)
                        || (licznik >= 14 && licznik <= 15)) {
                        obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    }
                    else if ((licznik >= 6 && licznik <= 7)
                        || (licznik >= 10 && licznik <= 11)) {
                        obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    }
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {1, 1, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {0, 0, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 20; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }
                l1_pola = new Pole[19];

                L_wiatraki_N = new int[2] {0, 0};
                L_wiatraki_przyspieszane_N = new int[2] {0, 0};

                L_jeze_dyn_N = new int[2] {0, 0};

                l1_widzialnosc = new int[2] {0, 0};

                l1_zmienne_pomocnicze = new char[2] {'d', 'd'};

                //LABIRYNT 2
                l2_elementy = new Element[6];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[8] {'w', 'a', 'o', 'a', 'z', 'a', 'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[9] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 0;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 2;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 3;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[11] {'w', 'a', 'o', 'b', 'd', 'v', 'd', 'a', 'z', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[11] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_odbiornik, NOWY_ID_znikanie_czas + 1, NOWY_ID_odbiornik, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 2, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 3;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 3;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 6; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l2_pola = new Pole[5];

                l2_widzialnosc = new int[3] {0, 0, 0};
                L_widzialnosc = NULL;
                L_widzialnosc_N = new int[2] {2, 3};

                l2_etapy_znikania = new char[3] {1, 1, 1};
                L_etapy_znikania = NULL;
                L_etapy_znikania_N = new int[2] {0, 3};//new int[2] {0, 0};


                l2_zmienne_pomocnicze = new char[1] {'b'};
                L_zmienne_pomocnicze = NULL;
                L_zmienne_pomocnicze_N = new int[2] {2, 1};


                l2_zapadnie_czas = new double[8] {2.7, 7.8, 3.4, 8.1, 15.0, 4.1, 8.4, 16.0};
                l2_pojawiajace_czas = new double[9] {0.7, 5.8, 9.0, 1.4, 6.1, 10.0, 2.1, 6.4, 11.0};

                L_wiatraki_N = new int[2] {0, 0};
                L_wiatraki_przyspieszane_N = new int[2] {0, 0};
                L_jeze_dyn_N = new int[2] {0, 0};

                poziomik.labirynty = new Labirynt[2]{
                    Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, NULL, NULL, NULL, NULL, NULL, l1_widzialnosc, NULL),
                    Labirynt(l2_elementy, l2_pola, l2_zmienne_pomocnicze, l2_zapadnie_czas, l2_pojawiajace_czas, NULL, NULL, l2_etapy_znikania, l2_widzialnosc, NULL) };

                q1_zakresyID = new int[2] {1, 7};
                q2_zakresyID = new int[2] {3, 10};
                poziomik.quizy = new Quiz[2]{
                    Quiz(q1_zakresyID, 'b', 1, 5, 10.0, 0.0),
                    Quiz(q2_zakresyID, 's', 1, 6, 12.0, 6.0) };

                break;//KONIEC - POZIOM 1 EPIZOD 1

            case 2://POZIOM 2 EPIZOD 1

                limit_cofniecia = 10;
                limit_czas = 600.0;
                poziomik.etapy = new char[5] {'q', 'l', 'q', 'l', '='};
                //LABIRYNT 1
                l1_elementy = new Element[37];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = rand() % 3;
                obecny_x = 0.0f;
                obecny_y = 0.0f;


                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 2; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    if (NOWY_ID_odbiornik == 3) NOWY_ID_odbiornik = 0;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 3; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 4; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    if (NOWY_ID_odbiornik == 3) NOWY_ID_odbiornik = 0;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 5; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    if (NOWY_ID_odbiornik == 3) NOWY_ID_odbiornik = 0;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 8; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 10; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 12; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 22; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 24; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 28; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 30; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 32; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 33; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x + 7 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 34; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 0, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 35; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 1, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 36; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'x', 'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 2, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 37; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l1_pola = new Pole[36];

                l1_widzialnosc = new int[30];
                for (int i = 0; i < 29; i ++){                    
                    l1_widzialnosc[i] = 0;
                }
                l1_widzialnosc[29] = -1;


                L_widzialnosc = NULL;
                L_widzialnosc_N = new int[2] {30, 12};

                l1_etapy_znikania = new char[27] {1};
                for (int i = 0; i < 27; i++) {
                    l1_etapy_znikania[i] = 1;
                }
                L_etapy_znikania = NULL;
                L_etapy_znikania_N = new int[2] {27, 0};


                l1_zmienne_pomocnicze = new char[3] {'d', 'd', 'd'};
                L_zmienne_pomocnicze = NULL;
                L_zmienne_pomocnicze_N = new int[2] {3, 0};


                l1_zapadnie_czas = new double[27];
                for (int i = 0; i < 27; i++) {
                    l1_zapadnie_czas[i] = 8.0 + 2.0 * double(i);
                }
                l1_pojawiajace_czas = new double[27];
                for (int i = 0; i < 27; i++) {
                    l1_pojawiajace_czas[i] = 5.0 + 2.0 * double(i);
                }

                //LABIRYNT 2
                l2_elementy = new Element[26];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_odbiornik = rand() % 3;
                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 3; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 6; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 8; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 9; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 10; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 12; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 14; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 16; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - 6 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 18; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + 6 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 20; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 21; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - 6 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 22; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 23; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 24; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l2_pola = new Pole[25];

                l2_widzialnosc = new int[12];
                for (int i = 0; i < 12; i++) {
                    l2_widzialnosc[i] = -1;
                }

                l2_zapadnie_czas = new double[6] {0.7, 1.0, 3.0, 2.0, 6.5, 5.5};
                L_wiatraki_N = new int[2] {0, 0};
                L_wiatraki_przyspieszane_N = new int[2] {0, 0};
                L_jeze_dyn_N = new int[2] {0, 0};

                poziomik.labirynty = new Labirynt[2]{
                    Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, l1_zapadnie_czas, l1_pojawiajace_czas, NULL, NULL, l1_etapy_znikania, l1_widzialnosc, NULL),
                    Labirynt(l2_elementy, l2_pola, NULL, l2_zapadnie_czas, NULL, NULL, NULL, NULL, l2_widzialnosc, NULL) };

                q1_zakresyID = new int[2] {1, 26};
                q2_zakresyID = new int[2] {5, 33};
                poziomik.quizy = new Quiz[2]{
                    Quiz(q1_zakresyID, 'b', 1, 3, 10.0, 0.0),
                    Quiz(q2_zakresyID, 'p', 1, 10, 25.0, 0.0) };


                break;//KONIEC - POZIOM 2 EPIZOD 1

            case 3://POZIOM 3 EPIZOD 1

                limit_cofniecia = 30;
                limit_czas = 600.0;
                poziomik.etapy = new char[6] {'l', 'q', 'l', 'q', 'l', '='};
                //LABIRYNT 1
                l1_elementy = new Element[19];
                l1_wiatraki = new Wiatrak[1];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', 's', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 3; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 0};
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'j';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }


                l1_pola = new Pole[18];

                L_widzialnosc = NULL;
                L_widzialnosc_N = new int[3] {0, 0, 4};

                L_etapy_znikania = NULL;
                L_etapy_znikania_N = new int[3] {0, 0, 0};

                l1_zmienne_pomocnicze = new char[1] {'b'};
                L_zmienne_pomocnicze = NULL;
                L_zmienne_pomocnicze_N = new int[3] {1, 1, 4};

                //LABIRYNT 2
                l2_elementy = new Element[27];
                l2_wiatraki = new Wiatrak[10];
                l2_pola = new Pole[26];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                obecny_x = 0.0f;
                obecny_y = 0.0f;

                l2_zmienne_pomocnicze = new char[1] {'b'};

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 3; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 6; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 8; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 10; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 12; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 20; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 21; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 22; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 23; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 24; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 0};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'j';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 27; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }

                L_wiatraki_N = new int[3] {1, 10, 4};
                L_wiatraki_przyspieszane_N = new int[3] {0, 0, 0};
                L_jeze_dyn_N = new int[3] {0, 0, 0};

                //LABIRYNT 3
                l3_elementy = new Element[18];
                l3_wiatraki = new Wiatrak[4];
                l3_pola = new Pole[17];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                obecny_x = 0.0f;
                obecny_y = 0.0f;

                l3_zmienne_pomocnicze = new char[4] {'d', 'd', 'd', 'd'};
                l3_widzialnosc = new int[4] {0, 0, 0, 0};

                for (licznik; licznik < 1; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 3; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 6; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 8; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 2};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 9; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 3};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 10; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 2, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 12; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 0, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 1, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[1] {'='};
                }

                poziomik.labirynty = new Labirynt[3]{
                    Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, NULL, NULL, l1_wiatraki, NULL, NULL, NULL, NULL),
                    Labirynt(l2_elementy, l2_pola, l2_zmienne_pomocnicze, NULL, NULL, l2_wiatraki, NULL, NULL, NULL, NULL),
                    Labirynt(l3_elementy, l3_pola, l3_zmienne_pomocnicze, NULL, NULL, l3_wiatraki, NULL, NULL, l3_widzialnosc, NULL) };

                q1_zakresyID = new int[2] {1, 50};
                q2_zakresyID = new int[2] {1, 50};
                poziomik.quizy = new Quiz[2]{
                    Quiz(q1_zakresyID, 's', 1, 6, 16.0, 8.0),
                    Quiz(q2_zakresyID, 's', 1, 8, 20.0, 10.0) };



                break;//KONIEC - POZIOM 3 EPIZOD 1

            case 4://POZIOM 4 EPIZOD 1


                limit_cofniecia = 20;
                limit_czas = 600.0;
                poziomik.etapy = new char[6] {'q', 'l', 'q', 'l', 'q', '='};
                //LABIRYNT 1
                l1_elementy = new Element[29];
                l1_pola = new Pole[26];
                l1_wiatraki = new Wiatrak[2];
                l1_jeze = new Jez[2];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                L_widzialnosc_N = new int[2] {0, 9};
                L_etapy_znikania_N = new int[2] {0, 0};
                L_zmienne_pomocnicze_N = new int[2] {0, 0};
                L_wiatraki_N = new int[2] {2, 0};
                L_wiatraki_przyspieszane_N = new int[2] {2, 0};
                L_jeze_dyn_N = new int[2] {2, 2};

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 8; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 12; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 15; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 18; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 21; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 22; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, NOWY_ID_przyspieszane_wiatraki};
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'e';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 23; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 24; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, NOWY_ID_przyspieszane_wiatraki};
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'e';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'd';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x + 4 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'f';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (licznik; licznik < 29; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l1_etapy_wiatraki = new int[2];

                //LABIRYNT 2
                l2_elementy = new Element[34];
                l2_pola = new Pole[31];
                l2_jeze = new Jez[2];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 6; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 9; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 10; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 22; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 23; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 30; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - 4 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 31; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'b';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - 8 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'b';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (licznik; licznik < 34; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l2_widzialnosc = new int[9] {-1, -1, -1, -1, -1, -1, -1, -1, -1};
                l2_zapadnie_czas = new double[9] {2.0, 0.8, 0.2, 1.6, 1.8, 3.0, 4.0, 2.8, 2.6};



                poziomik.labirynty = new Labirynt[2]{
                    Labirynt(l1_elementy, l1_pola, NULL, NULL, NULL, l1_wiatraki, l1_etapy_wiatraki, NULL, NULL, l1_jeze),
                    Labirynt(l2_elementy, l2_pola, NULL, l2_zapadnie_czas, NULL, NULL, NULL, NULL, l2_widzialnosc, l2_jeze) };

                q1_zakresyID = new int[2] {1, 50};
                q2_zakresyID = new int[2] {25, 75};
                q3_zakresyID = new int[2] {50, 90};
                poziomik.quizy = new Quiz[3]{
                    Quiz(q1_zakresyID, 'b', 1, 7, 20.0, 0.0),
                    Quiz(q2_zakresyID, 's', 1, 7, 20.0, 10.0),
                    Quiz(q3_zakresyID, 'p', 1, 7, 20.0, 0.0) };

                

                break;//KONIEC - POZIOM 4 EPIZOD 1

            case 5://POZIOM 5 EPIZOD 1

                limit_cofniecia = 26;
                limit_czas = 900.0;
                poziomik.etapy = new char[8] {'l', 'q', 'l', 'q', 'l', 'q', 'l', '='};
                //LABIRYNT 1
                l1_elementy = new Element[26];
                l1_pola = new Pole[25];
                l1_wiatraki = new Wiatrak[1];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                L_widzialnosc_N = new int[4] {24, 0, 3, 37};
                L_etapy_znikania_N = new int[4] {0, 0, 0, 0};
                L_zmienne_pomocnicze_N = new int[4] {0, 0, 4, 0};
                L_wiatraki_N = new int[4] {1, 0, 5, 2};
                L_wiatraki_przyspieszane_N = new int[4] {1, 0, 2, 0};
                L_jeze_dyn_N = new int[4] {0, 3, 3, 6};

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'o', 'p', 's', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 6; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 't', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole, NOWY_ID_wiatrak, NOWY_ID_przyspieszane_wiatraki};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'f';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 10; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 7 * ODLEGLOSC_MIEDZY_POLAMI;
                NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas - 7;
                for (licznik; licznik < 13; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                for (licznik; licznik < 17; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas - 1;
                for (licznik; licznik < 18; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 20; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas - 1;
                for (licznik; licznik < 24; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas - 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                for (licznik; licznik < 25; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l1_zapadnie_czas = new double[10] {0.4, 0.8, 1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3.0, 3.3};
                l1_etapy_wiatraki = new int[10];
                l1_widzialnosc = new int[25];
                for (int i = 0; i < 25; i++) {
                    l1_widzialnosc[i] = -1;
                }


                //LABIRYNT 2
                l2_elementy = new Element[21];
                l2_pola = new Pole[17];
                l2_jeze = new Jez[3];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 6; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 8; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 10; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 12; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'c';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'c';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'c';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (licznik; licznik < 21; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }


                //LABIRYNT 3
                l3_elementy = new Element[31];
                l3_pola = new Pole[27];
                l3_wiatraki = new Wiatrak[5];
                l3_jeze = new Jez[3];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                l3_zmienne_pomocnicze = new char[4] {'b', 'b', 'b', 'd'};

                for (licznik; licznik < 1; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 3; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 5; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[4] {NOWY_ID_pole, NOWY_ID_wiatrak, 0, NOWY_ID_przyspieszane_wiatraki};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'k';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 9; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 10; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 11; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 1};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    l3_wiatraki[NOWY_ID_wiatrak].tempo = 1.1;
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 2};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 17; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 2};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    l3_wiatraki[NOWY_ID_wiatrak].tempo = 1.1;
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 20; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 21; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, NOWY_ID_przyspieszane_wiatraki};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'f';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 22; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 3};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 25; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 27; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l3_jeze[NOWY_ID_jeze].okreslnik = 'e';
                    l3_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l3_jeze[NOWY_ID_jeze].okreslnik = 'd';
                    l3_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l3_jeze[NOWY_ID_jeze].okreslnik = 'c';
                    l3_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (licznik; licznik < 31; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l3_etapy_wiatraki = new int[2];
                l3_widzialnosc = new int[3] {0, 0, 0};

                //LABIRYNT 4
                l4_elementy = new Element[45];
                l4_pola = new Pole[38];
                l4_wiatraki = new Wiatrak[2];
                l4_jeze = new Jez[6];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[5] {'q', 'o', 'p', '<', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 12; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;

                    licznik = licznik + 1;

                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                }
                for (licznik; licznik < 13; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 't', '-'};
                    l4_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    l4_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }



                for (licznik; licznik < 15; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 23; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;

                    licznik = licznik + 1;

                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                }
                for (licznik; licznik < 24; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 't', '-'};
                    l4_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    l4_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }



                for (licznik; licznik < 26; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 34; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;

                    licznik = licznik + 1;

                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                }
                for (licznik; licznik < 35; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 37; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 38; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (int i = 0; i < 3; i++) {

                    obecny_y = obecny_y - 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    {
                        l4_jeze[NOWY_ID_jeze].okreslnik = 'b';
                        l4_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                        l4_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                        NOWY_ID_jeze = NOWY_ID_jeze + 1;
                        l4_elementy[licznik].x = obecny_x;
                        l4_elementy[licznik].y = obecny_y;
                        licznik++;
                    }
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    {
                        l4_jeze[NOWY_ID_jeze].okreslnik = 'b';
                        l4_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                        l4_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                        NOWY_ID_jeze = NOWY_ID_jeze + 1;
                        l4_elementy[licznik].x = obecny_x;
                        l4_elementy[licznik].y = obecny_y;
                        licznik++;
                    }

                }
                for (licznik; licznik < 45; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l4_widzialnosc = new int[37];
                for (int i = 0; i < 37; i++) {
                    l4_widzialnosc[i] = -1;
                }
                l4_zapadnie_czas = new double[25];
                for (int i = 0; i < 9; i++) {
                    l4_zapadnie_czas[i] = 1.0 + 0.2 * double(i);
                }
                for (int i = 9; i < 16; i++) {
                    l4_zapadnie_czas[i] = 2.0 + 0.2 * double(i);
                }
                for (int i = 16; i < 25; i++) {
                    l4_zapadnie_czas[i] = 3.0 + 0.2 * double(i);
                }
         

                poziomik.labirynty = new Labirynt[4]{
                    Labirynt(l1_elementy, l1_pola, NULL, l1_zapadnie_czas, NULL, l1_wiatraki, l1_etapy_wiatraki, NULL, l1_widzialnosc, NULL),
                    Labirynt(l2_elementy, l2_pola, NULL, NULL, NULL, NULL, NULL, NULL, NULL, l2_jeze),
                    Labirynt(l3_elementy, l3_pola, l3_zmienne_pomocnicze, NULL, NULL, l3_wiatraki, l3_etapy_wiatraki, NULL, l3_widzialnosc, l3_jeze),
                    Labirynt(l4_elementy, l4_pola, NULL, l4_zapadnie_czas, NULL, l4_wiatraki, NULL, NULL, l4_widzialnosc, l4_jeze) };

                q1_zakresyID = new int[2] {1, 80};
                q2_zakresyID = new int[2] {1, 80};
                q3_zakresyID = new int[2] {1, 80};
                poziomik.quizy = new Quiz[3]{
                    Quiz(q1_zakresyID, 'p', 1, 9, 27.0, 0.0),
                    Quiz(q2_zakresyID, 'p', 1, 9, 27.0, 0.0),
                    Quiz(q3_zakresyID, 'p', 1, 9, 27.0, 0.0) };


                break;//KONIEC - POZIOM 5 EPIZOD 1

            }

            break;//KONIEC - EPIZOD 1





        case 2://EPIZOD 2

            switch (poziom) {
            default:
            case 1://POZIOM 1 EPIZOD 2

                limit_cofniecia = 21;
                limit_czas = 600.0;
                poziomik.etapy = new char[6] {'q', 'l', 'q', 'l', 'q', '='};
                //LABIRYNT 1
                l1_elementy = new Element[26];
                l1_pola = new Pole[25];
                l1_wiatraki = new Wiatrak[2];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                L_widzialnosc_N = new int[2] {8, 0};
                L_etapy_znikania_N = new int[2] {2, 0};
                L_zmienne_pomocnicze_N = new int[2] {4, 0};
                L_wiatraki_N = new int[2] {2, 0};
                L_wiatraki_przyspieszane_N = new int[2] {0, 0};
                L_jeze_dyn_N = new int[2] {0, 1};

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'c', 'z', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[6] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, 0, NOWY_ID_znikanie_czas, NOWY_ID_pole, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 6; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 8; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 12; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'w', 'c', 'z', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[6] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, 2, NOWY_ID_znikanie_czas, NOWY_ID_pole, 3};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 14; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 2};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 22; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 25; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 1, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l1_zmienne_pomocnicze = new char[4] {'d', 'd', 'd', 'd'};
                l1_zapadnie_czas = new double[2] {4.0, 8.0};
                l1_etapy_znikania = new char[2] {1, 1};
                l1_widzialnosc = new int[8] {0, 0, 0, 0, 0, 0, 0, 0};



                //LABIRYNT 2
                l2_elementy = new Element[15];
                l2_pola = new Pole[13];
                l2_jeze = new Jez[1];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;


                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 6; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 8; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 9; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 10; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 12; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'd';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (licznik; licznik < 15; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                    l2_elementy[licznik].y = obecny_y;
                }

                poziomik.labirynty = new Labirynt[2]{
                    Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, l1_zapadnie_czas, NULL, l1_wiatraki, NULL, l1_etapy_znikania, l1_widzialnosc, NULL),
                    Labirynt(l2_elementy, l2_pola, NULL, NULL, NULL, NULL, NULL, NULL, NULL, l2_jeze) };

                q1_zakresyID = new int[2] {1, 80};
                q2_zakresyID = new int[2] {1, 80};
                q3_zakresyID = new int[2] {1, 80};
                poziomik.quizy = new Quiz[3]{
                    Quiz(q1_zakresyID, 'b', 1, 6, 15.0, 0.0),
                    Quiz(q2_zakresyID, 's', 1, 5, 12.0, 6.0),
                    Quiz(q3_zakresyID, 'p', 1, 1, 3.0, 0.0) };

                break;//KONIEC - POZIOM 1 EPIZOD 2

            case 2://POZIOM 2 EPIZOD 2

                limit_cofniecia = 21;
                limit_czas = 600.0;
                poziomik.etapy = new char[4] {'q', 'l', 'q', '='};
                //LABIRYNT 1
                l1_elementy = new Element[31];
                l1_pola = new Pole[25];
                l1_jeze = new Jez[5];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                L_widzialnosc_N = new int[1] {17};
                L_etapy_znikania_N = new int[1] {0};
                L_zmienne_pomocnicze_N = new int[1] {4};
                L_wiatraki_N = new int[1] {0};
                L_wiatraki_przyspieszane_N = new int[1] {0};
                L_jeze_dyn_N = new int[1] {5};

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 2; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'c', 'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 8; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 9; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 10; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 0, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, 0, NOWY_ID_pole, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 12; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 1, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, 1, NOWY_ID_pole, 2};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 15; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 2, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'v', 'd', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 21; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'v', 'd', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 23; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'v', 'd', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 24; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'v', 'd', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, 3, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[5] {'q', 'v', 'd', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[5] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, 3, NOWY_ID_pole, 3};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'a';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'a';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - 5 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'b';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'b';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'b';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (licznik; licznik < 31; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l1_widzialnosc = new int[17];
                for (int i = 0; i < 7; i++) {
                    l1_widzialnosc[i] = 0;
                }
                for (int i = 7; i < 17; i++) {
                    l1_widzialnosc[i] = -1;
                }
                l1_zmienne_pomocnicze = new char[4] {'d', 'd', 'd', 'k'};
                l1_zapadnie_czas = new double[10];
                for (int i = 0; i < 10; i++) {
                    l1_zapadnie_czas[i] = 4.0 - double(i) * 0.4;
                }


                poziomik.labirynty = new Labirynt[1]{
                   Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, l1_zapadnie_czas, NULL, NULL, NULL, NULL, l1_widzialnosc, l1_jeze) };

                q1_zakresyID = new int[2] {1, 75};
                q2_zakresyID = new int[2] {1, 75};
                poziomik.quizy = new Quiz[2]{
                    Quiz(q1_zakresyID, 'b', 1, 10, 24.0, 0.0),
                    Quiz(q2_zakresyID, 'p', 1, 2, 6.0, 0.0) };

                break;//KONIEC - POZIOM 2 EPIZOD 2

            case 3://POZIOM 3 EPIZOD 2

                limit_cofniecia = 16;
                limit_czas = 900.0;
                poziomik.etapy = new char[10] {'l', 'q', 'l', 'q', 'l', 'q', 'l', 'q', 'l', '='};
                
                //LABIRYNT 1
                l1_elementy = new Element[18];
                l1_pola = new Pole[17];
                l1_wiatraki = new Wiatrak[4];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                L_widzialnosc_N = new int[5] {9, 278, 9, 0, 9};
                L_etapy_znikania_N = new int[5] {0, 0, 0, 0, 0};
                L_zmienne_pomocnicze_N = new int[5] {12, 0, 12, 2, 12};
                L_wiatraki_N = new int[5] {4, 0, 4, 9, 4};
                L_wiatraki_przyspieszane_N = new int[5] {0, 0, 0, 0, 0};
                L_jeze_dyn_N = new int[5] {0, 55, 0, 0, 0};

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', 's', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 8; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 11; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 12; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 9};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 10};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y - 5 * ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 11};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                } 
                for (licznik; licznik < 17; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }
                l1_zmienne_pomocnicze = new char[12];
                for (int i = 0; i < 12; i++) {
                    l1_zmienne_pomocnicze[i] = 'd';
                }
                l1_widzialnosc = new int[9] {-1, -1, -1, -1, -1, -1, -1, -1, -1 };
                
                tab_pom = new int[2]{ -1, -1};
                pom = rand() % 9;
                
                l1_elementy[2 + pom].ID_tab[3] = 9;
                tab_pom[0] = pom;
                while (pom == tab_pom[0]) {
                    pom = rand() % 9;
                }
                l1_elementy[2 + pom].ID_tab[3] = 10;
                tab_pom[1] = pom;
                while (pom == tab_pom[0] || pom == tab_pom[1]) {
                    pom = rand() % 9;
                }
                l1_elementy[2 + pom].ID_tab[3] = 11;

                delete[] tab_pom;
                tab_pom = NULL;

                //LABIRYNT 2

                l2_elementy = new Element[336];
                l2_pola = new Pole[280];
                l2_jeze = new Jez[55];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 113; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - 111 * ODLEGLOSC_MIEDZY_POLAMI;
                NOWY_ID_znikanie_czas = 1;
                for (licznik; licznik < 224; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 225; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 226; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas - 4;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 280; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas - 2;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (int i = 0; i < 55; i++){
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'a';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    licznik++;
                }
                for (licznik; licznik < 336; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l2_widzialnosc = new int[278];
                for (int i = 0; i < 278; i++) {
                    l2_widzialnosc[i] = -1;
                }
                l2_zapadnie_czas = new double[113];
                for (int i = 0; i < 113; i++) {
                    l2_zapadnie_czas[i] = 0.5 + double(i) * 0.18;
                }


                //LABIRYNT 3
                l3_elementy = new Element[18];
                l3_pola = new Pole[17];
                l3_wiatraki = new Wiatrak[4];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 8; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 11; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l3_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 12; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 9};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 10};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y - 5 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l3_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 11};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l3_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l3_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l3_elementy[licznik].x = obecny_x;
                    l3_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l3_elementy[licznik].typ_tab = new char[1] {'='};
                }
                l3_zmienne_pomocnicze = new char[12];
                for (int i = 0; i < 12; i++) {
                    l3_zmienne_pomocnicze[i] = 'd';
                }
                l3_widzialnosc = new int[9] {-1, -1, -1, -1, -1, -1, -1, -1, -1 };
                
                tab_pom = new int[2]{ -1, -1 };
                pom = rand() % 9;
                
                l3_elementy[2 + pom].ID_tab[3] = 9;
                tab_pom[0] = pom;
                while (pom == tab_pom[0]) {
                    pom = rand() % 9;
                }
                l3_elementy[2 + pom].ID_tab[3] = 10;
                tab_pom[1] = pom;
                while (pom == tab_pom[0] || pom == tab_pom[1]) {
                    pom = rand() % 9;
                }
                l3_elementy[2 + pom].ID_tab[3] = 11;

                delete[] tab_pom;
                tab_pom = NULL;

                //LABIRYNT 4
                l4_elementy = new Element[14];
                l4_pola = new Pole[13];
                l4_wiatraki = new Wiatrak[9];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l4_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l4_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l4_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l4_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 4 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 8; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l4_wiatraki[NOWY_ID_wiatrak].okreslnik = 'c';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 9; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l4_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y + 4 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 10; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l4_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 13; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l4_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l4_wiatraki[NOWY_ID_wiatrak].okreslnik = 'd';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l4_elementy[licznik].x = obecny_x;
                    l4_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l4_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l4_zmienne_pomocnicze = new char[2] {'b', 'b'};


                //LABIRYNT 5
                l5_elementy = new Element[18];
                l5_pola = new Pole[17];
                l5_wiatraki = new Wiatrak[4];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l5_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l5_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l5_wiatraki[NOWY_ID_wiatrak].okreslnik = 'a';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l5_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 8; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l5_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 11; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                    l5_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 12; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l5_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 9};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l5_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l5_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 14; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l5_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 10};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l5_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y - 5 * ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 15; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l5_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l5_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 11};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l5_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[3] {'p', 'm', '-'};
                    l5_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l5_elementy[licznik].x = obecny_x;
                    l5_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l5_elementy[licznik].typ_tab = new char[1] {'='};
                }
                l5_zmienne_pomocnicze = new char[12];
                for (int i = 0; i < 12; i++) {
                    l5_zmienne_pomocnicze[i] = 'd';
                }
                l5_widzialnosc = new int[9] {-1, -1, -1, -1, -1, -1, -1, -1, -1 };

                tab_pom = new int[2] { -1, -1 };
                pom = rand() % 9;

                l5_elementy[2 + pom].ID_tab[3] = 9;
                tab_pom[0] = pom;
                while (pom == tab_pom[0]) {
                    pom = rand() % 9;
                }
                l5_elementy[2 + pom].ID_tab[3] = 10;
                tab_pom[1] = pom;
                while (pom == tab_pom[0] || pom == tab_pom[1]) {
                    pom = rand() % 9;
                }
                l5_elementy[2 + pom].ID_tab[3] = 11;

                delete[] tab_pom;
                tab_pom = NULL;



                poziomik.labirynty = new Labirynt[5]{
                   Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, NULL, NULL, l1_wiatraki, NULL, NULL, l1_widzialnosc, NULL),
                   Labirynt(l2_elementy, l2_pola, NULL, l2_zapadnie_czas, NULL, NULL, NULL, NULL, l2_widzialnosc, l2_jeze),
                   Labirynt(l3_elementy, l3_pola, l3_zmienne_pomocnicze, NULL, NULL, l3_wiatraki, NULL, NULL, l3_widzialnosc, NULL),
                   Labirynt(l4_elementy, l4_pola, l4_zmienne_pomocnicze, NULL, NULL, l4_wiatraki, NULL, NULL, NULL, NULL),
                   Labirynt(l5_elementy, l5_pola, l5_zmienne_pomocnicze, NULL, NULL, l5_wiatraki, NULL, NULL, l5_widzialnosc, NULL) };

                q1_zakresyID = new int[2] {1, 75};
                q2_zakresyID = new int[2] {1, 75};
                q3_zakresyID = new int[2] {1, 75};
                q4_zakresyID = new int[2] {1, 75};
                poziomik.quizy = new Quiz[4]{
                    Quiz(q1_zakresyID, 's', 1, 7, 15.0, 7.5),
                    Quiz(q2_zakresyID, 's', 1, 7, 20.0, 10.0),
                    Quiz(q3_zakresyID, 's', 1, 7, 25.0, 12.5),
                    Quiz(q4_zakresyID, 's', 1, 7, 30.0, 15.0) };

                break;//KONIEC - POZIOM 3 EPIZOD 2

            case 4://POZIOM 4 EPIZOD 2

                limit_cofniecia = 16;
                limit_czas = 900.0;
                poziomik.etapy = new char[6] {'q', 'l', 'q', 'l', 'q', '='};

                //LABIRYNT 1
                l1_elementy = new Element[66];
                l1_pola = new Pole[65];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                L_widzialnosc_N = new int[2] {48, 8};
                L_etapy_znikania_N = new int[2] {48, 0};
                L_zmienne_pomocnicze_N = new int[2] {1, 16};
                L_wiatraki_N = new int[2] {0, 18};
                L_wiatraki_przyspieszane_N = new int[2] {0, 6};
                L_jeze_dyn_N = new int[2] {0, 2};

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 5; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 8; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 9; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 12; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 16; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 20; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 21; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 24; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 28; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 29; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 32; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 33; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 36; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 37; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 40; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 41; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 44; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 45; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - 4 * ODLEGLOSC_MIEDZY_POLAMI;

                for (licznik; licznik < 48; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 49; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 52; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[24] {'w', 'z', 'b', 'd', 'v', 'd', 'b', 'd', 'v', 'd', 'b', 'd', 'v', 'd', 'b', 'd', 'v', 'd', 'b', 'd', 'v', 'd', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[24] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, 0, NOWY_ID_znikanie_czas + 1, 0, NOWY_ID_pojawiajace_czas + 1, 0, NOWY_ID_znikanie_czas + 2, 0, NOWY_ID_pojawiajace_czas + 2, 0, NOWY_ID_znikanie_czas + 3, 0, NOWY_ID_pojawiajace_czas + 3, 0, NOWY_ID_znikanie_czas + 4, 0, NOWY_ID_pojawiajace_czas + 4, 0, NOWY_ID_znikanie_czas + 5, 0, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 53; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 54; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas - 18;
                NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas - 15;
                obecny_x = obecny_x - 5 * ODLEGLOSC_MIEDZY_POLAMI;

                for (licznik; licznik < 57; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 58; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 61; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 62; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 65; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 66; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l1_zmienne_pomocnicze = new char[1] {'b'};
                l1_zapadnie_czas = new double[270];
                for (int i = 0; i < 15; i++) {
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 6; j++) {
                            l1_zapadnie_czas[18 * i + j + 6 * k] = 0.2 + double(i) * 0.4 + double(k) * 0.1 + double(j) * 4.6;
                        }
                    }
                }
                l1_pojawiajace_czas = new double[225];
                for (int i = 0; i < 15; i++) {
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 5; j++) {
                            l1_pojawiajace_czas[15 * i + j + 5 * k] = 2.5 + double(i) * 0.4 + double(k) * 0.1 + double(j) * 4.6;
                        }
                    }
                }
                l1_etapy_znikania = new char[48];
                for(int i = 0; i < 48; i++){
                    l1_etapy_znikania[i] = 1;
                }
                l1_widzialnosc = new int[48];
                for (int i = 0; i < 48; i++) {
                    l1_widzialnosc[i] = -1;
                }

                //LABIRYNT 2
                l2_elementy = new Element[56];
                l2_pola = new Pole[53];
                l2_wiatraki = new Wiatrak[18];
                l2_jeze = new Jez[2];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 4; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'o', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas ,NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 5; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 6; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 7; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 9; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 10; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 11; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 2};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 12; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 13; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 3};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 14; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, NOWY_ID_przyspieszane_wiatraki};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'e';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }


                for (licznik; licznik < 15; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 16; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 3};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 17; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 4};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 18; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 2};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 19; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 5};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 20; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, NOWY_ID_przyspieszane_wiatraki};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'e';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }


                for (licznik; licznik < 21; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 22; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 4};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 23; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 8, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 24; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 6};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 25; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 5};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 26; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 8, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 27; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 7};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 28; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, NOWY_ID_przyspieszane_wiatraki};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'e';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }


                for (licznik; licznik < 29; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 8};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 30; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 7};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 31; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 11, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 32; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 9};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 33; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 6};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 34; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 11, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 35; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 10};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 36; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[4] {NOWY_ID_pole, NOWY_ID_wiatrak, 8, NOWY_ID_przyspieszane_wiatraki};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'k';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }


                for (licznik; licznik < 37; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 11};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 38; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 10};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 39; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 12};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 40; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 9};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 41; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 13};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 42; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[4] {NOWY_ID_pole, NOWY_ID_wiatrak, 11, NOWY_ID_przyspieszane_wiatraki};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'k';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }


                for (licznik; licznik < 43; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 44; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 12};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 45; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 14};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 46; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 13};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'i';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 47; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 15};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 48; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[4] {NOWY_ID_pole, NOWY_ID_wiatrak, 15, NOWY_ID_przyspieszane_wiatraki};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'k';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    NOWY_ID_przyspieszane_wiatraki = NOWY_ID_przyspieszane_wiatraki + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (licznik; licznik < 49; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 50; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 14, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 51; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                for (licznik; licznik < 52; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 53; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'd';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                    licznik++;
                }
                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'd';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (licznik; licznik < 56; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }

                l2_zmienne_pomocnicze = new char[16];
                for (int i = 0; i < 16; i++) {
                    l2_zmienne_pomocnicze[i] = 'd';
                }

                l2_zapadnie_czas = new double[3] {0.3, 0.4, 0.5};

                l2_etapy_wiatraki = new int[18];

                l2_widzialnosc = new int[8] {-1, -1, -1, -1, -1, -1, -1, 0};



                poziomik.labirynty = new Labirynt[2]{
                  Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, l1_zapadnie_czas, l1_pojawiajace_czas, NULL, NULL, l1_etapy_znikania, l1_widzialnosc, NULL),
                  Labirynt(l2_elementy, l2_pola, l2_zmienne_pomocnicze, l2_zapadnie_czas, NULL, l2_wiatraki, l2_etapy_wiatraki, NULL, l2_widzialnosc, l2_jeze) };

                q1_zakresyID = new int[2] {1, 75};
                q2_zakresyID = new int[2] {1, 75};
                q3_zakresyID = new int[2] {1, 75};
                poziomik.quizy = new Quiz[3]{
                    Quiz(q1_zakresyID, 'b', 1, 9, 33.0, 0.0),
                    Quiz(q2_zakresyID, 'p', 1, 9, 33.0, 0.0),
                    Quiz(q3_zakresyID, 'p', 1, 9, 33.0, 0.0)};

                break;//KONIEC - POZIOM 4 EPIZOD 2

            case 5://POZIOM 5 EPIZOD 2

                limit_cofniecia = 24;
                limit_czas = 1200.0;
                poziomik.etapy = new char[6] {'q', 'l', 'q', 'l', 'q', '='};

                //LABIRYNT 1
                l1_elementy = new Element[94];
                l1_pola = new Pole[90];
                l1_wiatraki = new Wiatrak[5];
                l1_jeze = new Jez[3];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                L_widzialnosc_N = new int[2] {61, 55};
                L_etapy_znikania_N = new int[2] {0, 55};
                L_zmienne_pomocnicze_N = new int[2] {65, 1};
                L_wiatraki_N = new int[2] {5, 2};
                L_wiatraki_przyspieszane_N = new int[2] {0, 2};
                L_jeze_dyn_N = new int[2] {3, 2};

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                for (licznik; licznik < 2; licznik++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, NOWY_ID_wiatrak};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'b';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                }
                obecny_y = obecny_y - 3 *  ODLEGLOSC_MIEDZY_POLAMI;

                for (int j = 0; j < 7; j++) {
                    for (int i = 0; i < 7; i++) {
                        l1_elementy[licznik].typ_tab = new char[4] {'q', 'x', 'y', '-'};
                        l1_elementy[licznik].ID_tab = new int[4] {NOWY_ID_widzialnosc, NOWY_ID_odbiornik, NOWY_ID_pole, NOWY_ID_odbiornik};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                        NOWY_ID_odbiornik = NOWY_ID_odbiornik + 1;
                        obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                        l1_elementy[licznik].x = obecny_x;
                        l1_elementy[licznik].y = obecny_y;
                        licznik++;
                    }
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_x = obecny_x - 7 * ODLEGLOSC_MIEDZY_POLAMI;
                }


                obecny_x = obecny_x + 4 * ODLEGLOSC_MIEDZY_POLAMI;


                {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 49};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'j';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                }
                for (int i = 0; i < 3; i++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 50, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                for (int i = 0; i < 2; i++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 51, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 63};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 52, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 53, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'd';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }


                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - 9 * ODLEGLOSC_MIEDZY_POLAMI;


                {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 54};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'j';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                }
                for (int i = 0; i < 3; i++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 55, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                for (int i = 0; i < 2; i++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 56, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l1_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 64};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 57, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y + 3 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 58, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'f';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                obecny_y = obecny_y + 6 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x + 3 * ODLEGLOSC_MIEDZY_POLAMI;

                {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 63};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'j';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;

                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 59, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (int i = 0; i < 3; i++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 60, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                for (int i = 0; i < 2; i++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (int i = 0; i < 2; i++) {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 61, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[4] {'q', 'c', 'p', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_widzialnosc, 62, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    obecny_y = obecny_y - 4 * ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y + 2 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l1_elementy[licznik].ID_tab = new int[3] {NOWY_ID_pole, NOWY_ID_wiatrak, 64};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l1_wiatraki[NOWY_ID_wiatrak].okreslnik = 'j';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_x = obecny_x - 3 * ODLEGLOSC_MIEDZY_POLAMI;
                {
                    l1_jeze[NOWY_ID_jeze].okreslnik = 'e';
                    l1_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l1_elementy[licznik].x = obecny_x;
                    l1_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l1_elementy[licznik].typ_tab = new char[1] {'='};
                }


                l1_zmienne_pomocnicze = new char[65];
                for (int i = 0; i < 65; i++) {
                    l1_zmienne_pomocnicze[i] = 'd';
                }
                l1_widzialnosc = new int[61];
                for (int i = 0; i < 49; i ++){
                    l1_widzialnosc[i] = -1;
                }
                for (int i = 49; i < 61; i++) {
                    l1_widzialnosc[i] = 0;
                }

                tab_pom = new int[13] {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
                
                pom = rand() % 49;
                l1_elementy[2 + pom].ID_tab[3] = 49;
                tab_pom[0] = pom;

                for (int i = 0; i < 13; i++) {
                    while (pom == tab_pom[0] || pom == tab_pom[1] || pom == tab_pom[2] || pom == tab_pom[3] || pom == tab_pom[4] || pom == tab_pom[5] || pom == tab_pom[6] || pom == tab_pom[7] || pom == tab_pom[8] || pom == tab_pom[9] || pom == tab_pom[10] || pom == tab_pom[11] || pom == tab_pom[12]) {
                        pom = rand() % 49;
                    }
                    l1_elementy[2 + pom].ID_tab[3] = 50 + i;
                    if(i != 12) tab_pom[i + 1] = pom;
                }

                delete[] tab_pom;
                tab_pom = NULL;

                //LABIRYNT 2
                l2_elementy = new Element[86];
                l2_pola = new Pole[83];
                l2_wiatraki = new Wiatrak[2];
                l2_jeze = new Jez[2];
                licznik = 0;
                NOWY_ID_pole = 0;
                NOWY_ID_etapy_znikania = 0;
                NOWY_ID_wiatrak = 0;
                NOWY_ID_przyspieszane_wiatraki = 0;
                NOWY_ID_widzialnosc = 0;
                NOWY_ID_znikanie_czas = 0;
                NOWY_ID_pojawiajace_czas = 0;
                NOWY_ID_odbiornik = 0;
                NOWY_ID_jeze = 0;

                obecny_x = 0.0f;
                obecny_y = 0.0f;

                for (licznik; licznik < 1; licznik++) {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '<', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                }

                for (int j = 0; j < 2; j++) {
                    for (int i = 0; i < 5; i++) {
                        l2_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                        NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                        NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                        NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                        obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }
                    {
                        l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }

                    for (int i = 0; i < 5; i++) {
                        l2_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                        NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                        NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                        NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                        obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }
                    {
                        l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }

                    for (int i = 0; i < 5; i++) {
                        l2_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                        NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                        NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                        NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                        obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }
                    {
                        l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }

                    for (int i = 0; i < 5; i++) {
                        l2_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                        NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                        NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                        NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                        obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }
                    {
                        l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                        l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                        NOWY_ID_pole = NOWY_ID_pole + 1;
                        obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                        l2_elementy[licznik].x = obecny_x;
                        l2_elementy[licznik].y = obecny_y;
                        licznik++;
                    }
                }

                for (int i = 0; i < 5; i++) {
                    l2_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                for (int i = 0; i < 5; i++) {
                    l2_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                for (int i = 0; i < 5; i++) {
                    l2_elementy[licznik].typ_tab = new char[14] {'w', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'a', 'z', 'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[14] {NOWY_ID_etapy_znikania, NOWY_ID_widzialnosc, NOWY_ID_znikanie_czas, NOWY_ID_pojawiajace_czas, NOWY_ID_znikanie_czas + 1, NOWY_ID_pojawiajace_czas + 1, NOWY_ID_znikanie_czas + 2, NOWY_ID_pojawiajace_czas + 2, NOWY_ID_znikanie_czas + 3, NOWY_ID_pojawiajace_czas + 3, NOWY_ID_znikanie_czas + 4, NOWY_ID_pojawiajace_czas + 4, NOWY_ID_znikanie_czas + 5, NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    NOWY_ID_etapy_znikania = NOWY_ID_etapy_znikania + 1;
                    NOWY_ID_widzialnosc = NOWY_ID_widzialnosc + 1;
                    NOWY_ID_znikanie_czas = NOWY_ID_znikanie_czas + 6;
                    NOWY_ID_pojawiajace_czas = NOWY_ID_pojawiajace_czas + 5;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                //JG:GLOWA WEZA

                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;

                for (int i = 0; i < 4; i++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                for (int i = 0; i < 2; i++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'y', '-'};
                    l2_elementy[licznik].ID_tab = new int[2] {NOWY_ID_pole, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                obecny_y = obecny_y - ODLEGLOSC_MIEDZY_POLAMI;
                for (int i = 0; i < 3; i++) {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[4] {NOWY_ID_pole, NOWY_ID_wiatrak, 0, 0};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'k';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'t', '-'};
                    l2_elementy[licznik].ID_tab = new int[4] {NOWY_ID_pole, NOWY_ID_wiatrak, 0, 1};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    l2_wiatraki[NOWY_ID_wiatrak].okreslnik = 'k';
                    NOWY_ID_wiatrak = NOWY_ID_wiatrak + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_y = obecny_y + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }
                {
                    l2_elementy[licznik].typ_tab = new char[3] {'p', '>', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
                    NOWY_ID_pole = NOWY_ID_pole + 1;
                    obecny_x = obecny_x + ODLEGLOSC_MIEDZY_POLAMI;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;
                obecny_y = obecny_y - 4 * ODLEGLOSC_MIEDZY_POLAMI;

                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'g';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                obecny_x = obecny_x - ODLEGLOSC_MIEDZY_POLAMI;

                {
                    l2_jeze[NOWY_ID_jeze].okreslnik = 'e';
                    l2_elementy[licznik].typ_tab = new char[2] {'i', '-'};
                    l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_jeze};
                    NOWY_ID_jeze = NOWY_ID_jeze + 1;
                    l2_elementy[licznik].x = obecny_x;
                    l2_elementy[licznik].y = obecny_y;
                    licznik++;
                }

                {
                    l2_elementy[licznik].typ_tab = new char[1] {'='};
                }


                l2_zmienne_pomocnicze = new char[1] {'b'};
                l2_zapadnie_czas = new double[330];
                for (int i = 0; i < 11; i++) {
                    for (int k = 0; k < 5; k++) {
                        for (int j = 0; j < 6; j++) {
                            l2_zapadnie_czas[18 * i + j + 6 * k] = 0.2 + double(i) * 0.4 + double(k) * 0.1 + double(j) * 4.6;
                        }
                    }
                }
                l2_pojawiajace_czas = new double[275];
                for (int i = 0; i < 11; i++) {
                    for (int k = 0; k < 5; k++) {
                        for (int j = 0; j < 5; j++) {
                            l2_pojawiajace_czas[15 * i + j + 5 * k] = 2.5 + double(i) * 0.4 + double(k) * 0.1 + double(j) * 4.6;
                        }
                    }
                }
                l2_etapy_znikania = new char[55];
                for (int i = 0; i < 55; i++) {
                    l2_etapy_znikania[i] = 1;
                }
                l2_widzialnosc = new int[55];
                for (int i = 0; i < 55; i++) {
                    l2_widzialnosc[i] = -1;
                }
                l2_etapy_wiatraki = new int[2];



                poziomik.labirynty = new Labirynt[2]{
                  Labirynt(l1_elementy, l1_pola, l1_zmienne_pomocnicze, NULL, NULL, l1_wiatraki, NULL, NULL, l1_widzialnosc, l1_jeze),
                  Labirynt(l2_elementy, l2_pola, l2_zmienne_pomocnicze, l2_zapadnie_czas, l2_pojawiajace_czas, l2_wiatraki, l2_etapy_wiatraki, l2_etapy_znikania, l2_widzialnosc, l2_jeze) };

                q1_zakresyID = new int[2] {1, 75};
                q2_zakresyID = new int[2] {1, 75};
                q3_zakresyID = new int[2] {1, 75};
                poziomik.quizy = new Quiz[3]{
                    Quiz(q1_zakresyID, 'b', 1, 3, 9.0, 0.0),
                    Quiz(q2_zakresyID, 's', 1, 6, 26.0, 9.0),
                    Quiz(q3_zakresyID, 's', 1, 9, 42.0, 21.0) };

                break;//KONIEC - POZIOM 5 EPIZOD 2

            }

            break;//KONIEC - EPIZOD 2





        case 3://EPIZOD 3

            switch (poziom) {
            default:
            case 1://POZIOM 1 EPIZOD 3



                break;//KONIEC - POZIOM 1 EPIZOD 3

            case 2://POZIOM 2 EPIZOD 3



                break;//KONIEC - POZIOM 2 EPIZOD 3

            case 3://POZIOM 3 EPIZOD 3



                break;//KONIEC - POZIOM 3 EPIZOD 3

            case 4://POZIOM 4 EPIZOD 3



                break;//KONIEC - POZIOM 4 EPIZOD 3

            case 5://POZIOM 5 EPIZOD 3



                break;//KONIEC - POZIOM 5 EPIZOD 3

            }

            break;//KONIEC - EPIZOD 3





        case 4://EPIZOD 4

            switch (poziom) {
            default:
            case 1://POZIOM 1 EPIZOD 4



                break;//KONIEC - POZIOM 1 EPIZOD 4

            case 2://POZIOM 2 EPIZOD 4



                break;//KONIEC - POZIOM 2 EPIZOD 4

            case 3://POZIOM 3 EPIZOD 4



                break;//KONIEC - POZIOM 3 EPIZOD 4

            case 4://POZIOM 4 EPIZOD 4



                break;//KONIEC - POZIOM 4 EPIZOD 4

            case 5://POZIOM 5 EPIZOD 4



                break;//KONIEC - POZIOM 5 EPIZOD 4

            }

            break;//KONIEC - EPIZOD 4





        }

    }

    void PRZELADUJ_FABULE() {//JG

        switch (poziomik.quizy[biezacy_quiz].Q_wyzwanie) {
        default:
        case 'b':
            switch (poziomik.quizy[biezacy_quiz].Q_fabula_ID) {
            default:
            case 1:
                pytanie_opis = "Bladzac w tajemniczym labiryncie w koncu udaje Ci sie odnalezc wyjscie. Czy to juz koniec wedrowki? Czy wreszcie uda Ci sie wydostac i wrocic do swojego swiata? Podchodzisz do drzwi i naciskasz klamke. Zamkniete. Dostrzegasz jednak tajemnicze, wydrazone inskrypcje na drzwiach. Moze to zagadka?\0";
                odp_opis[0] = "Udało Ci się w pełni rozpracować szyfr! Wypowiadasz magiczne słowa i drzwi otwierają się na tyle, że możesz przejść. Z wielka niecierpliwoscia przechodzisz na drugą stronę...";
                odp_opis[1] = "Wypowiadasz magiczne słowa i drzwi się otwieraja, jednak tylko przez parę sekund. Szpara jest za mała by się prześlizgnąć, więc trzeba próbować dalej.";
                odp_opis[2] = "Wypowiadasz magiczne słowa i naciskasz klamke. Drzwi się otwieraja. Ale tylko przez ułamek sekundy.Trzeba będzie spróbować ponownie.";
                odp_opis[3] = "Wypowiadasz magiczne słowa - rozwiązanie zagadki i naciskasz klamkę, ale drzwi się nie otwierają...";
                odp_opis[4] = "Dość!Kopiesz drzwi z całej siły, jednak ten argument do nich nie przemawia.Za to do komórek nerwowych twojej stopy już tak...";
                break;
            }
            break;
        case 's':
            switch (poziomik.quizy[biezacy_quiz].Q_fabula_ID) {
            default:
            case 1:
                pytanie_opis = "Niespodziewanie natrafiasz na papierowego smoka. Bestia spi, cale szczescie. Nagle dostrzegasz za nia drzwi. Moze uda Ci sie przeslizgnac?\0";
                odp_opis[0] = "Udało Ci się! Przekradles/as sie kolo smoka nie budzac go! Z wielka niecierpliwoscia przechodzisz na drugą stronę drzwi...";
                odp_opis[1] = "Stawiasz kilka kolejnych krokow, jednak smok nie budzi sie. Moze uda sie jednak przeslizgnac?";
                odp_opis[2] = "Stawiasz ostroznie nastepny krok, gdy niespodziewanie ze smoczych chrap wydobywa sie dym i glosny pisk. Nieruchomiejesz... Na szczescie mozesz odetchnac z ulga, gdyz smok jedynie parsknal przez sen.";
                odp_opis[3] = "Nim zdarzysz wykonac krok, slyszysz przerazliwy zgrzyt - to smok przesunal sie przez sen, jeszcze bardziej przyslaniajac drzwi. Szanse na przeslizgniecie sa coraz mniejsze...";
                odp_opis[4] = "Stawiasz nastepny krok. Jestes juz tuz tuz, gdy zdajesz sobie sprawe, ze wlasnie nadepnales/as bestii na ogon. Smok kwiknal z bulu i kierujac na Ciebie pelne zlosci spojrzenie zional piuropuszem papierowej miazgi...";
                break;
            }
            break;
        case 'p':
            switch (poziomik.quizy[biezacy_quiz].Q_fabula_ID) {
            default:
            case 1:
                pytanie_opis = "Stajesz, a przed Toba widoczne sa zamkniete drzwi. Widzisz po lewej i prawej dzwignie, prawdopodobnie sluzace do ich otwierania. Podloga jest jednak najerzona dziwnymi otworami. Zapewne kolce - pulapka! Juz masz odejsc, gdy dostrzegasz na sklepieniu tajemnicza mape. Moze to wskazuwka jak uniknac pulapki?\0";
                odp_opis[0] = "Nareszcie! Wraz z opuszczeniem ostatniej dzwigni drzwi otworzyly sie! Szybko mijasz ostatni dziury w podlodze i przechodzisz na druga strone...";
                odp_opis[1] = "Mimo trudnosci, udaje Ci sie ominac kolce i wcisnac kolejna dzwignie. Chociaz slyszysz satysfakcjonujacy zgrzyt mechanizmu, tyle niwystarczy. Ponuro patrzysz na kolejna dzwignie - wyglada na to, ze musisz sie do niej dostac.";
                odp_opis[2] = "Probujesz kierowac sie mapa, jednak utrzymanie rownowagi na waskim pasie bezpiecznej przestrzeni nie jest latwe. Probujac postawic kolejny krok zataczasz sie prawie na kolce, ktore wysunely sie w przerazajacym tempie. Na szczescie los Ci sprzyja - przeracasz sie idealnie na bezpieczny obszar, w dodatku blizej dzwigni!";
                odp_opis[3] = "Juz masz postawic kolejny krok, gdy ostatnie spojrzenie na mape uswiadamia Ci, ze zle idziesz! W ostatniej chwili cofasz noge i jeszcze raz, uwazniej przegladasz mape.";
                odp_opis[4] = "Juz masz postawic kolejny krok, gdy nagle slysysz przerazliwy swist... Jest to tez ostatnia rzecz jaka pamietasz budzac sie w zupelnie innym miejscu. Miejscu dziwnie znajomym...";
                break;
            }
        }

    }

};

extern PakietZmiennych* zmienne;