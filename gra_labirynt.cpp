﻿#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "Grafika.h"
#include "gamestate.h"
#include "przycisk.h"
#include <string>
#include "Poziom.h"

namespace labirynt {
	

	// Rysowanie
	void drawLabirynt() {
		if (zmienne->kurosr_czulosc == 0) SetMouseCursor(1);
		else if (zmienne->kurosr_czulosc > 0) zmienne->kurosr_czulosc = zmienne->kurosr_czulosc - 1;
		else zmienne->kurosr_czulosc = 0;
		ClearBackground(BLACK);
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		float Skala_liter = 1.0;
		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = wys / OknoWysBaz;
		}
		else {//JG:INNE PROPORCJE OKNA
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = szer / OknoSzerBaz;
		}

		Color szata_epizodu = BLACK;
		Color napis_epizodu = BLACK;
		switch (zmienne->epizod) {
		default:
		case 1://JG:EP 1
			szata_epizodu = BROWN;
			napis_epizodu = YELLOW;
			break;
		case 2://JG:EP 2
			szata_epizodu = DARKGREEN;
			napis_epizodu = ColorBrightness(SKYBLUE, 0.15f);
			break;
		case 3://JG:EP 3
			szata_epizodu = DARKGRAY;
			napis_epizodu = RED;
			break;
		case 4://JG:EP 4
			szata_epizodu = BLACK;
			napis_epizodu = WHITE;
			break;
		}



		//LABIRYNT - ELEMENTY:

		double tempo = 1.0;
		/*JG:TRUDNOSCI:
			a)labirynty:
				'0' - poczatkujacy
				'l' - latwy
				'n' - normalny
				't' - trudny
				'm' - mistrzowski*/
		switch (zmienne->trudnosc_labirynt) {
		case '0':
			tempo = 1.3;
			break;
		case 'l':
			tempo = 1.15;
			break;
		default:
		case 'n':
			tempo = 1.0;
			break;
		case 't':
			tempo = 0.95;
			break;
		case 'm':
			tempo = 0.9;
			break;
		}

		float X_GRANICA = szer - 272.0f * Skala_liter;//JG:Prawa optycznie granica planszy
		float Y_GRANICA = 40.0f * Skala_liter;//JG:Gorna optycznie granica planszy
		float duch = 1.0f;//JG:Glownie do epizodu 4 - labiryntt cieni. Okresla przezrozczystosc elementu.

		bool Gracza_na_planszy = false;//JG:przechodzac po elementach od razu sprawdza czy gracz znajduje sie na planszy (jak nie to spada)
		bool Gracza_skluty = false;//JG:przechodzac po elementach od razu sprawdza czy gracz dotyka wiatraka lub kolczatki lub innego klujacego elementu (jak tak to zbity)
		int Widzialnosc = -1;//JG:ustawienie na wartosc ID do widzialnosci prze odpowiedni podtyp gwrantuje rozpatrzenie w kolejnych podtypach
		char Typ_animacji = '0';/*JG:okresla np czy ma znikac czy sie pojawiac :
			'0' - brak;
			'z' - zapadanie sie;
			'o' - spalanie;
			'a' - pojawianie sie;
		*/
		char Wskazik_do_etapu_znikania_pojawiania = 0;//JG:uzywane przy wielokrotnie zmiennych widocznoscia, by okreslic, na jakim etapie znikania/pojawiania sie (za ile typow bedzie bierzacy typ znikanie/pojawianie); w trybie jednorazowego znikania/pojawiania wynosi 1.

