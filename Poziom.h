#pragma once
#include "raylib.h"
#include "Grafika.h"
#include <iostream>

#define ODLEGLOSC_MIEDZY_POLAMI 100.0f
#define PREDKOSC_OBROTU 0.54f

/*WIELKA KSIEGA CHAROW:

ROZDZIAL I - typ (do typ_tab):

= - ten element znakuje koniec tablicy i nie peleni zadnej innej roli
	(wyklucza: wszystkie inne)

- - oznacza koniec listy podtypow w danym elemencie

p - pole: 
	ma ID do pola do tablicy {Pole* pola} z danymi wycinka tekstury z grafiki pol/przyciskow
	otrzymuje funkcje rysowania pola, 
	chroni kursor przed upadkiem 
	(wyklucza: t, y, i, u)

m - meta:
	dodaje funkcje sprawdzajaca czy kliknieto na polu, wowczas konczy poziom, 
	uzupelnia grafike pola o napis "META" 
	(wymaga: p; wyklucza: s, >, <)

s - start: 
	uzupelnia grafike pola o napis "START" 
	(wymaga: p; wyklucza: m, >, <)

> - przejscie-wejscie: 
	uzupelnia grafike pola o napis "DRZWI", 
	dodaje funkcje sprawdzajaca czy kliknieto na polu - jak tak to zapisuje wspolrzedne punktu kontrolnego i przestawia etap na kolejny 
	(wymaga: p; wyklucza: s, m, <)

< - przejscie-wyjscie:
	uzupelnia grafike pola o napis "WEJSCIE"
	(wymaga: p; wyklucza: s, m, >)

q - zmienne widocznoscia raz lub 1 seria:
	okresla, ze pole moze byc aktywne lub nie
	wymagane raz do dzialania magicznych ogni i systemu pojawiania sie/znikania
	ma ID do tablicy {int* widzialnosc} aktywnosci pol (czy sa czy nie sa widoczne, na jakim etapie jest animacja)
	(wymaga: p LUB i LUB t LUB y; wyklucza: w)

z - zapadnia:
	kazda dodana to 1 moment czasu gdy pole znika,
	ma ID do tabelicy {double* zapadnie_czas} czasow zawierajacej moment czasu, w ktorym pole znika
	uzupelnia o funkcje znikniecia gdy czas minie
	(wymaga: p LUB i LUB t LUB y, q LUB w; wyklucza: PRZYNAJMNIEJ_1 m)

a - pojawiajace sie:
	kazde dodane to 1 moment czasu gdy pole pojawia sie,
	ma ID do tabelicy {double* pojawiajace_czas} czasow zawierajacej moment czasu, w ktorym pole pojawia sie
	uzupelnia o funkcje pojawienia gdy czas minie
	(wymaga: p LUB i LUB y LUB t, q LUB w; wyklucza: s, <)

NOTATKA: niewidoczne pola nie podtrzymuja gracza i nie sa rysowane. Wartosci inne niz maks i min moga sluzyc do rysowania kolejnych etapow animacji

w - zmienne widoczne i znikajace wielokrotnie:
	okresla, ze pole moze byc aktywne lub nie
	wymagane raz do dzialania systemu pojawiania sie/znikania
	ma ID do tablicy {char* etapy_znikania} zawierajacej liczbe okreslajaca ktora serie znikniec i pojawien aktualnie wykorzystuje
	ma ID do tablicy {int* widzialnosc} aktywnosci pol (czy sa czy nie sa widoczne, na jakim etapie jest animacja)
	(wymaga: p LUB i LUB t LUB y; wyklucza: q)

x - zapadnia aktywowana przyciskiem
	pole znika gdy wskazywana zmienna labiryntu (char) jest aktywna po raz pierwszy
	jeden char do jednej zmiennej odwolania
	efekt sprawdzania odnawia sie, jesli pole pojawi sie na skutek innego efektu skladowego
	ma ID do tablicy {char** odbiorcy} wskazujacej lokalizacje zmiennej, od ktorej aktywacja zapadni jest uzalezniona
	uzupelnia o funkcje zapadniecia, gdy aktywowano
	(wymaga: p LUB i LUB y LUB t, q LUB w; wyklucza PRZYNAJMNIEJ_1 m) 

c - pojawiajacy aktywowany przyciskiem
	pole pojawia sie gdy aktywowana jest przypisana zmienna labiryntu (char; aktywowana po raz pierwszy)
	jeden char do jednej zmiennej odwolania
	efekt sprwadzania odnawia sie po zapdnieciu pola na skutek innego efektu skladowego
	ma ID do tablicy {char** odbiorcy} wskazujacej lokalizacje zmiennej, od ktorej aktywacji pojawienia sie jest uzalezniona
	uzupelnia o funkcje pojawienia sie, gdy aktywowano
	(wymaga: p LUB i LUB y LUB t, q LUB w; wyklucza s, <)
	
d - pelni wazna funkcje nawigacyjna wystepujac po typach v i b, pozwala zachowac jednolitosc przesuniec charakterow i identyfikatorow bez wzgledu na rodzaje charakterow
	sprawdzenia do 'x' oraz 'c' moga byc przeprowadzane dopiero gdy minie czas wskazany ID
	(wymaga: p LUB y LUB t LUB i; wyklucza: ---)

v - zapadnia aktywowana przyciskiem ale od okreslonego czasu (dziala jak 'z' i 'x' ale ma wymagania obu w warunku i zajumuje 2 identyfikatry (do czasu i zmiennej)).

b - analogicznie jak 'v' ale dla pojawiania sie (nie znikania).

o - magiczny ogien, dziala jak zapadnia z dodatkowa animacja i biciem przy kontakcie w czasie palenia
	gdy ustawiony bije przy znikaniu z dodatkowa animacja, dziala i fuunkcjonuje jak 'z' z dodatkowa informacja o powyzszym
	(wymaga: p LUB i LUB t LUB y, q LUB w; wyklucza: PRZYNAJMNIEJ_1 m)

t - wiatrak, obraca sie klujac przy kontakcie
	ma ID do wiatraka do tablicy {Wiatrak* wiatraki} z danymi wycinka tekstury z grafiki wiatrakow oraz biezaca rotacja
	otrzymuje funkcje rysowania wiatraka, uwzgledniajaca rotacje,
	otrzymuje funkcje sprawdzania kolizji z kursorem oraz rotowania sie
	kluje (bije) kursor przy kontakcie
	(wyklucza: p, y, i)
	
y - przycisk, po kliknieciu zmienia dane zmiennych labiryntu
	ma ID do przycisku do tablicy {Aktywator* aktywatory} z danymi wycinka tekstury z grafiki przyciskow oraz typ ustawiania zmiennej (char) oraz liste zmiennych do zmiany w zmiennych labiryntowych (char**)
	otrzymuje funkcje rysowania przycisku, uwzgledniajaca efekt wciskania, 
	chroni kursor przed upadkiem 
	(wyklucza: t, p, i)

i - kolczatka, krazy wokol pozycji lub przemierza inna trase bijac przy kontakcie
	ma ID do kolczatki do tablicy {Kolczatka* kolczatki} z danymi odwolania do tekstury grafiki oraz biezaca rotacja i trase ruchu/typ (char), oraz etapu przemieszczania (int)
	otrzymuje funkcje rysowania kolczatki, uwzgledniajaca rotacje i inne efekty
	otrzymuje funkcje sprawdzania kolizji z kursorem oraz przemieszczania sie
	kluje (bije) kursor przy kontakcie
	(wyklucza: p, y, t)

u - portal, element wizualny, z ktorego wychodza kolczatki, bije przy kontakcie
	ma ID do portalu do tablicy {Portal* portale} z danymi wycinka tekstury z grafiki portali
	otrzymuje funkcje rysowania portalu, uwzgledniajac animacje tworzenia
	kluje (bije) kursor przy kontakcie
	(wyklucza: t, p, i)

*/


