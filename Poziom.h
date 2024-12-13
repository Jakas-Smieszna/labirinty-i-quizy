#pragma once
#include "raylib.h"
#include "Grafika.h"
#include <iostream>

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
	ma ID do tablicy {char* widzialnosc} aktywnosci pol (czy sa czy nie sa widoczne, na jakim etapie jest animacja)
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
	ma ID do tablicy {char* widzialnosc} aktywnosci pol (czy sa czy nie sa widoczne, na jakim etapie jest animacja)
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
	
d - nie morze byc przywrocony przyciskiem lub nim usuniety dopoki nie minie czas do pojawienia sie/znikniecia
	sprawdzenia do 'x' oraz 'c' moga byc przeprowadzane dopiero gdy minie czas wskazany ID
	ma ID do tablicy {double* odblokuj_aktywacje} zawierajaca czas po ktorym mozliwe jest rozpatrywanie aktywacji przypisanych zmiennych
	(wymaga: p LUB y LUB t LUB i; wyklucza: ---)

o - magiczny ogien, dziala jak zapadnia z dodatkowa animacja i biciem przy kontakcie w czasie palenia
	gdy ustawiony bije przy znikaniu z dodatkowa animacja
	(wymaga: x lub z; wyklucza: ---)

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
	Element(char* typ_tab0, int* ID_tab0, float x0, float y0) {//jedyny konstruktor
		typ_tab = typ_tab0;
		ID_tab = ID_tab0;
		x = x0;
		y = y0;
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
	char* zmienne_pomocnicze;//przechowuje np 2 zmienne ktore trwale ustawiaj sie na TAK po jednorazowym wcisnieciu przycisku
	double* zapadnie_czas;//dane momentu czasu znikniecia niektorych pol
	double* pojawiajace_czas;//dane momentu czasu pojawienia sie niektorych pol
	double* odblokuj_aktywacje;//dane momentu czasu po ktorym aktywacja jest mozliwa
	//int* animacja;//przechowuje liczby calkowite okreslajace etap animacji elementu z animacjami
	char** odbiorniki;//wskazniki do zmiennych labiryntu dla odbirocow ich stanu
	char* etapy_znikania;//zawiera informacje ktora seria znikniec i pojawien sie pola jest aktywna (przy polu znikajacym i pojawiajacym sie wielokrotnie)
	char* widzialnosc;//zawiera etapy animcaji znikania i okresla czy pole/obiekt znikniety czy nie

};

class Poziom {
public:

	char* etapy;// np. [l,q,l,l,q] - uruchom poziom >> labirynt1 >> quiz1 >> labirynt2 >> labirynt3 >> quiz2 >> koniec misji - okresla kolejnosc etapow na poziomie
	Labirynt* labirynty;//tablica dynamiczna etapow "labirynt"

};