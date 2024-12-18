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
    float LAB_zaczep_dec_przycisku[24];//JG:obszary poboru tekstur (po 2 na przycisk, 1 dla x, 1 dla y)
    char LAB_czulosc_przycisku[9];//JG:liczniki odliczajace do 0 przed mozliwoscia ponownego klikniecia (po 1 na prycisk, nie wszystkie uzywaja)
    

    PakietZmiennych() {//inicjalizacja zmiennych po uruchmoieniu (wiele ma teraz wartosci testowe)



        limit_cofniecia = 25;
        limit_czas = 600.0;
        poziomik.etapy = new char[5] {'l', 'q', 'l', 'q', '='};
        //LABIRYNT 1
        Element* l1_elementy = new Element[18];
        int licznik = 0;
        int NOWY_ID_pole = 0;
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
            l1_elementy[licznik].typ_tab = new char[2] {'p', '-'};
            l1_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
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
            l1_elementy[licznik].typ_tab = new char[1] {'='};
        }
        Pole* l1_pola = new Pole[17];
        //LABIRYNT 2
        Element* l2_elementy = new Element[6];
        licznik = 0;
        NOWY_ID_pole = 0;
        obecny_x = 0.0f;
        obecny_y = 0.0f;
        for (licznik; licznik < 1; licznik++) {
            l2_elementy[licznik].typ_tab = new char[3] {'p', 's', '-'};
            l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
            l2_elementy[licznik].x = obecny_x;
            l2_elementy[licznik].y = obecny_y;
        }
        for (licznik; licznik < 4; licznik++) {
            l2_elementy[licznik].typ_tab = new char[2] {'p', '-'};
            l2_elementy[licznik].ID_tab = new int[1] {NOWY_ID_pole};
            NOWY_ID_pole = NOWY_ID_pole + 1;
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


        poziomik.labirynty = new Labirynt[2]{
            Labirynt(l1_elementy, l1_pola, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
            Labirynt(l2_elementy, l2_pola, NULL, NULL, NULL, NULL, NULL, NULL, NULL) };

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
        odp_wytlumaczenie = "Poniewaz dwie kupki po 5 jablek to 10 jablek a jak zjemy z tego 7 jablek to zostanie nam ich 3.\nA - niepoprawna (0pkt)\nB - niepoprawna, ale rozni sie tylko o 1 od poprawnej (1pkt)\nC - poprawna (5pkt)\nD - niepoprawna (0pkt)\0";
        //JG:inicjuje losowe bazy grafik przyciskow po rozpoczeciu gry oraz zeruje ich czulosc
        for (int i = 0; i <24; i++) {
            LAB_zaczep_dec_przycisku[i] = (float)(rand() % 51) * 0.01f * 1000.0f;
        }
        for (int i = 0; i < 9; i++) {
            LAB_czulosc_przycisku[i] = 0;
        }
    }

    void D_Zmienne(){
        
        if (pytanie != NULL) delete pytanie;

    }

};

extern PakietZmiennych* zmienne;