		int obecny_labirynt = zmienne->biezacy_labirynt;//JG:Po kliknieciu drzwi biezacy labirynt ulega zmianie. Aby uniknac awarii przy probie dokonczenia funkcji labiryntu w takich warunkach, operuje na kopii.
		int element = 0;//JG: int do przechodzenia po kolei wszytskich elementow w labiryncie
		while (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[0] != '=') {//JG:przechodzi wszystkie elementy do elementu koncowego o pierwszym typie '='
			
			int charakter = 0;//JG: int do przechodzenia po tablicy charakterow
			int identyfikator = 0;//JG: int do przechodzenia po tablicy ID-kow
			float x = zmienne->plansza_x * Skala_liter + X_GRANICA * 0.5f + Skala_liter * (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].x);//JG:liczenie wzglednej pozycji x elementu na mapie
			float y = zmienne->plansza_y * Skala_liter + (wys - Y_GRANICA) * 0.5f + Skala_liter * (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].y);//JG:liczenie wzglednej pozycji y elementu na mapie
			duch = 1.0;//JG:efekt przezroczystosci
			Widzialnosc = -1;//JG:widzialnosc/animacja
			Typ_animacji = '0';//JG:informuje dalsze instrukcje czy zmniejszac czy zwiekszac etap animcaji (znikanie i pojawianie maja odwrotne kierunki) oraz o charakterze (palenie ma odmienny od reszty)
			Wskazik_do_etapu_znikania_pojawiania = 0;
			//std::cout << "\n";
			while (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] != '-') {//JG:przechodzi domyslnie wszystkie podtypy elementu az do podtypu koncowego '-'
				int pom = 0;//JG:pomocniczy int uzywany na wiele sposobow
				//std::cout << zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter];
				//std::cout << identyfikator;
				switch (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter]) {//JG:wybiera instrukcje od charakteru podtypu

					//JG:POLE
				case 'p':
					if (zmienne->epizod == 4) duch = 0.5f;
					if (x < szer + 50.0f * Skala_liter - TOL && x > -50.0f * Skala_liter + TOL && y < wys + 50.0f * Skala_liter + TOL && y > -50.0f * Skala_liter - TOL) {//JG:Jesli na obszarze okna rysuj
						
						if (Widzialnosc == -1) {//JG:Widoczne i aktywne
							DrawRectangle(x - 50.0f * Skala_liter, y - 50.0f * Skala_liter, 100.0f * Skala_liter, 100.0f * Skala_liter, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
							DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { x, y, 96.0f * Skala_liter, 96.0f * Skala_liter }, { 48.0f * Skala_liter, 48.0f * Skala_liter }, 0.0f, Fade(ColorBrightness(WHITE, 0.0f), duch));
							if (!Gracza_na_planszy && abs(X_GRANICA * 0.5f - x) < 62.5f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 62.5f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
								Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
							}
							break;
						
						}
						else if (Widzialnosc > 0) {//JG:W animacji if(TAK) lub niewidoczny (nieaktywny) if(NIE)

							float mnoznik = 0.0f;
							Color barwnik = WHITE;
							Color barwnik2 = WHITE;

							if (Typ_animacji == 'o') {//JG:palenie - przezroczystosc i barwnik
								duch = duch * (float)((double)Widzialnosc / 100.0);
								switch (zmienne->epizod) {
								default:
								case 1:
								case 2:
									barwnik = ORANGE;
									barwnik2 = YELLOW;
									break;
								case 3:
								case 4:
									barwnik = BLUE;
									barwnik2 = SKYBLUE;
									break;
								}
							}

							switch ((Widzialnosc / 100)) {//JG:wybor wariantu animacji
							
							default:
							case 0://JG:Typ animacji 1 (od/dosrodkowe 4 kwadraty)
								mnoznik = (float)((double)Widzialnosc * 0.01);
								
								//JG:rysowanie obrysow
								DrawRectangle(x - 50.0f * Skala_liter, y - 50.0f * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
								DrawRectangle(x + (50.0f - 50.0f * mnoznik) * Skala_liter, y - 50.0f * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
								DrawRectangle(x - 50.0f * Skala_liter, y + (50.0f - 50.0f * mnoznik) * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
								DrawRectangle(x + (50.0f - 50.0f * mnoznik) * Skala_liter, y + (50.0f - 50.0f * mnoznik) * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { 49.0f * Skala_liter, 49.0f * Skala_liter }, 0.0f, Fade(ColorBrightness(barwnik, 0.0f), duch));
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla + grafiki->pole1.szer * 0.25f * (2.0f -mnoznik), zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { -49.0f * Skala_liter * (1.0f - mnoznik), 49.0f * Skala_liter}, 0.0f, Fade(ColorBrightness(barwnik, 0.0f), duch));
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla + grafiki->pole1.wys * 0.25f * (2.0f - mnoznik), grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { 49.0f * Skala_liter, -49.0f * Skala_liter * (1.0f - mnoznik) }, 0.0f, Fade(ColorBrightness(barwnik, 0.0f), duch));
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla + grafiki->pole1.szer * 0.25f * (2.0f - mnoznik), zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla + grafiki->pole1.wys * 0.25f * (2.0f - mnoznik), grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { -49.0f * Skala_liter * (1.0f - mnoznik), -49.0f * Skala_liter * (1.0f - mnoznik) }, 0.0f, Fade(ColorBrightness(barwnik, 0.0f), duch));

								if (abs(X_GRANICA * 0.5f - (x - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (Typ_animacji == 'z' || Typ_animacji == 'a') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								if (abs(X_GRANICA * 0.5f - (x + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (Typ_animacji == 'z' || Typ_animacji == 'a') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								if (abs(X_GRANICA * 0.5f - (x - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (Typ_animacji == 'z' || Typ_animacji == 'a') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								if (abs(X_GRANICA * 0.5f - (x + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (Typ_animacji == 'z' || Typ_animacji == 'a') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}

								break;

							case 1://JG:Typ animacji 2 (spadanie)
								mnoznik = (float)((double)(Widzialnosc - 100) * 0.01);

								//JG:rysowanie obrysow
								DrawRectanglePro({ x, y, 100.0f * Skala_liter * mnoznik, 100.0f * Skala_liter * mnoznik }, { 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik}, 360.0 * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
								
								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { x, y, 96.0f * Skala_liter * mnoznik, 96.0f * Skala_liter * mnoznik }, { 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, 360.0 * mnoznik, Fade(ColorBrightness(barwnik, 0.0f), duch));
								
								
								if (abs(X_GRANICA * 0.5f - x) < 62.5f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 62.5f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (mnoznik > 0.75 && (Typ_animacji == 'z' || Typ_animacji == 'a')) Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								break;

							case 2://JG:Typ animacji 3 (wsuwany od/do srodka gora-dol)
								mnoznik = (float)((double)(Widzialnosc - 200) * 0.01);

								//JG:rysowanie obrysow
								DrawRectanglePro({ x, y, 100.0f * Skala_liter, 100.0f * Skala_liter * mnoznik }, { 50.0f * Skala_liter, 50.0f * Skala_liter * mnoznik }, 0.0, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f * mnoznik }, { x, y, 96.0f * Skala_liter, 96.0f * Skala_liter * mnoznik }, { 48.0f * Skala_liter, 48.0f * Skala_liter * mnoznik }, 0.0, Fade(ColorBrightness(barwnik, 0.0f), duch));


								if (abs(X_GRANICA * 0.5f - x) < 62.5f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 62.5f * Skala_liter * mnoznik + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if ((Typ_animacji == 'z' || Typ_animacji == 'a')) Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								break;

							case 3://JG:Typ animacji 4 (wsuwany od/do srodka lewo-prawo)
								mnoznik = (float)((double)(Widzialnosc - 300) * 0.01);

								//JG:rysowanie obrysow
								DrawRectanglePro({ x, y, 100.0f * Skala_liter * mnoznik, 100.0f * Skala_liter }, { 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter }, 0.0, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f * mnoznik, grafiki->pole1.wys * 0.5f }, { x, y, 96.0f * Skala_liter * mnoznik, 96.0f * Skala_liter }, { 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter }, 0.0, Fade(ColorBrightness(barwnik, 0.0f), duch));


								if (abs(X_GRANICA * 0.5f - x) < 62.5f * Skala_liter * mnoznik + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 62.5f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if ((Typ_animacji == 'z' || Typ_animacji == 'a')) Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								break;

							case 4://JG:Typ animacji 5 (wsuwany do gory)
								mnoznik = (float)((double)(Widzialnosc - 400) * 0.01);

								//JG:rysowanie obrysow
								DrawRectanglePro({ x, y, 100.0f * Skala_liter, 100.0f * Skala_liter * mnoznik }, { 50.0f * Skala_liter, 50.0f * Skala_liter }, 0.0, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f * mnoznik }, { x, y, 96.0f * Skala_liter, 96.0f * Skala_liter * mnoznik }, { 48.0f * Skala_liter, 48.0f * Skala_liter }, 0.0, Fade(ColorBrightness(barwnik, 0.0f), duch));


								if (abs(X_GRANICA * 0.5f - x) < 62.5f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y - 50.0f * Skala_liter * (1.0f - mnoznik))) < 62.5f * Skala_liter * mnoznik + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if ((Typ_animacji == 'z' || Typ_animacji == 'a')) Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								break;

							case 5://JG:Typ animacji 6 (wsuwany w lewo)
								mnoznik = (float)((double)(Widzialnosc - 500) * 0.01);

								//JG:rysowanie obrysow
								DrawRectanglePro({ x, y, 100.0f * Skala_liter * mnoznik, 100.0f * Skala_liter }, { 50.0f * Skala_liter, 50.0f * Skala_liter }, 0.0, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f * mnoznik, grafiki->pole1.wys * 0.5f }, { x, y, 96.0f * Skala_liter * mnoznik, 96.0f * Skala_liter }, { 48.0f * Skala_liter, 48.0f * Skala_liter }, 0.0, Fade(ColorBrightness(barwnik, 0.0f), duch));


								if (abs(X_GRANICA * 0.5f - (x - 50.0f * Skala_liter * (1.0f - mnoznik))) < 62.5f * Skala_liter * mnoznik + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 62.5f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if ((Typ_animacji == 'z' || Typ_animacji == 'a')) Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								break;

							case 6://JG:Typ animacji 7 (wsuwany do dolu)
								mnoznik = (float)((double)(Widzialnosc - 600) * 0.01);

								//JG:rysowanie obrysow
								DrawRectanglePro({ x, y + 100.0f * Skala_liter * (float)(1.0 - mnoznik), 100.0f * Skala_liter, 100.0f * Skala_liter * mnoznik}, {50.0f * Skala_liter, 50.0f * Skala_liter}, 0.0, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla + grafiki->pole1.wys * 0.5f * (float)(1.0 - mnoznik), grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f * mnoznik }, { x, y + 100.0f * Skala_liter * (float)(1.0 - mnoznik), 96.0f * Skala_liter, 96.0f * Skala_liter * mnoznik }, { 48.0f * Skala_liter, 48.0f * Skala_liter }, 0.0, Fade(ColorBrightness(barwnik, 0.0f), duch));


								if (abs(X_GRANICA * 0.5f - x) < 62.5f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y + 50.0f * Skala_liter * (1.0f - mnoznik))) < 62.5f * Skala_liter * mnoznik + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if ((Typ_animacji == 'z' || Typ_animacji == 'a')) Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								break;

							case 7://JG:Typ animacji 8 (wsuwany w prawo)
								mnoznik = (float)((double)(Widzialnosc - 700) * 0.01);

								//JG:rysowanie obrysow
								DrawRectanglePro({ x + 100.0f * Skala_liter * (float)(1.0 - mnoznik), y, 100.0f * Skala_liter * mnoznik, 100.0f * Skala_liter }, { 50.0f * Skala_liter, 50.0f * Skala_liter }, 0.0, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								//JG:rysowanie tekstur
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla + grafiki->pole1.szer * 0.5f * (float)(1.0 - mnoznik), zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f * mnoznik, grafiki->pole1.wys * 0.5f }, { x + 100.0f * Skala_liter * (float)(1.0 - mnoznik), y, 96.0f * Skala_liter * mnoznik, 96.0f * Skala_liter }, { 48.0f * Skala_liter, 48.0f * Skala_liter }, 0.0, Fade(ColorBrightness(barwnik, 0.0f), duch));


								if (abs(X_GRANICA * 0.5f - (x + 50.0f * Skala_liter * (1.0f - mnoznik))) < 62.5f * Skala_liter * mnoznik + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 62.5f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if ((Typ_animacji == 'z' || Typ_animacji == 'a')) Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								break;
							
							}

							//JG:niezalezne od typu animacji

							if (Typ_animacji == 'o') {//JG:rysowanie iskierek i plomieni

								if (Widzialnosc % 100 > 89) {//JG:zaplon
									DrawCircle(x, y, 5.0f * (float)(10 - (Widzialnosc % 100 - 89)) * Skala_liter, Fade(ColorBrightness(barwnik, 0.09f * (float)(10 - (Widzialnosc % 100 - 89))), 0.1f * (float)(10 - (Widzialnosc % 100 - 89))));
									DrawCircle(x, y, 3.0f * (float)(10 - (Widzialnosc % 100 - 89)) * Skala_liter, Fade(ColorBrightness(barwnik2, 0.09f * (float)(10 - (Widzialnosc % 100 - 89))), 0.1f * (float)(10 - (Widzialnosc % 100 - 89))));
								}
								else {//JG:Plomien
									DrawCircle(x, y, 5.0f * (float)(10 - ((Widzialnosc % 100) % 10)) * (1.0f - 0.01f * (float)(100 - ((Widzialnosc % 100) % 89))) * Skala_liter, Fade(ColorBrightness(barwnik, 0.06f * (float)(5 - (Widzialnosc % 100) % 5)), 0.1f * (float)(5 - (Widzialnosc % 100 - 89) % 5)));
									DrawCircle(x, y, 3.0f * (float)(10 - ((Widzialnosc % 100) % 10)) * (1.0f - 0.01f * (float)(100 - ((Widzialnosc % 100) % 89))) * Skala_liter, Fade(ColorBrightness(barwnik2, 0.06f * (float)(5 - (Widzialnosc % 100) % 5)), 0.3f * (float)(5 - (Widzialnosc % 100 - 89) % 5)));
								}
								//JG:Iskry
								pom = (rand() % 3 + 1) * rand() % (((Widzialnosc % 100) / 9) + 1) + 3 * ((Widzialnosc % 100) / 10);//JG:losowanie liczby iskierek
								for (int i = 0; i < pom; i++) {

									switch (rand() % 2 + 1) {
									default:
									case 1:
										DrawCircle(x + (-50.0f + (float)(rand() % 101)) * Skala_liter, y + (-50.0f + (float)(rand() % 101)) * Skala_liter, 0.25f * (float)(rand() % 10 + 1) * Skala_liter, Fade(ColorBrightness(barwnik2, 0.06f * (float)(rand() % 5 + 1)), 0.3f * (float)(rand() % 5 + 1)));
										break;
									case 2:
										DrawCircle(x + (-50.0f + (float)(rand() % 101)) * Skala_liter, y + (-50.0f + (float)(rand() % 101)) * Skala_liter, 0.25f * (float)(rand() % 10 + 1) * Skala_liter, Fade(ColorBrightness(barwnik, 0.06f * (float)(rand() % 5 + 1)), 0.3f * (float)(rand() % 5 + 1)));
										break;
									}
								}

							}

							//JG:Postep animacji
							identyfikator = identyfikator - Wskazik_do_etapu_znikania_pojawiania;
							if (!zmienne->pauza) {
								if (Typ_animacji == 'z' || Typ_animacji == 'o') {//JG:Spadek widzialnosci
									zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] - 1;
									if (zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] < 1 + 100 * (Widzialnosc / 100)) {
										zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = 0;
										if (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[0] == 'w') zmienne->L_etapy_znikania[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = zmienne->L_etapy_znikania[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] + 1;
									}

								}
								else if (Typ_animacji == 'a') {//JG:Wzrost widzialnosci
									zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] + 1;
									if (zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] > 99 + 100 * (Widzialnosc / 100)) {
										zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = -1;
										if (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[0] == 'w') zmienne->L_etapy_znikania[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = zmienne->L_etapy_znikania[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] + 1;
									}

								}
								else {//JG:Nigdy nie powinno miec miejsca
									zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = -1;
								}
							}
							identyfikator = identyfikator + Wskazik_do_etapu_znikania_pojawiania;

						}
					
					}
					break;
					

					//JG:START
				case 's':
					if (x < szer + 50.0f * Skala_liter - TOL && x > -50.0f * Skala_liter + TOL && y < wys + 50.0f * Skala_liter + TOL && y > -50.0f * Skala_liter - TOL) {//JG:Jesli na obszarze okna rysuj
						helper::DrawTextCentered("START", x + 3.0f * Skala_liter, y - 7.0f * Skala_liter, 26.0f * Skala_liter, BLACK);//JG 'cien'
						helper::DrawTextCentered("START", x, y - 10.0f * Skala_liter, 26.0f * Skala_liter, EpisodeTheme.textColor);
					}
					break;

					//JG:META
				case 'm':
					//JG:WEJSCIE
				case '>':
					if (x < szer + 50.0f * Skala_liter - TOL && x > -50.0f * Skala_liter + TOL && y < wys + 50.0f * Skala_liter + TOL && y > -50.0f * Skala_liter - TOL) {//JG:Jesli na obszarze okna rysuj
						
						if (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == '>') {
							helper::DrawTextCentered("DRZWI", x + 3.0f * Skala_liter, y - 7.0f * Skala_liter, 26.0f * Skala_liter, BLACK);//JG 'cien'
							helper::DrawTextCentered("DRZWI", x, y - 10.0f * Skala_liter, 26.0f * Skala_liter, EpisodeTheme.textColor);
						}
						else if (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'm') {
							helper::DrawTextCentered("META", x + 3.0f * Skala_liter, y - 7.0f * Skala_liter, 26.0f * Skala_liter, BLACK);//JG 'cien'
							helper::DrawTextCentered("META", x, y - 10.0f * Skala_liter, 26.0f * Skala_liter, EpisodeTheme.textColor);
						}
						
						if (abs(X_GRANICA * 0.5f - x) < 44.0f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 44.0f * Skala_liter + TOL) {//JG:Jak gracz na drzwiach (w centralnej czesci)
							
							if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
								
								if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'l') {//JG:Przy nastepnym labiryncie wezmie jego parametry z tablicy quizow zamiast obecnuch
									zmienne->biezacy_labirynt = zmienne->biezacy_labirynt + 1;
								} 
								else if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'q') {
									zmienne->biezacy_quiz = zmienne->biezacy_quiz + 1;
								}
								
								zmienne->biezacy_etap = zmienne->biezacy_etap + 1;
								
								if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'l') {//JG:NASTEPNY ETAP - LABIRYNT

									zmienne->plansza_x = 0.0f;
									zmienne->plansza_y = 0.0f;
									zmienne->kontrola_czas = zmienne->czas;//JG:zapis danych do punktu kontrolnego
									zmienne->kontrola_wynik = zmienne->wynik;

									if (zmienne->L_widzialnosc != NULL) delete[] zmienne->L_widzialnosc;
									zmienne->L_widzialnosc = new int[zmienne->L_widzialnosc_N[zmienne->biezacy_labirynt]];
									for (int i = 0; i < zmienne->L_widzialnosc_N[zmienne->biezacy_labirynt]; i++) {
										zmienne->L_widzialnosc[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].widzialnosc[i];
									}

									if (zmienne->L_etapy_znikania != NULL) delete[] zmienne->L_etapy_znikania;
									zmienne->L_etapy_znikania = new char[zmienne->L_etapy_znikania_N[zmienne->biezacy_labirynt]];
									for (int i = 0; i < zmienne->L_etapy_znikania_N[zmienne->biezacy_labirynt]; i++) {
										zmienne->L_etapy_znikania[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].etapy_znikania[i];
									}

								}
								else if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'q') {//JG:NASTEPNY ETAP - QUIZ
									
									zmienne->punkty = 0.0;
									zmienne->proba = 1;
									zmienne->odp_zaznaczona = 'A';
									zmienne->ministan = 'q';
									zmienne->proba_max = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_proby;
									zmienne->punkty_wymagane = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_prog_punktowy;
									zmienne->punkty_straznik = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_prog_bezpieczenstwa;
									zmienne->wyzwanie = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_wyzwanie;
									stanGry = StanEkranu::GRA_QUIZ;

								}
								else if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == '=') {//JG:KONIEC POZIOMU

									zmienne->wynik = zmienne->wynik
										* (1.0 + (zmienne->limit_czas - zmienne->czas) / (zmienne->limit_czas + zmienne->czas))
										* (1.0 + (((double)zmienne->limit_cofniecia - (double)zmienne->cofniecia) / (double)zmienne->limit_cofniecia));

									zmienne->ministan = 'z';
									stanGry = PODSUMOWANIE;
									zmienne->LAB_czulosc_przycisku[0] = 25;
									SetMouseCursor(1);
									zmienne->kurosr_czulosc = 0;

								}

							}
						}
					}
					break;

					//JG:WYJSCIE
				case '<':
					if (x < szer + 50.0f * Skala_liter - TOL && x > -50.0f * Skala_liter + TOL && y < wys + 50.0f * Skala_liter + TOL && y > -50.0f * Skala_liter - TOL) {//JG:Jesli na obszarze okna rysuj
						helper::DrawTextCentered("WEJSCIE", x + 3.0f * Skala_liter, y - 5.0f * Skala_liter, 20.0f * Skala_liter, BLACK);//JG 'cien'
						helper::DrawTextCentered("WEJSCIE", x, y - 8.0f * Skala_liter, 20.0f * Skala_liter, EpisodeTheme.textColor);
					}
					break;

					//JG:JEDNORAZOWO ZMIENNA WIDZIALNOSC
				case 'q':
					Widzialnosc = zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]];
					Wskazik_do_etapu_znikania_pojawiania = 1;
					Typ_animacji = zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + Wskazik_do_etapu_znikania_pojawiania];
					if (Typ_animacji == 'c') Typ_animacji == 'a';
					else if (Typ_animacji == 'x') Typ_animacji == 'z';
					break;

					//JG:WIELOKROTNIE ZMIENNA WIDZIALNOSC etapy_znikania
				case 'w':
					pom = zmienne->L_etapy_znikania[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]];
					if (pom < 1) zmienne->koniec = true;
					identyfikator = identyfikator + 1;
					Widzialnosc = zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]];
					Wskazik_do_etapu_znikania_pojawiania = pom;
					Typ_animacji = zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + Wskazik_do_etapu_znikania_pojawiania];
					if (Typ_animacji == 'c') Typ_animacji == 'a';
					else if (Typ_animacji == 'x') Typ_animacji == 'z';
					charakter = charakter + pom - 1;
					break;

					//JG:ZAPADNIA/POZAR
				case 'o':
				case 'z':
					identyfikator = identyfikator + Wskazik_do_etapu_znikania_pojawiania;
					if (Widzialnosc == -1 &&
						zmienne->poziomik.labirynty[obecny_labirynt].zapadnie_czas[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] * tempo < zmienne->czas - zmienne->kontrola_czas &&
						zmienne->poziomik.labirynty[obecny_labirynt].zapadnie_czas[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] * tempo + 0.2 > zmienne->czas - zmienne->kontrola_czas) {
						identyfikator = identyfikator - Wskazik_do_etapu_znikania_pojawiania;
						zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = (rand() % 8 + 1) * 100 - 1;
						identyfikator = identyfikator + Wskazik_do_etapu_znikania_pojawiania;
					}
					pom = identyfikator;
					//JG:opuszczenie strefy identyfikatorow dla znikania/pojawiania sie (do tablic czasow, widzialnosci, zmiennych aktywacji, czasu odblokowan
					while (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'q' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'w' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'z' ||
					   	   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'o' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'x' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'a' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'c' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'd') {
						identyfikator = identyfikator + 1;
						Wskazik_do_etapu_znikania_pojawiania = Wskazik_do_etapu_znikania_pojawiania + 1;
						charakter = charakter + 1;
					}
					charakter = charakter - 1;
					break;

					//JG:POJAWIAJACE SIE
				case 'a':
					identyfikator = identyfikator + Wskazik_do_etapu_znikania_pojawiania;
					if (Widzialnosc == 0 &&
						zmienne->poziomik.labirynty[obecny_labirynt].pojawiajace_czas[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] * tempo < zmienne->czas - zmienne->kontrola_czas &&
						zmienne->poziomik.labirynty[obecny_labirynt].pojawiajace_czas[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] * tempo + 0.2 > zmienne->czas - zmienne->kontrola_czas) {
						identyfikator = identyfikator - Wskazik_do_etapu_znikania_pojawiania;
						zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = (rand() % 8 + 0) * 100 + 1;
						identyfikator = identyfikator + Wskazik_do_etapu_znikania_pojawiania;
					}
					pom = identyfikator;
					//JG:opuszczenie strefy identyfikatorow dla znikania/pojawiania sie (do tablic czasow, widzialnosci, zmiennych aktywacji, czasu odblokowan
					while (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'q' ||
					   	   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'w' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'z' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'o' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'x' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'a' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'c' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] == 'd') {
						identyfikator = identyfikator + 1;
						Wskazik_do_etapu_znikania_pojawiania = Wskazik_do_etapu_znikania_pojawiania + 1;
						charakter = charakter + 1;
					}
					charakter = charakter - 1;
					break;


				default:
					break;

				}
				charakter = charakter + 1;
			}

			element = element + 1;

		}

		//SPRAWDZANIE CZY GRACZ NA MAPIE I ROZPATRYWANIE EFEKTOW JAK NIE
		if (zmienne->opoznienie > 0 || !Gracza_na_planszy || Gracza_skluty) {
			
			if (zmienne->opoznienie % 100 == 1) {
				
				zmienne->opoznienie = 0;
				
				if (zmienne->cofniecia < zmienne->limit_cofniecia) {//JG:Powrot do punktu kontrolnego
					zmienne->cofniecia = zmienne->cofniecia + 1;
					zmienne->wynik = zmienne->kontrola_wynik;
					zmienne->czas = zmienne->kontrola_czas;
					zmienne->pauza = true;
					zmienne->LAB_czulosc_przycisku[1] = 25;
					zmienne->plansza_x = 0.0f;
					zmienne->plansza_y = 0.0f;

					if (zmienne->L_widzialnosc != NULL) delete[] zmienne->L_widzialnosc;
					zmienne->L_widzialnosc = new int[zmienne->L_widzialnosc_N[zmienne->biezacy_labirynt]];
					for (int i = 0; i < zmienne->L_widzialnosc_N[zmienne->biezacy_labirynt]; i++) {
						zmienne->L_widzialnosc[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].widzialnosc[i];
					}

					if (zmienne->L_etapy_znikania != NULL) delete[] zmienne->L_etapy_znikania;
					zmienne->L_etapy_znikania = new char[zmienne->L_etapy_znikania_N[zmienne->biezacy_labirynt]];
					for (int i = 0; i < zmienne->L_etapy_znikania_N[zmienne->biezacy_labirynt]; i++) {
						zmienne->L_etapy_znikania[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].etapy_znikania[i];
					}

				}
				else {//JG:Porazka (wyczerpanie cofniec)
					zmienne->ministan = 'p';
					stanGry = PODSUMOWANIE;
					zmienne->LAB_czulosc_przycisku[0] = 25;
					SetMouseCursor(1);
					zmienne->kurosr_czulosc = 0;
				}
			}
			else if (zmienne->opoznienie > 1){
				zmienne->opoznienie = zmienne->opoznienie - 1;
			}
			else {
				zmienne->opoznienie = 100 * (rand()%9 + 1) - 1;
			}
		}

		//RYSOWANIE GRACZA (AWATAR)
		if (zmienne->opoznienie == 0) {
			DrawTexturePro(grafiki->awatar.text, { 0.0f, 0.0f, grafiki->awatar.szer, grafiki->awatar.wys }, { X_GRANICA * 0.5f, (wys - Y_GRANICA) * 0.5f, 26.0f * Skala_liter, 26.0f * Skala_liter }, { 13.0f * Skala_liter, 13.0f * Skala_liter }, 0.0f, ColorBrightness(WHITE, 0.0f));
		}
		else {
			DrawTexturePro(grafiki->awatar.text, { 0.0f, 0.0f, grafiki->awatar.szer, grafiki->awatar.wys }, { X_GRANICA * 0.5f, (wys - Y_GRANICA) * 0.5f, 26.0f * Skala_liter, 26.0f * Skala_liter }, { 13.0f * Skala_liter, 13.0f * Skala_liter }, 0.0f, Fade(ColorBrightness(BLACK, 0.0f), 0.5f));
			
			char* napis_pom = NULL;
			switch (zmienne->opoznienie / 100) {//JG:losowy tekst niepowodzenia
			default:
			case 0:
				napis_pom = "Cos poszlo nie tak...";
				break;
			case 1:
				napis_pom = "Upss";
				break;
			case 2:
				napis_pom = "Nastepnym razem bedzie lepiej!";
				break;
			case 3:
				napis_pom = "To nie takie proste!";
				break;
			case 4:
				napis_pom = "No i znow to samo...";
				break;
			case 5:
				napis_pom = "Czuje sie jak krolik doswiadczalny";
				break;
			case 6:
				napis_pom = "Chyba zabraklo nam ostroznosci";
				break;
			case 7:
				napis_pom = "Ten labirynt nie jest jednak taki latwy";
				break;
			case 8:
				napis_pom = "Czas na nastepna probe!";
				break;
			}

			DrawRectangle(0.0f, 40.0f * Skala_liter, szer - 272.0f * Skala_liter, 50.0f * Skala_liter, Fade(szata_epizodu, 0.75f));
			DrawRectangle(0.0f, 90.0f * Skala_liter, szer - 272.0f * Skala_liter, 3.0f * Skala_liter, BLACK);

			helper::DrawTextCentered(napis_pom, 0.5f * X_GRANICA + 3.0f * Skala_liter, 53.0f * Skala_liter, 36.0f * Skala_liter, BLACK);//JG 'cien'
			helper::DrawTextCentered(napis_pom, 0.5f * X_GRANICA, 50.0f * Skala_liter, 36.0f * Skala_liter, EpisodeTheme.textColor);
		}


		//JG:Interfejs

		DrawRectangle(szer - 272.0f * Skala_liter, 0.0f, 280.0f * Skala_liter, wys, Fade(szata_epizodu, 0.75f));
		DrawRectangle(0.0f, 0.0f, szer - 272.0f * Skala_liter, 40.0f * Skala_liter, Fade(szata_epizodu, 0.75f));
		DrawRectangle(szer - 274.0f * Skala_liter, 0.0f, 3.0f * Skala_liter, wys, BLACK);
		DrawRectangle(0.0f, 40.0f * Skala_liter, szer - 272.0f * Skala_liter, 3.0f * Skala_liter, BLACK);

		DrawText(TextFormat("Epizod: %d", zmienne->epizod), 10.0f * Skala_liter, 11.5f * Skala_liter, (int)(21.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacy epizod
		DrawText(TextFormat("Poziom: %d", zmienne->poziom), 124.0f * Skala_liter, 11.5f * Skala_liter, (int)(21.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacy poziom
		char* trudnosc_napis = "";
		//MG: nie byłoby najwydajniej użyć mapy?
		// https://en.cppreference.com/w/cpp/container/map
		switch (zmienne->trudnosc_labirynt) {//JG:chyba wydajniejsze niz string i konwersja
		default:
		case '0':
			switch (zmienne->trudnosc_pytania) {
			default:
			case '6':
				trudnosc_napis = "Trudnosc: Poczatkujacy-Odkrywca";
				break;
			case '2':
				trudnosc_napis = "Trudnosc: Poczatkujacy-Uczen";
				break;
			case 's':
				trudnosc_napis = "Trudnosc: Poczatkujacy-Ekspert";
				break;
			}
			break;
		case 'l':
			switch (zmienne->trudnosc_pytania) {
			default:
			case '6':
				trudnosc_napis = "Trudnosc: Latwy-Odkrywca";
				break;
			case '2':
				trudnosc_napis = "Trudnosc: Latwy-Uczen";
				break;
			case 's':
				trudnosc_napis = "Trudnosc: Latwy-Ekspert";
				break;
			}
			break;
		case 'n':
			switch (zmienne->trudnosc_pytania) {
			default:
			case '6':
				trudnosc_napis = "Trudnosc: Normalny-Odkrywca";
				break;
			case '2':
				trudnosc_napis = "Trudnosc: Normalny-Uczen";
				break;
			case 's':
				trudnosc_napis = "Trudnosc: Normalny-Ekspert";
				break;
			}
			break;
		case 't':
			switch (zmienne->trudnosc_pytania) {
			default:
			case '6':
				trudnosc_napis = "Trudnosc: Trudny-Odkrywca";
				break;
			case '2':
				trudnosc_napis = "Trudnosc: Trudny-Uczen";
				break;
			case 's':
				trudnosc_napis = "Trudnosc: Trudny-Ekspert";
				break;
			}
			break;
		case 'm':
			switch (zmienne->trudnosc_pytania) {
			default:
			case '6':
				trudnosc_napis = "Trudnosc: Mistrzowski-Odkrywca";
				break;
			case '2':
				trudnosc_napis = "Trudnosc: Mistrzowski-Uczen";
				break;
			case 's':
				trudnosc_napis = "Trudnosc: Mistrzowski-Ekspert";
				break;
			}
			break;
		}
		DrawText(trudnosc_napis, 228.0f * Skala_liter, 11.5f * Skala_liter, (int)(21.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacy poziom trudnosci
		DrawText(TextFormat("Czas: %0.2lf", zmienne->czas), 622.0f * Skala_liter, 11.5f * Skala_liter, (int)(21.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacy czas

		DrawText(zmienne->nazwa_uzytkownika.c_str(), szer - 258.0f * Skala_liter, 13.5f * Skala_liter, (int)(26.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacego gracza
		//JG:Wyswietla ikony do wynikow:
		DrawTexturePro(grafiki->puchar.text, { 0.0f, 0.0f, grafiki->puchar.szer, grafiki->puchar.wys }, { szer - 258.0f * Skala_liter, 60.0f * Skala_liter, 65.0f * Skala_liter * grafiki->puchar.szer / grafiki->puchar.wys, 65.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, 0.0f));
		DrawTexturePro(grafiki->puchar.text, { 0.0f, 0.0f, grafiki->puchar.szer, grafiki->puchar.wys }, { szer - 75.0f * Skala_liter, 60.0f * Skala_liter, 65.0f * Skala_liter * grafiki->puchar.szer / grafiki->puchar.wys, 65.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, 0.0f));
		DrawText("WYNIKI", szer - 205.0f * Skala_liter, 81.0f * Skala_liter, (int)(33.0f * Skala_liter), napis_epizodu);//JG:wyswietla naglowek
		//JG: poszczegolne wyniki:
		DrawText(TextFormat("Biezacy: %0.2lf (%0.2lf)", zmienne->wynik, zmienne->wynik
			* (1.0 + (zmienne->limit_czas - zmienne->czas) / (zmienne->limit_czas + zmienne->czas))
			* (1.0 + (((double)zmienne->limit_cofniecia - (double)zmienne->cofniecia) / (double)zmienne->limit_cofniecia))
		), szer - 258.0f * Skala_liter, 140.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla obecny wynik biezacego gracza
		DrawText(TextFormat("Rekord gracza: %0.2lf", zmienne->rekord_wlasny), szer - 258.0f * Skala_liter, 162.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla najlepszy wynik biezacego gracza
		DrawText(TextFormat("Rekord lokalny: %0.2lf", zmienne->rekord_lokalny), szer - 258.0f * Skala_liter, 184.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla najlepszy wynik w tej aplikacji
		DrawText(TextFormat("Rekord swiata: %0.2lf", zmienne->rekord_swiata), szer - 258.0f * Skala_liter, 206.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla najlepszy wynik dla tego poziomu na swiecie
		//JG: WYNIKI - KONIEC

		DrawText("ROZGRYWKA", szer - 248.0f * Skala_liter, 242.0f * Skala_liter, (int)(33.0f * Skala_liter), napis_epizodu);//JG:wyswietla naglowek

		if (!zmienne->pauza) DrawText("Ruch [Q]: wlaczony", szer - 258.0f * Skala_liter, 290.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla czy ruch jest aktywny
		else DrawText("Ruch [Q]: wylaczony", szer - 258.0f * Skala_liter, 290.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Limit czasu: %0.2lf", zmienne->limit_czas), szer - 258.0f * Skala_liter, 312.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Cofniecia: %d/%d", zmienne->cofniecia, zmienne->limit_cofniecia), szer - 258.0f * Skala_liter, 334.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		
		if (zmienne->limit_cofniecia > zmienne->cofniecia) {
			DrawText(TextFormat("Czas PK: %0.2lf", zmienne->kontrola_czas), szer - 258.0f * Skala_liter, 356.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
			DrawText(TextFormat("Wynik PK: %0.2lf (%0.2lf)", zmienne->kontrola_wynik, zmienne->kontrola_wynik
				* (1.0 + (zmienne->limit_czas - zmienne->kontrola_czas) / (zmienne->limit_czas + zmienne->kontrola_czas))
				* (1.0 + (((double)zmienne->limit_cofniecia - 1.0 - (double)zmienne->cofniecia) / (double)zmienne->limit_cofniecia))
			), szer - 258.0f * Skala_liter, 378.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}
		else {
			DrawText(TextFormat("Czas PK: ---"), szer - 258.0f * Skala_liter, 356.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
			DrawText(TextFormat("Wynik PK: ---"), szer - 258.0f * Skala_liter, 378.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}

		//JG:PRZYCISK PAUZA
		DrawRectangle(szer - 248.0f * Skala_liter, 410.0f * Skala_liter, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
		float jasnosc_pom = 0.0f;
		if (zmienne->pauza_czulosc == 0 && zmienne->mysz_x > szer - 248.0f * Skala_liter && zmienne->mysz_x < szer - 178.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Wlacz/wylacz ruch", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[0], zmienne->LAB_zaczep_dec_przycisku[1], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { szer - 246.0f * Skala_liter, 412.0f * Skala_liter, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		if (!zmienne->pauza) {
			DrawRectangle(szer - 231.0f * Skala_liter, 422.0f * Skala_liter, 15.0f * Skala_liter, 46.0f * Skala_liter, napis_epizodu);
			DrawRectangle(szer - 210.0f * Skala_liter, 422.0f * Skala_liter, 15.0f * Skala_liter, 46.0f * Skala_liter, napis_epizodu);
		}
		else {
			DrawTriangle({ szer - 190.0f * Skala_liter, 445.0f * Skala_liter }, { szer - 232.0f * Skala_liter, 419.0f * Skala_liter }, { szer - 232.0f * Skala_liter, 471.0f * Skala_liter }, napis_epizodu);
		}

		//JG:PRZYCISK MENU
		DrawRectangle(szer - 163.0f * Skala_liter, 410.0f * Skala_liter, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
		if (zmienne->LAB_czulosc_przycisku[0] == 0 && zmienne->mysz_x > szer - 163.0f * Skala_liter && zmienne->mysz_x < szer - 93.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Wroc do menu glownego", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}
		else jasnosc_pom = 0.0f;
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[2], zmienne->LAB_zaczep_dec_przycisku[3], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { szer - 161.0f * Skala_liter, 412.0f * Skala_liter, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawTriangle({ szer - 106.0f * Skala_liter, 442.0f * Skala_liter }, { szer - 128.0f * Skala_liter, 415.0f * Skala_liter }, { szer - 150.0f * Skala_liter, 442.0f * Skala_liter }, napis_epizodu);
		DrawRectangle(szer - 144.0f * Skala_liter, 442.0f * Skala_liter, 6.0f * Skala_liter, 26.0f * Skala_liter, napis_epizodu);
		DrawRectangle(szer - 131.0f * Skala_liter, 442.0f * Skala_liter, 6.0f * Skala_liter, 26.0f * Skala_liter, napis_epizodu);
		DrawRectangle(szer - 118.0f * Skala_liter, 442.0f * Skala_liter, 6.0f * Skala_liter, 26.0f * Skala_liter, napis_epizodu);
		DrawRectangle(szer - 144.0f * Skala_liter, 442.0f * Skala_liter, 32.0f * Skala_liter, 6.0f * Skala_liter, napis_epizodu);
		DrawRectangle(szer - 144.0f * Skala_liter, 456.0f * Skala_liter, 14.0f * Skala_liter, 12.0f * Skala_liter, napis_epizodu);
		DrawRectangle(szer - 130.0f * Skala_liter, 466.0f * Skala_liter, 14.0f * Skala_liter, 2.0f * Skala_liter, napis_epizodu);
		DrawRectangle(szer - 142.0f * Skala_liter, 423.0f * Skala_liter, 5.0f * Skala_liter, 11.0f * Skala_liter, napis_epizodu);

		//JG:PRZYCISK COFNIECIE DO PUNKTU KONTROLNEGO
		DrawRectangle(szer - 78.0f * Skala_liter, 410.0f * Skala_liter, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
		if (zmienne->cofniecia >= zmienne->limit_cofniecia) {
			jasnosc_pom = -0.75f;
		}
		else if (zmienne->LAB_czulosc_przycisku[1] == 0 && zmienne->mysz_x > szer - 76.0f * Skala_liter && zmienne->mysz_x < szer - 10.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Cofnij sie do PK", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}
		else jasnosc_pom = 0.0f;
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[4], zmienne->LAB_zaczep_dec_przycisku[5], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { szer - 76.0f * Skala_liter, 412.0f * Skala_liter, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawRectangle(szer - 62.0f * Skala_liter, 464.0f * Skala_liter, 32.0f * Skala_liter, 4.0f * Skala_liter, napis_epizodu);
		DrawRectangle(szer - 55.0f * Skala_liter, 420.0f * Skala_liter, 4.0f * Skala_liter, 44.0f * Skala_liter, napis_epizodu);
		DrawTriangle({ szer - 52.0f * Skala_liter, 421.0f * Skala_liter }, { szer - 52.0f * Skala_liter, 436.0f * Skala_liter }, { szer - 26.0f * Skala_liter, 428.5f * Skala_liter }, napis_epizodu);
		DrawTriangle({ szer - 36.0f * Skala_liter, 453.0f * Skala_liter }, { szer - 28.0f * Skala_liter, 462.0f * Skala_liter }, { szer - 28.0f * Skala_liter, 444.0f * Skala_liter }, napis_epizodu);
		DrawTriangle({ szer - 42.0f * Skala_liter, 453.0f * Skala_liter }, { szer - 34.0f * Skala_liter, 462.0f * Skala_liter }, { szer - 34.0f * Skala_liter, 444.0f * Skala_liter }, napis_epizodu);

		//JG:SUWAK GLOSNOSCI
		DrawRectangle(szer - 228.0f * Skala_liter, 520.0f * Skala_liter, 190.0f * Skala_liter, 20.0f * Skala_liter, napis_epizodu);
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[6], zmienne->LAB_zaczep_dec_przycisku[7], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { szer - 226.0f * Skala_liter, 522.0f * Skala_liter, 186.0f * Skala_liter, 16.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, 0.0f));
		//JG:PRZYCISK MUTE SUWAKA
		DrawRectangle(szer - 257.0f * Skala_liter, 515.0f * Skala_liter, 30.0f * Skala_liter, 30.0f * Skala_liter, napis_epizodu);
		if (zmienne->LAB_czulosc_przycisku[2] == 0 && zmienne->mysz_x > szer - 255.0f * Skala_liter && zmienne->mysz_x < szer - 229.0f * Skala_liter && zmienne->mysz_y > 517.0f * Skala_liter && zmienne->mysz_y < 543.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Wycisz dzwiek", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}
		else jasnosc_pom = 0.0f;
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[8], zmienne->LAB_zaczep_dec_przycisku[9], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { szer - 255.0f * Skala_liter, 517.0f * Skala_liter, 26.0f * Skala_liter, 26.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawRectangle(szer - 251.0f * Skala_liter, 527.0f * Skala_liter, 6.0f * Skala_liter, 6.0f * Skala_liter, napis_epizodu);
		DrawTriangle({ szer - 251.0f * Skala_liter, 530.0f * Skala_liter }, { szer - 233.0f * Skala_liter, 538.0f * Skala_liter }, { szer - 233.0f * Skala_liter, 522.0f * Skala_liter }, napis_epizodu);
		DrawLineEx({ szer - 257.0f * Skala_liter, 516.0f * Skala_liter }, { szer - 229.0f * Skala_liter, 544.0f * Skala_liter }, 1.5f * Skala_liter, ColorBrightness(napis_epizodu, -0.3f));
		//JG:PRZYCISK MAKS GLOSNOSC SUWAKA
		DrawRectangle(szer - 39.0f * Skala_liter, 515.0f * Skala_liter, 30.0f * Skala_liter, 30.0f * Skala_liter, napis_epizodu);
		if (zmienne->LAB_czulosc_przycisku[3] == 0 && zmienne->mysz_x > szer - 37.0f * Skala_liter && zmienne->mysz_x < szer - 11.0f * Skala_liter && zmienne->mysz_y > 517.0f * Skala_liter && zmienne->mysz_y < 543.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Maksymalna glosnosc", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}
		else jasnosc_pom = 0.0f;
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[10], zmienne->LAB_zaczep_dec_przycisku[11], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { szer - 37.0f * Skala_liter, 517.0f * Skala_liter, 26.0f * Skala_liter, 26.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawRectangle(szer - 33.0f * Skala_liter, 527.0f * Skala_liter, 6.0f * Skala_liter, 6.0f * Skala_liter, napis_epizodu);
		DrawTriangle({ szer - 33.0f * Skala_liter, 530.0f * Skala_liter }, { szer - 15.0f * Skala_liter, 538.0f * Skala_liter }, { szer - 15.0f * Skala_liter, 522.0f * Skala_liter }, napis_epizodu);
		//JG:RACZKA SUWAKA
		float pozX_pom = szer - 227.0f * Skala_liter + zmienne->glosnosc * 0.01f * 160.0f * Skala_liter;
		DrawRectangle(pozX_pom, 515.0f * Skala_liter, 30.0f * Skala_liter, 30.0f * Skala_liter, napis_epizodu);
		if (zmienne->mysz_x > pozX_pom + 2.0f * Skala_liter && zmienne->mysz_x < pozX_pom + 28.0f * Skala_liter && zmienne->mysz_y > 517.0f * Skala_liter && zmienne->mysz_y < 543.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Zmien glosnosc", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		}
		else jasnosc_pom = 0.0f;
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[12], zmienne->LAB_zaczep_dec_przycisku[13], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { pozX_pom + 2.0f * Skala_liter, 517.0f * Skala_liter, 26.0f * Skala_liter, 26.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));





	}

	void updateLabirynt(grafika* tlo) {
		
		//JG:USTAWIANIE ZMIENNYCH ZWIAZANYCH Z WYMIARAMI OKNA
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		float Skala_liter = 1.0;
		if (szer >= wys * tlo->szer / tlo->wys) {
			Skala_liter = wys / OknoWysBaz;
		}
		else {
			Skala_liter = szer / OknoSzerBaz;
		}
		//JG:AKTUALIZACJA DANYCH KURSORA
		if (IsCursorOnScreen()) {
			zmienne->mysz_pop_x = zmienne->mysz_x;
			zmienne->mysz_pop_y = zmienne->mysz_y;
			zmienne->mysz_x = GetMouseX();
			zmienne->mysz_y = GetMouseY();
		}
		//JG:PRZESUNIECIE PLANSZY
		if (IsCursorOnScreen() && !zmienne->pauza && zmienne->opoznienie == 0) {
			float zmiana_x = ((-1) * zmienne->mysz_x + zmienne->mysz_pop_x);
			float zmiana_y = ((-1) * zmienne->mysz_y + zmienne->mysz_pop_y);
			if (zmiana_x > ODLEGLOSC_MIEDZY_POLAMI + TOL) zmiana_x = ODLEGLOSC_MIEDZY_POLAMI;//JG:zabezpieczenie przed teleportacja na skutek blyskawicznego ruchu myszka
			if (zmiana_y > ODLEGLOSC_MIEDZY_POLAMI + TOL) zmiana_y = ODLEGLOSC_MIEDZY_POLAMI;
			zmienne->plansza_x = zmienne->plansza_x + zmiana_x;
			zmienne->plansza_y = zmienne->plansza_y + zmiana_y;
		}
		//JG:PRZYCISK PAUZA
		if (!zmienne->pauza) {
			zmienne->czas = zmienne->czas + 0.01;
		}
		if (zmienne->pauza_czulosc > 0) {
			zmienne->pauza_czulosc = zmienne->pauza_czulosc - 1;
		}
		else if (zmienne->pauza_czulosc != 0) {
			zmienne->pauza_czulosc = 0;
		}
		else if (IsKeyDown(KEY_Q) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > szer - 248.0f * Skala_liter && zmienne->mysz_x < szer - 178.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter)) {
			zmienne->pauza = !zmienne->pauza;
			zmienne->pauza_czulosc = 25;
		}
		//JG:PRZYCISK >> MENU
		if (zmienne->LAB_czulosc_przycisku[0] > 0) {
			zmienne->LAB_czulosc_przycisku[0] = zmienne->LAB_czulosc_przycisku[0] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[0] != 0) {
			zmienne->LAB_czulosc_przycisku[0] = 0;
		}
		else if ((IsKeyDown(KEY_P) && (IsKeyDown(KEY_O))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > szer - 163.0f * Skala_liter && zmienne->mysz_x < szer - 93.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter)) {
			stanGry = MAIN_MENU;
			zmienne->LAB_czulosc_przycisku[0] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}

		//JG:PRZYCISK >> PUNKT KONTROLNY (COFNIECIE)
		if (zmienne->LAB_czulosc_przycisku[1] > 0) {
			zmienne->LAB_czulosc_przycisku[1] = zmienne->LAB_czulosc_przycisku[1] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[1] != 0) {
			zmienne->LAB_czulosc_przycisku[1] = 0;
		}
		else if (!(zmienne->cofniecia >= zmienne->limit_cofniecia) && ((IsKeyDown(KEY_K) && (IsKeyDown(KEY_L))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > szer - 76.0f * Skala_liter && zmienne->mysz_x < szer - 10.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter))) {
			
			zmienne->opoznienie = 0;
			zmienne->cofniecia = zmienne->cofniecia + 1;
			zmienne->wynik = zmienne->kontrola_wynik;
			zmienne->czas = zmienne->kontrola_czas;
			zmienne->pauza = true;
			zmienne->LAB_czulosc_przycisku[1] = 25;

			if (zmienne->L_widzialnosc != NULL) delete[] zmienne->L_widzialnosc;
			zmienne->L_widzialnosc = new int[zmienne->L_widzialnosc_N[zmienne->biezacy_labirynt]];
			for (int i = 0; i < zmienne->L_widzialnosc_N[zmienne->biezacy_labirynt]; i++) {
				zmienne->L_widzialnosc[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].widzialnosc[i];
			}

			if (zmienne->L_etapy_znikania != NULL) delete[] zmienne->L_etapy_znikania;
			zmienne->L_etapy_znikania = new char[zmienne->L_etapy_znikania_N[zmienne->biezacy_labirynt]];
			for (int i = 0; i < zmienne->L_etapy_znikania_N[zmienne->biezacy_labirynt]; i++) {
				zmienne->L_etapy_znikania[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].etapy_znikania[i];
			}

			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
			zmienne->plansza_x = 0.0f;
			zmienne->plansza_y = 0.0f;
		}

		//JG:PRZYCISK WYCISZ (MUTE)
		if (zmienne->LAB_czulosc_przycisku[2] > 0) {
			zmienne->LAB_czulosc_przycisku[2] = zmienne->LAB_czulosc_przycisku[2] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[2] != 0) {
			zmienne->LAB_czulosc_przycisku[2] = 0;
		}
		else if (IsKeyDown(KEY_M) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > szer - 255.0f * Skala_liter && zmienne->mysz_x < szer - 229.0f * Skala_liter && zmienne->mysz_y > 517.0f * Skala_liter && zmienne->mysz_y < 543.0f * Skala_liter)) {
			zmienne->glosnosc = 0.0f;
			zmienne->LAB_czulosc_przycisku[2] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}

		//JG:PRZYCISK MAKS GLOSNOSC
		if (zmienne->LAB_czulosc_przycisku[3] > 0) {
			zmienne->LAB_czulosc_przycisku[3] = zmienne->LAB_czulosc_przycisku[3] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[3] != 0) {
			zmienne->LAB_czulosc_przycisku[3] = 0;
		}
		else if (IsKeyDown(KEY_U) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > szer - 37.0f * Skala_liter && zmienne->mysz_x < szer - 11.0f * Skala_liter && zmienne->mysz_y > 517.0f * Skala_liter && zmienne->mysz_y < 543.0f * Skala_liter)) {
			zmienne->glosnosc = 100.0f;
			zmienne->LAB_czulosc_przycisku[3] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}

		//JG:PRZYCISK SUWAK
		float pozX_pom = szer - 227.0f * Skala_liter + zmienne->glosnosc * 0.01f * 160.0f * Skala_liter;
		if ((IsMouseButtonDown(MOUSE_LEFT_BUTTON) && zmienne->mysz_pop_x > pozX_pom + 2.0f * Skala_liter && zmienne->mysz_pop_x < pozX_pom + 28.0f * Skala_liter && zmienne->mysz_pop_y > 517.0f * Skala_liter && zmienne->mysz_pop_y < 543.0f * Skala_liter)) {
			if (zmienne->mysz_x <= szer - 212.0f * Skala_liter) zmienne->glosnosc = 0.0f;
			else if (zmienne->mysz_x >= szer - 52.0f * Skala_liter) zmienne->glosnosc = 100.0f;
			else zmienne->glosnosc = (zmienne->mysz_x - szer + 212.0f * Skala_liter) / (1.6f * Skala_liter);
		}
		
		/*for (auto& B : Buttons) {
			B.update();
		}*/
	}


}