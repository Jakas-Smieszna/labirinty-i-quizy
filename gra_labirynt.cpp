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

		int obecny_labirynt = zmienne->biezacy_labirynt;
		int element = 0;//JG: int do przechodzenia po kolei wszytskich elementow w labiryncie
		while (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[0] != '=') {
			
			int charakter = 0;//JG: int do przechodzenia po tablicy charakterow
			int identyfikator = 0;//JG: int do przechodzenia po tablicy ID-kow
			float x = zmienne->plansza_x * Skala_liter + X_GRANICA * 0.5f + Skala_liter * (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].x);
			float y = zmienne->plansza_y * Skala_liter + (wys - Y_GRANICA) * 0.5f + Skala_liter * (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].y);
			duch = 1.0;
			Widzialnosc = -1;
			Typ_animacji = '0';
			Wskazik_do_etapu_znikania_pojawiania = 0;

			while (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter] != '-') {
				int pom = 0;
				
				switch (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter]) {

					//JG:POLE
				case 'p':
					if (zmienne->epizod == 4) duch = 0.5f;
					if (x < szer + 50.0f * Skala_liter - TOL && x > -50.0f * Skala_liter + TOL && y < wys + 50.0f * Skala_liter + TOL && y > -50.0f * Skala_liter - TOL) {//JG:Jesli na obszarze okna rysuj
						
						if (Widzialnosc == -1) {//JG:Widoczne i aktywne
							DrawRectangle(x - 50.0f * Skala_liter, y - 50.0f * Skala_liter, 100.0f * Skala_liter, 100.0f * Skala_liter, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
							DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { x, y, 96.0f * Skala_liter, 96.0f * Skala_liter }, { 48.0f * Skala_liter, 48.0f * Skala_liter }, 0.0f, Fade(ColorBrightness(WHITE, 1.0f), duch));
							if (!Gracza_na_planszy && abs(X_GRANICA * 0.5f - x) < 62.5f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - y) < 62.5f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
								Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
							}
							break;
						
						}
						else if (Widzialnosc > 0) {//JG:W animacji if(TAK) lub niewidoczny (nieaktywny) if(NIE)

							float mnoznik = 0.0f;
							Color barwnik = WHITE;
							switch ((Widzialnosc / 100)) {
							
							case 0://JG:Typ animacji 1 (od/dosrodkowe 4 kwadraty)
								mnoznik = (float)((double)Widzialnosc * 0.01);
								if (Typ_animacji == 'o') { 
									duch = duch * (float)((double)Widzialnosc / 100.0);
									switch (zmienne->epizod) {
									default:
									case 1:
									case 2:
										barwnik = ORANGE;
										break;
									case 3:
									case 4:
										barwnik = BLUE;
										break;
									}
								}
								
								DrawRectangle(x - 50.0f * Skala_liter, y - 50.0f * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
								DrawRectangle(x + (50.0f - 50.0f * mnoznik) * Skala_liter, y - 50.0f * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
								DrawRectangle(x - 50.0f * Skala_liter, y + (50.0f - 50.0f * mnoznik) * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));
								DrawRectangle(x + (50.0f - 50.0f * mnoznik) * Skala_liter, y + (50.0f - 50.0f * mnoznik) * Skala_liter, 50.0f * Skala_liter * mnoznik, 50.0f * Skala_liter * mnoznik, Fade(ColorBrightness(napis_epizodu, -0.8f), 1.5f * duch));

								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { 49.0f * Skala_liter, 49.0f * Skala_liter }, 0.0f, Fade(ColorBrightness(barwnik, 1.0f), duch));
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla + grafiki->pole1.szer * 0.25f * (1.0f -mnoznik), zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla, grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { -49.0f * Skala_liter * (1.0f - mnoznik), 49.0f * Skala_liter}, 0.0f, Fade(ColorBrightness(barwnik, 1.0f), duch));
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla, zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla + grafiki->pole1.wys * 0.25f * (1.0f - mnoznik), grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { 49.0f * Skala_liter, -49.0f * Skala_liter * (1.0f - mnoznik) }, 0.0f, Fade(ColorBrightness(barwnik, 1.0f), duch));
								DrawTexturePro(grafiki->pole1.text, { zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].x_zrodla + grafiki->pole1.szer * 0.25f * (1.0f - mnoznik), zmienne->poziomik.labirynty[obecny_labirynt].pola[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]].y_zrodla + grafiki->pole1.wys * 0.25f * (1.0f - mnoznik), grafiki->pole1.szer * 0.25f * mnoznik, grafiki->pole1.wys * 0.25f * mnoznik }, { x, y, 48.0f * Skala_liter * mnoznik, 48.0f * Skala_liter * mnoznik }, { -49.0f * Skala_liter * (1.0f - mnoznik), -49.0f * Skala_liter * (1.0f - mnoznik) }, 0.0f, Fade(ColorBrightness(barwnik, 1.0f), duch));

								if (!Gracza_na_planszy && abs(X_GRANICA * 0.5f - (x - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if(Typ_animacji == 'z') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								if (!Gracza_na_planszy && abs(X_GRANICA * 0.5f - (x + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (Typ_animacji == 'z') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								if (!Gracza_na_planszy && abs(X_GRANICA * 0.5f - (x - (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (Typ_animacji == 'z') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}
								if (!Gracza_na_planszy && abs(X_GRANICA * 0.5f - (x + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL && abs((wys - Y_GRANICA) * 0.5f - (y + (50.0f - 25.0f * mnoznik) * Skala_liter)) < 31.25f * Skala_liter + TOL) {//JG:Jak gracz na polu i nie wiadomo czy na planszy
									if (Typ_animacji == 'z') Gracza_na_planszy = true;//JG:to zaznacz, ze jest na planszy i nie spada
									else if (Typ_animacji == 'o') Gracza_skluty = true;//JG:to zaznacz, ze jest na ogniu i sie pali
								}

								if (!zmienne->pauza) {
									if (Typ_animacji == 'z' || Typ_animacji == 'o') {//JG:Spadek widzialnosci
										zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] - 1;
										if (zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] < 1) zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = 0;
									}
									else if (Typ_animacji == 'a') {//JG:Wzrost widzialnosci
										zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] + 1;
										if (zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] > 99) zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = -1;
									}
									else {//JG:Nigdy nie powinno miec miejsca
										zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = -1;
									}
								}

								break;

							default:
								break;
							
							}
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
					if (x < szer + 50.0f * Skala_liter - TOL && x > -50.0f * Skala_liter + TOL && y < wys + 50.0f * Skala_liter + TOL && y > -50.0f * Skala_liter - TOL) {//JG:Jesli na obszarze okna rysuj
						helper::DrawTextCentered("META", x + 3.0f * Skala_liter, y - 7.0f * Skala_liter, 26.0f * Skala_liter, BLACK);//JG 'cien'
						helper::DrawTextCentered("META", x, y - 10.0f * Skala_liter, 26.0f * Skala_liter, EpisodeTheme.textColor);
					}
					break;

					//JG:WEJSCIE
				case '>':
					if (x < szer + 50.0f * Skala_liter - TOL && x > -50.0f * Skala_liter + TOL && y < wys + 50.0f * Skala_liter + TOL && y > -50.0f * Skala_liter - TOL) {//JG:Jesli na obszarze okna rysuj
						helper::DrawTextCentered("DRZWI", x + 3.0f * Skala_liter, y - 7.0f * Skala_liter, 26.0f * Skala_liter, BLACK);//JG 'cien'
						helper::DrawTextCentered("DRZWI", x, y - 10.0f * Skala_liter, 26.0f * Skala_liter, EpisodeTheme.textColor);
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

									stanGry = MAIN_MENU;
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

					//JG:ZAPADNIA/POZAR
				case 'o':
				case 'z':
					identyfikator = identyfikator + Wskazik_do_etapu_znikania_pojawiania;
					if (Widzialnosc == -1 &&
						zmienne->poziomik.labirynty[obecny_labirynt].zapadnie_czas[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] < zmienne->czas - zmienne->kontrola_czas &&
						zmienne->poziomik.labirynty[obecny_labirynt].zapadnie_czas[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] + 2.0 > zmienne->czas - zmienne->kontrola_czas) {
						identyfikator = identyfikator - Wskazik_do_etapu_znikania_pojawiania;
						zmienne->L_widzialnosc[zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].ID_tab[identyfikator]] = (rand() % 1 + 1) * 100 - 1;
					}
					else identyfikator = identyfikator - Wskazik_do_etapu_znikania_pojawiania;
					pom = identyfikator;
					//JG:opuszczenie strefy identyfikatorow dla znikania/pojawiania sie (do tablic czasow, widzialnosci, zmiennych aktywacji, czasu odblokowan
					while (zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'q' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'w' || 
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'z' || 
					   	   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'o' || 
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'x' || 
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'a' || 
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'c' ||
						   zmienne->poziomik.labirynty[obecny_labirynt].elementy[element].typ_tab[charakter + identyfikator - pom] == 'd') {
						identyfikator = identyfikator + 1;
					}
					break;

				default:
					break;

				}
				charakter = charakter + 1;
			}

			element = element + 1;

		}

		//SPRAWDZANIE CZY GRACZ NA MAPIE I ROZPATRYWANIE EFEKTOW JAK NIE
		if (!Gracza_na_planszy || Gracza_skluty) {
			if (zmienne->cofniecia < zmienne->limit_cofniecia) {//JG:Powrot do punktu kontrolnego
				zmienne->cofniecia = zmienne->cofniecia + 1;
				zmienne->wynik = zmienne->kontrola_wynik;
				zmienne->czas = zmienne->kontrola_czas;
				zmienne->pauza = true;
				zmienne->LAB_czulosc_przycisku[1] = 25;
				zmienne->plansza_x = 0.0f;
				zmienne->plansza_y = 0.0f;
				for (int i = 0; i < zmienne->L_widzialnosc_N[zmienne->biezacy_labirynt]; i++) {
					zmienne->L_widzialnosc[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].widzialnosc[i];
				}
			}
			else {//JG:Porazka (wyczerpanie cofniec)
				stanGry = MAIN_MENU;
				zmienne->LAB_czulosc_przycisku[0] = 25;
				SetMouseCursor(1);
				zmienne->kurosr_czulosc = 0;
			}
		}

		//RYSOWANIE GRACZA (AWATAR)
		DrawTexturePro(grafiki->awatar.text, { 0.0f, 0.0f, grafiki->awatar.szer, grafiki->awatar.wys }, { X_GRANICA * 0.5f, (wys - Y_GRANICA) * 0.5f, 26.0f * Skala_liter, 26.0f * Skala_liter }, { 13.0f * Skala_liter, 13.0f * Skala_liter }, 0.0f, ColorBrightness(WHITE, 1.0f));



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
		DrawText(TextFormat("Biezacy: %0.2lf", zmienne->wynik), szer - 258.0f * Skala_liter, 140.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla obecny wynik biezacego gracza
		DrawText(TextFormat("Rekord gracza: %0.2lf", zmienne->rekord_wlasny), szer - 258.0f * Skala_liter, 162.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla najlepszy wynik biezacego gracza
		DrawText(TextFormat("Rekord lokalny: %0.2lf", zmienne->rekord_lokalny), szer - 258.0f * Skala_liter, 184.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla najlepszy wynik w tej aplikacji
		DrawText(TextFormat("Rekord swiata: %0.2lf", zmienne->rekord_swiata), szer - 258.0f * Skala_liter, 206.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla najlepszy wynik dla tego poziomu na swiecie
		//JG: WYNIKI - KONIEC

		DrawText("ROZGRYWKA", szer - 248.0f * Skala_liter, 242.0f * Skala_liter, (int)(33.0f * Skala_liter), napis_epizodu);//JG:wyswietla naglowek

		if (!zmienne->pauza) DrawText("Ruch [Q]: wlaczony", szer - 258.0f * Skala_liter, 290.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla czy ruch jest aktywny
		else DrawText("Ruch [Q]: wylaczony", szer - 258.0f * Skala_liter, 290.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Limit czasu: %0.2lf", zmienne->limit_czas), szer - 258.0f * Skala_liter, 312.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Cofniecia: %d/%d", zmienne->cofniecia, zmienne->limit_cofniecia), szer - 258.0f * Skala_liter, 334.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Czas PK: %0.2lf", zmienne->kontrola_czas), szer - 258.0f * Skala_liter, 356.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Wynik PK: %0.2lf", zmienne->kontrola_wynik), szer - 258.0f * Skala_liter, 378.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);

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
		if (IsCursorOnScreen() && !zmienne->pauza) {
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