class Element {
public:

	char* typ_tab;//charaktery
	int* ID_tab;//ID w tablicach charakterow
	float x;//pozycja x
	float y;//pozycja y

	Element(char* typ_tab0, int* ID_tab0, float x0, float y0) {//jedyny konstruktor praktyczny
		typ_tab = typ_tab0;
		ID_tab = ID_tab0;
		x = x0;
		y = y0;
	}

	Element() {//konstruktor pod puste
		typ_tab = NULL;
		ID_tab = NULL;
		x = 0;
		y = 0;
	}

	void D_Element() {//zwalnianie pamieci
		if (typ_tab != NULL) delete[] typ_tab;
		if (ID_tab != NULL) delete[] ID_tab;
	}

};

class Wiatrak {//charakter - pole CHAR = 't'
public:

	float x_zrodla;//x zrodlowe cwiartki grafiki
	float y_zrodla;//y zrodlowe cwiartki grafiki
	float rotacja;//odchylenie od domyslnego kierunku w stopniach
	double tempo;//tempo obrotu obracaka (mnoznik)
	char okreslnik;/*uniwersalna zmienna znakowa zawierajaca wszystkie dodatkowe informacje.
	Znaczenia:
	a - obrot w prawo
	b - obrot w lewo
	c - obrot w prawo gdy zmienna aktywna i lewo gdy nieaktywna (ID do zmiennych poziomu)
	d - obrot w lewo gdy zmienna aktywna i prawo gdy nieaktywna (ID do zmiennych poziomu)
	e - obrot w prawo, przyspieszenie (razy 3.33) co losowo od 5 do 10 sekund na losowo od 1 do 3 sekund (ID do etapow wiatraka)
	f - obrot w lewo, przyspieszenie (razy 3.33) co losowo od 5 do 10 sekund na losowo od 1 do 3 sekund (ID do etapow wiatraka)
	g - obrot w prawo gdy zmienna aktywna i lewo gdy nieaktywna (ID do zmiennych poziomu) + przyspieszenie (razy 3.33) co losowo od 5 do 10 sekund na losowo od 1 do 3 sekund (ID do etapow wiatraka)
	h - obrot w lewo gdy zmienna aktywna i prawo gdy nieaktywna (ID do zmiennych poziomu) + przyspieszenie (razy 3.33) co losowo od 5 do 10 sekund na losowo od 1 do 3 sekund (ID do etapow wiatraka)
	i - obrot w prawo gdy zmienna aktywna i brak obrotu gdy nieaktywna (ID do zmiennych poziomu)
	j - obrot w lewo gdy zmienna aktywna i brak obrotu gdy nieaktywna (ID do zmiennych poziomu)
	k - obrot w prawo gdy zmienna aktywna i brak obrotu gdy nieaktywna (ID do zmiennych poziomu) + przyspieszenie (razy 3.33) co losowo od 5 do 10 sekund na losowo od 1 do 3 sekund (ID do etapow wiatraka)
	l - obrot w lewo gdy zmienna aktywna i brak obrotu gdy nieaktywna (ID do zmiennych poziomu) + przyspieszenie (razy 3.33) co losowo od 5 do 10 sekund na losowo od 1 do 3 sekund (ID do etapow wiatraka)

	*/

