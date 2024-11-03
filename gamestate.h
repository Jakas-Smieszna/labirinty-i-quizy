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
    GRA_LABIRYNT = 7,//JG:labirynt
    GRA_QUIZ = 8,//JG:quiz
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
    char* pytanie_opis;//JG:caly tekst opisu fabularnego pytania
    char* pytanie;//JG:caly tekst pytania z odpowiedziami; dzielony na 5 segmentow - w tym 4 z odpowiedziami i 1 z pytaniem; segmenty oddzielone znakie '\n'; na koncu znak '\0'
    char* odp_wytlumaczenie;//JG:caly tekst wytlumaczenia wraz z opisem fabularnym odzielone na 2 segmenty, analogicznie jak pytanie; najpierw opis, potem tlumaczenie; 
    char odp_pop;
    
    //JG:TABLICE POD PRZYCISKI TRYBU GRY
    float LAB_zaczep_dec_przycisku[24];//JG:obszary poboru tekstur (po 2 na przycisk, 1 dla x, 1 dla y)
    char LAB_czulosc_przycisku[9];//JG:liczniki odliczajace do 0 przed mozliwoscia ponownego klikniecia (po 1 na prycisk, nie wszystkie uzywaja)
    

    PakietZmiennych() {//inicjalizacja zmiennych po uruchmoieniu (wiele ma teraz wartosci testowe)
        uzytkownik = "Rimek Wesolek";
        koniec = false;
        mysz_x = GetMouseX();
        mysz_y = GetMouseY();
        mysz_pop_x = GetMouseX();
        mysz_pop_y = GetMouseY();
        kurosr_czulosc = 0;
        srand(time(NULL));
        epizod_doc = (char)(rand()%4 + 1);//losuje epizod pod tlo po uruchomieniu
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
        limit_cofniecia = 20;
        trudnosc_labirynt = '0';
        trudnosc_pytania = '6';
        glosnosc = 50.0f;

        wyzwanie = 'b';
       
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