	Wiatrak() {//jedyny konstruktor
		x_zrodla = (float)(rand() % 51) * 0.01f * 1000.0f;//analogicznie do grafik przycisków
		y_zrodla = (float)(rand() % 51) * 0.01f * 1000.0f;
		rotacja = 0.0;
		tempo = 1.0;
		okreslnik = 'a';
	}


};

class Pole {//charakter - pole CHAR = 'p'
public:

	float x_zrodla;//x zrodlowe cwiartki grafiki
	float y_zrodla;//y zrodlowe cwiartki grafiki
	Pole() {//jedyny konstruktor
		x_zrodla = (float)(rand() % 51) * 0.01f * 1000.0f;//analogicznie do grafik przycisków
		y_zrodla = (float)(rand() % 51) * 0.01f * 1000.0f;
	}

};

class Labirynt {
public:

	Element* elementy;//wszystkie pola i przeciwnicy
	Pole* pola;//wszystkie dane zrodlowe wycinku grafiki pol
	Wiatrak* wiatraki;//wszystkie dane zrodlowe wycinku grafiki wiatrakow oraz o ich rotacji
	char* zmienne_pomocnicze;//przechowuje np 2 zmienne ktore trwale ustawiaj sie na TAK po jednorazowym wcisnieciu przycisku
	double* zapadnie_czas;//dane momentu czasu znikniecia niektorych pol
	double* pojawiajace_czas;//dane momentu czasu pojawienia sie niektorych pol
	double* odblokuj_aktywacje;//dane momentu czasu po ktorym aktywacja jest mozliwa //JG: OBECNIE W DRODZE DO KASACJI - PRAWDOPODOBNIE NIEUZYWANE
	//int* animacja;//przechowuje liczby calkowite okreslajace etap animacji elementu z animacjami
	int* etapy_wiatraki;//odliczanie przerw i czasow wiarakow o zmiennej predkosci //JG: OBECNIE W DRODZE DO KASACJI - PRAWDOPODOBNIE NIEUZYWANE
	char* etapy_znikania;//zawiera informacje ktora seria znikniec i pojawien sie pola jest aktywna (przy polu znikajacym i pojawiajacym sie wielokrotnie)
	int* widzialnosc;//zawiera etapy animcaji znikania i okresla czy pole/obiekt znikniety czy nie

	Labirynt() {//konstruktor pusty
		elementy = NULL;
		pola = NULL;
		wiatraki = NULL;
		zmienne_pomocnicze = NULL;
		zapadnie_czas = NULL;
		pojawiajace_czas = NULL;
		odblokuj_aktywacje = NULL;
		etapy_wiatraki = NULL;
		etapy_znikania = NULL;
		widzialnosc = NULL;
	}

	Labirynt(Element* elementy0, Pole* pola0, char* zmienne_pomocnicze0, double* zapadnie_czas0, double* pojawiajace_czas0, Wiatrak* wiatraki0, int* etapy_wiatraki0, char* etapy_znikania0, int* widzialnosc0) {//konstruktor glowny
		elementy = elementy0;
		pola = pola0;
		wiatraki = wiatraki0;
		zmienne_pomocnicze = zmienne_pomocnicze0;
		zapadnie_czas = zapadnie_czas0;
		pojawiajace_czas = pojawiajace_czas0;
		odblokuj_aktywacje = NULL;
		etapy_wiatraki = etapy_wiatraki0;
		etapy_znikania = etapy_znikania0;
		widzialnosc = widzialnosc0;

	}

	void D_Labirynt() {//zwalnianie pamieci
		if (elementy != NULL) {
			int licznik = 0;
			while (elementy[licznik].typ_tab[0] != '=') {
				elementy[licznik].D_Element();
				licznik = licznik + 1;
			}
			elementy[licznik].D_Element();
			delete[] elementy;
		}
		if (pola != NULL) delete[] pola;
		if (wiatraki != NULL) delete[] wiatraki;
		if (zmienne_pomocnicze != NULL) delete[] zmienne_pomocnicze;
		if (zapadnie_czas != NULL) delete[] zapadnie_czas;
		if (pojawiajace_czas != NULL) delete[] pojawiajace_czas;
		if (odblokuj_aktywacje != NULL) delete[] odblokuj_aktywacje;
		if (etapy_wiatraki != NULL) delete[] etapy_wiatraki;
		if (etapy_znikania != NULL) delete[] etapy_znikania;
		if (widzialnosc != NULL) delete[] widzialnosc;
	}

};

class Quiz {
public:

	int* Q_zakres_pytan;//zawsze zawiera parzysta ilosc numerow indeksow pytan  (parami - pierwszy z pary to min, drugi to max tak wiec {5, 7, 9, 9, 12, 60} to suma zbiorow pytan od 5 do 7, jednoelementowego 9 oraz od 12 do 60 (wszystko wlacznie)
	char Q_wyzwanie;//jakie wyzwanie (do wyzwania w gamestate)
	int Q_fabula_ID;//ktory zestaw tekstow fabularnych z bazy
	int Q_proby;//ile przysluguje prob w quizie
	double Q_prog_punktowy;//ile punktow wymaganych do zaliczenia
	double Q_prog_bezpieczenstwa;//ile punktow wymaganych do unikniecia zbicia przez straznika

	//Quiz() {//konstruktor testowy
	//	Q_zakres_pytan = new int[2];
	//	Q_zakres_pytan[0] = 1;
	//	Q_zakres_pytan[0] = 100;
	//	Q_fabula_ID = rand() % 4;
	//	Q_wyzwanie = 'b';
	//	Q_proby = 5;
	//	Q_prog_punktowy = 10.0;
	//	Q_prog_bezpieczenstwa = 5.0;
	//}

	Quiz() {//konstruktor pusty
		Q_zakres_pytan = NULL;
		Q_fabula_ID = rand() % 4;
		Q_wyzwanie = 'b';
		Q_proby = 5;
		Q_prog_punktowy = 10.0;
		Q_prog_bezpieczenstwa = 5.0;
	}

	Quiz(int* zakresy, char wyzwanie, int fabula, int proby, double punkty, double straznik) {//konstruktor praktyczy
		Q_zakres_pytan = zakresy;
		Q_wyzwanie = wyzwanie;
		Q_fabula_ID = fabula;
		Q_proby = proby;
		Q_prog_punktowy = punkty;
		Q_prog_bezpieczenstwa = straznik;
	}

	void D_Quiz() {//do zwalniania pamieci
		if(Q_zakres_pytan != NULL) delete[] Q_zakres_pytan;
	}

};

class Poziom {
public:

	char* etapy;// np. [l,q,l,l,q,=] - uruchom poziom >> labirynt1 >> quiz1 >> labirynt2 >> labirynt3 >> quiz2 >> koniec misji - okresla kolejnosc etapow na poziomie. '=' oznacza koniec tablicy
	Labirynt* labirynty;//tablica dynamiczna etapow "labirynt"
	Quiz* quizy;//tablica dynamiczna etapow "Quiz"


	Poziom() {//konstruktor pusty
		etapy = NULL;
		labirynty = NULL;
		quizy = NULL;
	}

	void D_Poziom(){//zwalnianie pamieci
		if (etapy != NULL) {
			int Q_licznik = 0;
			int L_licznik = 0;
			int licznik = 0;
			while (etapy[licznik] != '=') {
				if (etapy[licznik] == 'q' && quizy != NULL) {
					quizy[Q_licznik].D_Quiz();
					Q_licznik = Q_licznik + 1;
				}
				else if (etapy[licznik] == 'l' && labirynty != NULL) {
					labirynty[L_licznik].D_Labirynt();
					L_licznik = L_licznik + 1;
				}
				licznik = licznik + 1;
			}
			delete[] etapy;
		}
		if (labirynty != NULL) delete[] labirynty;
		if (quizy != NULL) delete[] quizy;
	}
};