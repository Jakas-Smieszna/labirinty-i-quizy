#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "Grafika.h"
#include "gamestate.h"
#include "przycisk.h"
#include <string>
#include "Baza.h"
namespace quiz {

	// Rysowanie
	void drawQuiz() {

		if (zmienne->pytanie == NULL) getdata();
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
		DrawRectangle(szer - 272.0f * Skala_liter, 0.0f, 280.0f * Skala_liter, wys, Fade(szata_epizodu, 0.75f));
		DrawRectangle(0.0f, 0.0f, szer - 272.0f * Skala_liter, 40.0f * Skala_liter, Fade(szata_epizodu, 0.75f));
		DrawRectangle(szer - 274.0f * Skala_liter, 0.0f, 3.0f * Skala_liter, wys, BLACK);
		DrawRectangle(0.0f, 40.0f * Skala_liter, szer - 272.0f * Skala_liter, 3.0f * Skala_liter, BLACK);

		float szer_pom = szer - 392.0f * Skala_liter;
		float wys_pom = wys - 240.0f * Skala_liter;

		if (!zmienne->pauza) {
			int linia_dlugosc = (int)((szer_pom - 25.0f * Skala_liter) / (8.0f * Skala_liter));
			if (Skala_liter < 0.60f) linia_dlugosc = (int)((szer_pom - 25.0f * Skala_liter) / (11.0f * Skala_liter));
			else if (Skala_liter < 0.67f) linia_dlugosc = (int)((szer_pom - 25.0f * Skala_liter) / (9.0f * Skala_liter));
			int j = 0;
			int i = 0;
			int odp_fab = 0;//JG:odpowiada za wybor tekstu z fabuly zaleznie od poprawnosci odpowiedzi (tylko do ministanu 'd' lub 'u')
			float nowa_linia = 0.0f;
			bool sekcja_tekstu = true;
			char* napis_pom = "BLAD!";
			DrawRectangle(60.0f * Skala_liter, 80.0f * Skala_liter, szer_pom, wys_pom, Fade(szata_epizodu, 0.75f));
			DrawRectangle(59.0f * Skala_liter, 79.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
			DrawRectangle(59.0f * Skala_liter + szer_pom, 79.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
			DrawRectangle(59.0f * Skala_liter, 79.0f * Skala_liter + wys_pom, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);
			DrawRectangle(59.0f * Skala_liter, 79.0f * Skala_liter, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);

			if (zmienne->ministan == 'q') {
				switch (zmienne->fabula_quizu_ID) {
				case 1:
					napis_pom = "Tajemnicze drzwi";
					break;
				default:
					napis_pom = "Poczucie humoru autorow";
					break;
				}
				helper::DrawTextCentered(napis_pom, 60.0f * Skala_liter + szer_pom * 0.5f + 5.0f * Skala_liter, 100.0f * Skala_liter, 60.0f * Skala_liter, BLACK);//JG 'cien'
				helper::DrawTextCentered(napis_pom, 60.0f * Skala_liter + szer_pom * 0.5f, 95.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
				nowa_linia = nowa_linia + 75.0f * Skala_liter;


				while (sekcja_tekstu) {
					i = 0;
					char* linia = new char[linia_dlugosc + 1]{};
					while (MeasureTextEx(EpisodeTheme.textFont, linia, (int)(16.0f * Skala_liter), 0.0f).x < szer_pom - 25.0f * Skala_liter - TOL && i < linia_dlugosc && zmienne->pytanie_opis[j] != '\n' && zmienne->pytanie_opis[j] != '\0') {
						if (!(i == 0 && zmienne->pytanie_opis[j] == ' ')) linia[i] = zmienne->pytanie_opis[j];
						else i--;
						j++;
						i++;
					}
					linia[i] = '\0';
					if (zmienne->pytanie_opis[j] == '\0') sekcja_tekstu = false;
					while (linia[i] != ' ' && sekcja_tekstu) {
						linia[i] = '\0';
						i--;
						j--;
					}
					DrawText(linia, 70.0f * Skala_liter, 90.5f * Skala_liter + nowa_linia, (int)(16.0f * Skala_liter), napis_epizodu);
					delete[] linia;
					nowa_linia = nowa_linia + 26.0f * Skala_liter;
				}
				sekcja_tekstu = true;
				j = 0;
				for (int k = 0; k < 5; k++) {
					sekcja_tekstu = true;
					while (sekcja_tekstu) {
						i = 0;
						char* linia = new char[linia_dlugosc + 1];
						for (i; i < linia_dlugosc && zmienne->pytanie[j] != '\n' && zmienne->pytanie[j] != '\0'; i++) {
							if (!(i == 0 && zmienne->pytanie[j] == ' ')) linia[i] = zmienne->pytanie[j];
							else i--;
							j++;
						}
						linia[i] = '\0';
						if (zmienne->pytanie[j] == '\n') {
							sekcja_tekstu = false;
							j++;
						}
						else if (zmienne->pytanie[j] == '\0') sekcja_tekstu = false;
						while (linia[i] != ' ' && sekcja_tekstu) {
							linia[i] = '\0';
							i--;
							j--;
						}
						DrawText(linia, 70.0f * Skala_liter, 90.5f * Skala_liter + nowa_linia, (int)(16.0f * Skala_liter), napis_epizodu);
						delete[] linia;
						nowa_linia = nowa_linia + 26.0f * Skala_liter;
					}
				}
			}
			else if (zmienne->ministan == 'd' || zmienne->ministan == 'u') {
				
				if (zmienne->ministan == 'u') {
					if (zmienne->punkty >= zmienne->punkty_wymagane - TOL) {
						odp_fab = 0;
						napis_pom = "Droga wolna!"; 
					}
					else {
						odp_fab = 4;
						napis_pom = "Porazka!";
					}
				}
				else {
					if (zmienne->odp_pop == zmienne->odp_zaznaczona) {
						odp_fab = 1;
						napis_pom = "Sukces!";
					}
					else if (zmienne->punkty_odpowiedzi[(int)(zmienne->odp_zaznaczona - 'A')]) {
						odp_fab = 2;
						napis_pom = "Powoli do przodu";
					}
					else {
						odp_fab = 3;
						napis_pom = "Niepowodzenie";
					}
				}
				helper::DrawTextCentered(napis_pom, 60.0f * Skala_liter + szer_pom * 0.5f + 5.0f * Skala_liter, 100.0f * Skala_liter, 60.0f * Skala_liter, BLACK);//JG 'cien'
				helper::DrawTextCentered(napis_pom, 60.0f * Skala_liter + szer_pom * 0.5f, 95.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
				nowa_linia = nowa_linia + 75.0f * Skala_liter;

				while (sekcja_tekstu) {
					i = 0;
					char* linia = new char[linia_dlugosc + 1];
					for (i; i < linia_dlugosc && zmienne->odp_opis[odp_fab][j] != '\n' && zmienne->odp_opis[odp_fab][j] != '\0'; i++) {
						if (!(i == 0 && zmienne->odp_opis[odp_fab][j] == ' ')) linia[i] = zmienne->odp_opis[odp_fab][j];
						else i--;
						j++;
					}
					linia[i] = '\0';
					if (zmienne->odp_opis[odp_fab][j] == '\0') sekcja_tekstu = false;
					while (linia[i] != ' ' && sekcja_tekstu) {
						linia[i] = '\0';
						i--;
						j--;
					}
					DrawText(linia, 70.0f * Skala_liter, 90.5f * Skala_liter + nowa_linia, (int)(16.0f * Skala_liter), napis_epizodu);
					delete[] linia;
					nowa_linia = nowa_linia + 26.0f * Skala_liter;
				}
				sekcja_tekstu = true;
				j = 0;
				for (int k = 0; k < 5; k++) {
					sekcja_tekstu = true;
					while (sekcja_tekstu) {
						i = 0;
						char* linia = new char[linia_dlugosc + 1];
						for (i; i < linia_dlugosc && zmienne->odp_wytlumaczenie[j] != '\n' && zmienne->odp_wytlumaczenie[j] != '\0'; i++) {
							if (!(i == 0 && zmienne->odp_wytlumaczenie[j] == ' ')) linia[i] = zmienne->odp_wytlumaczenie[j];
							else i--;
							j++;
						}
						linia[i] = '\0';
						if (zmienne->odp_wytlumaczenie[j] == '\n') {
							sekcja_tekstu = false;
							j++;
						}
						else if (zmienne->odp_wytlumaczenie[j] == '\0') sekcja_tekstu = false;
						while (linia[i] != ' ' && sekcja_tekstu) {
							linia[i] = '\0';
							i--;
							j--;
						}
						DrawText(linia, 70.0f * Skala_liter, 90.5f * Skala_liter + nowa_linia, (int)(16.0f * Skala_liter), napis_epizodu);
						delete[] linia;
						nowa_linia = nowa_linia + 26.0f * Skala_liter;
					}
				}
			}
		}


		DrawText(TextFormat("Epizod: %d", zmienne->epizod), 10.0f * Skala_liter, 11.5f * Skala_liter, (int)(21.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacy epizod
		DrawText(TextFormat("Poziom: %d", zmienne->poziom), 124.0f * Skala_liter, 11.5f * Skala_liter, (int)(21.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacy poziom
		char* trudnosc_napis = "";
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

		DrawText("ZAGADKA", szer - 248.0f * Skala_liter, 242.0f * Skala_liter, (int)(33.0f * Skala_liter), napis_epizodu);//JG:wyswietla naglowek

		switch (zmienne->wyzwanie) {
		default:
		case 'b':
			DrawText("Wyzwanie: bezpiecznie", szer - 258.0f * Skala_liter, 290.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla czy ruch jest aktywny
			break;
		case 's':
			DrawText("Wyzwanie: straznik", szer - 258.0f * Skala_liter, 290.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla czy ruch jest aktywny
			break;
		case 'p':
			DrawText("Wyzwanie: pulapka", szer - 258.0f * Skala_liter, 290.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);//JG:wyswietla czy ruch jest aktywny
			break;
		}
		DrawText(TextFormat("Pytanie: %d/%d", zmienne->proba, zmienne->proba_max), szer - 258.0f * Skala_liter, 312.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Punkty: %0.2lf", zmienne->punkty), szer - 258.0f * Skala_liter, 334.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Prog punktowy: %0.2lf", zmienne->punkty_wymagane), szer - 258.0f * Skala_liter, 356.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
		DrawText(TextFormat("Limit czasu: %0.2lf", zmienne->limit_czas), szer - 258.0f * Skala_liter, 378.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);

		float jasnosc_pom = 0.0f;

		if (!zmienne->pauza) {

			//JG:KONTUR PODPANELU
			DrawRectangle(57.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 79.0f * Skala_liter + wys_pom, 364.0f * Skala_liter, 76.0f * Skala_liter, BLACK);

			//JG:PRZYCISK ZATWIERDZ
			DrawRectangle(348.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 82.0f * Skala_liter + wys_pom, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
			jasnosc_pom = 0.0f;
			if (zmienne->LAB_czulosc_przycisku[8] == 0 && zmienne->mysz_x > 350.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 416.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom) {
				jasnosc_pom = -0.5f;
				SetMouseCursor(4);
				zmienne->kurosr_czulosc = 1;
				if (zmienne->ministan == 'q') {
					switch (zmienne->odp_zaznaczona) {
					default:
					case 'A':
						DrawText("Zatwierdz odpowiedz A", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
						break;
					case 'B':
						DrawText("Zatwierdz odpowiedz B", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
						break;
					case 'C':
						DrawText("Zatwierdz odpowiedz C", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
						break;
					case 'D':
						DrawText("Zatwierdz odpowiedz D", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
						break;
					}
				}
				else if (zmienne->ministan == 'd') DrawText("Kontynuuj", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
				else DrawText("Ukoncz i idz dalej", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
			}
			DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[22], zmienne->LAB_zaczep_dec_przycisku[23], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 350.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
			if (zmienne->ministan == 'q') {
				DrawTriangle({ 356.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 105.0f * Skala_liter + wys_pom }, { 380.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 145.0f * Skala_liter + wys_pom }, { 385.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 135.0f * Skala_liter + wys_pom }, napis_epizodu);
				DrawTriangle({ 411.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 90.0f * Skala_liter + wys_pom }, { 395.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 103.0f * Skala_liter + wys_pom }, { 385.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 135.0f * Skala_liter + wys_pom }, napis_epizodu);
				DrawTriangle({ 385.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 135.0f * Skala_liter + wys_pom }, { 395.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 103.0f * Skala_liter + wys_pom }, { 375.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 126.0f * Skala_liter + wys_pom }, napis_epizodu);
			}
			else {
				DrawTriangle({ 406.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 115.0f * Skala_liter + wys_pom }, { 364.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 89.0f * Skala_liter + wys_pom }, { 364.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 141.0f * Skala_liter + wys_pom }, napis_epizodu);
			}

			//JG:PRZYCISK ODPOWIEDZ A
			DrawRectangle(60.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 82.0f * Skala_liter + wys_pom, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
			jasnosc_pom = 0.0f;
			if (zmienne->odp_zaznaczona == 'A') {
				jasnosc_pom = -0.75f;
			}
			else if (zmienne->ministan == 'q' && zmienne->LAB_czulosc_przycisku[4] == 0 && zmienne->mysz_x > 62.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 128.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom) {
				jasnosc_pom = -0.5f;
				SetMouseCursor(4);
				zmienne->kurosr_czulosc = 1;
				DrawText("Wybierz odpowiedz A", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
			}
			DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[14], zmienne->LAB_zaczep_dec_przycisku[15], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 62.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
			DrawText("A", 74.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, (int)(70.0f * Skala_liter), napis_epizodu);

			//JG:PRZYCISK ODPOWIEDZ B
			DrawRectangle(132.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 82.0f * Skala_liter + wys_pom, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
			jasnosc_pom = 0.0f;
			if (zmienne->odp_zaznaczona == 'B') {
				jasnosc_pom = -0.75f;
			}
			else if (zmienne->ministan == 'q' && zmienne->LAB_czulosc_przycisku[5] == 0 && zmienne->mysz_x > 134.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 200.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom) {
				jasnosc_pom = -0.5f;
				SetMouseCursor(4);
				zmienne->kurosr_czulosc = 1;
				DrawText("Wybierz odpowiedz B", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
			}
			DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[16], zmienne->LAB_zaczep_dec_przycisku[17], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 134.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
			DrawText("B", 146.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, (int)(70.0f * Skala_liter), napis_epizodu);

			//JG:PRZYCISK ODPOWIEDZ C
			DrawRectangle(204.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 82.0f * Skala_liter + wys_pom, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
			jasnosc_pom = 0.0f;
			if (zmienne->odp_zaznaczona == 'C') {
				jasnosc_pom = -0.75f;
			}
			else if (zmienne->ministan == 'q' && zmienne->LAB_czulosc_przycisku[6] == 0 && zmienne->mysz_x > 206.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 272.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom) {
				jasnosc_pom = -0.5f;
				SetMouseCursor(4);
				zmienne->kurosr_czulosc = 1;
				DrawText("Wybierz odpowiedz C", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
			}
			DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[18], zmienne->LAB_zaczep_dec_przycisku[19], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 206.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
			DrawText("C", 218.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, (int)(70.0f * Skala_liter), napis_epizodu);

			//JG:PRZYCISK ODPOWIEDZ D
			DrawRectangle(276.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 82.0f * Skala_liter + wys_pom, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
			jasnosc_pom = 0.0f;
			if (zmienne->odp_zaznaczona == 'D') {
				jasnosc_pom = -0.75f;
			}
			else if (zmienne->ministan == 'q' && zmienne->LAB_czulosc_przycisku[7] == 0 && zmienne->mysz_x > 278.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 344.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom) {
				jasnosc_pom = -0.5f;
				SetMouseCursor(4);
				zmienne->kurosr_czulosc = 1;
				DrawText("Wybierz odpowiedz D", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
			}
			DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[20], zmienne->LAB_zaczep_dec_przycisku[21], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 278.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, 66.0f * Skala_liter, 66.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
			DrawText("D", 290.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f, 84.0f * Skala_liter + wys_pom, (int)(70.0f * Skala_liter), napis_epizodu);
		}
		else {
			DrawRectangle((szer - 272.0f * Skala_liter) * 0.5f - 80.0f * Skala_liter, wys * 0.5f - 30.0f * Skala_liter, 160.0f * Skala_liter, 60.0f * Skala_liter, Fade(szata_epizodu, 0.75f));
			DrawRectangle((szer - 272.0f * Skala_liter) * 0.5f - 81.0f * Skala_liter, wys * 0.5f - 31.0f * Skala_liter, 3.0f * Skala_liter, 62.0f * Skala_liter, BLACK);
			DrawRectangle((szer - 272.0f * Skala_liter) * 0.5f + 79.0f * Skala_liter, wys * 0.5f - 31.0f * Skala_liter, 3.0f * Skala_liter, 62.0f * Skala_liter, BLACK);
			DrawRectangle((szer - 272.0f * Skala_liter) * 0.5f - 81.0f * Skala_liter, wys * 0.5f + 29.0f * Skala_liter, 162.0f * Skala_liter, 3.0f * Skala_liter, BLACK);
			DrawRectangle((szer - 272.0f * Skala_liter) * 0.5f - 81.0f * Skala_liter, wys * 0.5f - 31.0f * Skala_liter, 162.0f * Skala_liter, 3.0f * Skala_liter, BLACK);
			DrawText("PAUZA", (szer - 272.0f * Skala_liter) * 0.5f - 67.0f * Skala_liter, wys * 0.5f - 17.0f * Skala_liter, (int)(40.0f * Skala_liter), napis_epizodu);
		}

		//JG:PRZYCISK PAUZA
		DrawRectangle(szer - 248.0f * Skala_liter, 410.0f * Skala_liter, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
		jasnosc_pom = 0.0f;
		if (zmienne->pauza_czulosc == 0 && zmienne->mysz_x > szer - 248.0f * Skala_liter && zmienne->mysz_x < szer - 178.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Pauza (zmienia pytanie!)", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
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

		//JG:PRZYCISK COFNIECIE DO LABIRYNTU
		DrawRectangle(szer - 78.0f * Skala_liter, 410.0f * Skala_liter, 70.0f * Skala_liter, 70.0f * Skala_liter, napis_epizodu);
		if (zmienne->cofniecia >= zmienne->limit_cofniecia) {
			jasnosc_pom = -0.75f;
		}
		else if (zmienne->LAB_czulosc_przycisku[1] == 0 && zmienne->mysz_x > szer - 76.0f * Skala_liter && zmienne->mysz_x < szer - 10.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
			DrawText("Poddaj sie/wroc", szer - 258.0f * Skala_liter, 490.0f * Skala_liter, (int)(18.0f * Skala_liter), napis_epizodu);
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


	void updateQuiz(grafika* tlo) {
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
		float szer_pom = szer - 392.0f * Skala_liter;
		float wys_pom = wys - 240.0f * Skala_liter;
		//JG:AKTUALIZACJA DANYCH KURSORA
		if (IsCursorOnScreen()) {
			zmienne->mysz_pop_x = zmienne->mysz_x;
			zmienne->mysz_pop_y = zmienne->mysz_y;
			zmienne->mysz_x = GetMouseX();
			zmienne->mysz_y = GetMouseY();
		}
		//JG:AKTUALIZACJA CZASU
		if (!zmienne->pauza) {
			zmienne->czas = zmienne->czas + 0.01;
		}

		//JG:PRZYCISK ODPOWIEDZ A
		if (!zmienne->pauza && zmienne->ministan == 'q') {
			if (zmienne->LAB_czulosc_przycisku[4] > 0) {
				zmienne->LAB_czulosc_przycisku[4] = zmienne->LAB_czulosc_przycisku[4] - 1;
			}
			else if (zmienne->LAB_czulosc_przycisku[4] != 0) {
				zmienne->LAB_czulosc_przycisku[4] = 0;
			}
			else if ((zmienne->odp_zaznaczona != 'A') && ((IsKeyDown(KEY_A) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 62.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 128.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom)))) {
				zmienne->odp_zaznaczona = 'A';
				zmienne->LAB_czulosc_przycisku[4] = 25;
				SetMouseCursor(1);
				zmienne->kurosr_czulosc = 0;
			}
		}

		//JG:PRZYCISK ODPOWIEDZ B
		if (!zmienne->pauza && zmienne->ministan == 'q') {
			if (zmienne->LAB_czulosc_przycisku[5] > 0) {
				zmienne->LAB_czulosc_przycisku[5] = zmienne->LAB_czulosc_przycisku[5] - 1;
			}
			else if (zmienne->LAB_czulosc_przycisku[5] != 0) {
				zmienne->LAB_czulosc_przycisku[5] = 0;
			}
			else if ((zmienne->odp_zaznaczona != 'B') && ((IsKeyDown(KEY_W) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 134.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 200.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom)))) {
				zmienne->odp_zaznaczona = 'B';
				zmienne->LAB_czulosc_przycisku[5] = 25;
				SetMouseCursor(1);
				zmienne->kurosr_czulosc = 0;
			}
		}

		//JG:PRZYCISK ODPOWIEDZ C
		if (!zmienne->pauza && zmienne->ministan == 'q') {
			if (zmienne->LAB_czulosc_przycisku[6] > 0) {
				zmienne->LAB_czulosc_przycisku[6] = zmienne->LAB_czulosc_przycisku[6] - 1;
			}
			else if (zmienne->LAB_czulosc_przycisku[6] != 0) {
				zmienne->LAB_czulosc_przycisku[6] = 0;
			}
			else if ((zmienne->odp_zaznaczona != 'C') && ((IsKeyDown(KEY_S) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 206.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 272.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom)))) {
				zmienne->odp_zaznaczona = 'C';
				zmienne->LAB_czulosc_przycisku[6] = 25;
				SetMouseCursor(1);
				zmienne->kurosr_czulosc = 0;
			}
		}

		//JG:PRZYCISK ODPOWIEDZ D
		if (!zmienne->pauza && zmienne->ministan == 'q') {
			if (zmienne->LAB_czulosc_przycisku[7] > 0) {
				zmienne->LAB_czulosc_przycisku[7] = zmienne->LAB_czulosc_przycisku[7] - 1;
			}
			else if (zmienne->LAB_czulosc_przycisku[7] != 0) {
				zmienne->LAB_czulosc_przycisku[7] = 0;
			}
			else if ((zmienne->odp_zaznaczona != 'D') && ((IsKeyDown(KEY_D) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 278.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 344.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom)))) {
				zmienne->odp_zaznaczona = 'D';
				zmienne->LAB_czulosc_przycisku[7] = 25;
				SetMouseCursor(1);
				zmienne->kurosr_czulosc = 0;
			}
		}

		//JG:PRZYCISK ZATWIERDZ
		if (!zmienne->pauza) {
			if (zmienne->LAB_czulosc_przycisku[8] > 0) {
				zmienne->LAB_czulosc_przycisku[8] = zmienne->LAB_czulosc_przycisku[8] - 1;
			}
			else if (zmienne->LAB_czulosc_przycisku[8] != 0) {
				zmienne->LAB_czulosc_przycisku[8] = 0;
			}
			else if (((IsKeyDown(KEY_R) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 278.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x > 350.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_x < 416.0f * Skala_liter + (szer_pom - 358.0f * Skala_liter) * 0.5f && zmienne->mysz_y > 84.0f * Skala_liter + wys_pom && zmienne->mysz_y < 150.0f * Skala_liter + wys_pom)))) {
				if (zmienne->ministan == 'q' && zmienne->proba <= zmienne->proba_max && zmienne->punkty < zmienne->punkty_wymagane) { 
					zmienne->punkty = zmienne->punkty + zmienne->punkty_odpowiedzi[int(zmienne->odp_zaznaczona - 'A')];
					zmienne->wynik = zmienne->wynik - 0.75 + zmienne->punkty_odpowiedzi[int(zmienne->odp_zaznaczona - 'A')];//JG:PREMIA DO WYNIKU ZA POPRAWNE ODPOWIEDZI (I MALA KARA ZA NIEPOPRAWNE)
					if (zmienne->punkty > zmienne->punkty_wymagane - TOL || zmienne->proba >= zmienne->proba_max) zmienne->ministan = 'u';
					else zmienne->ministan = 'd';
				}
				else if (zmienne->ministan == 'd') {
					zmienne->ministan = 'q';
					if (zmienne->proba < zmienne->proba_max)
					{
						zmienne->proba = zmienne->proba + 1;
						std::cout << '\n' << zmienne->punkty_odpowiedzi[0] << '\n';
						std::cout << zmienne->punkty_odpowiedzi[1] << '\n';
						std::cout << zmienne->punkty_odpowiedzi[2] << '\n';
						std::cout << zmienne->punkty_odpowiedzi[3] << '\n';
						getdata();
					}
					else {
						switch (zmienne->wyzwanie) {
						default:
						case 'b':
							break;
						case 's':
							if (zmienne->punkty > zmienne->punkty_straznik - TOL) break;
						case 'p':
							zmienne->cofniecia = zmienne->cofniecia + 1;
							zmienne->wynik = zmienne->kontrola_wynik;
							zmienne->czas = zmienne->kontrola_czas;
							break;
						}
						stanGry = GRA_LABIRYNT;
						zmienne->pauza = true;
					}
				}
				else {//jak ministan rowny 'u'

					if (zmienne->punkty > zmienne->punkty_wymagane - TOL) {//JG:ZWYCIESTWO W QUIZIE

						if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'l') {
							zmienne->biezacy_labirynt = zmienne->biezacy_labirynt + 1;
						}
						else if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'q') {//JG:Przy nastepnym quizie wezmie jego parametry z tablicy quizow zamiast obecnuch
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

							if (zmienne->L_zmienne_pomocnicze != NULL) delete[] zmienne->L_zmienne_pomocnicze;
							zmienne->L_zmienne_pomocnicze = new char[zmienne->L_zmienne_pomocnicze_N[zmienne->biezacy_labirynt]];
							for (int i = 0; i < zmienne->L_zmienne_pomocnicze_N[zmienne->biezacy_labirynt]; i++) {
								zmienne->L_zmienne_pomocnicze[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].zmienne_pomocnicze[i];
							}

							stanGry = GRA_LABIRYNT;
							zmienne->pauza = true;

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
					else {//PORAZKA
						
						zmienne->wynik = zmienne->wynik - zmienne->punkty;//JG:zapobiega "farmieniu" punktow na bezpiecznych quizach
						switch (zmienne->wyzwanie) {
						default:
						case 'b'://JG:WYZWANIE:BEZPIECZNY:COFA NA POCZATEK QUIZU
							zmienne->punkty = 0.0;
							zmienne->proba = 1;
							getdata();
							zmienne->ministan = 'q';
							break;
						case 's'://JG:WYZWANIE:STRAZNIK:COFA NA POCZATEK QUIZU PRZY ZEBRANIU WYSTARCZAJACEJ LICZBY PUNKTOW. INACZEJ COFA DO PUNKTU KONTROLNEGO W OSTATNIM LABIRYNCIE
							if (zmienne->punkty > zmienne->punkty_straznik - TOL){
								zmienne->punkty = 0.0;
								zmienne->proba = 1;
								getdata();
								zmienne->ministan = 'q';
								break;
							}
						case 'p'://JG:WYZWANIE:PULAPKA:COFA DO PUNKTU KONTROLNEGO W OSTATNIM LABIRYNCIE
							if (zmienne->cofniecia < zmienne->limit_cofniecia) {//JG:Powrot do punktu kontrolnego
								zmienne->cofniecia = zmienne->cofniecia + 1;
								zmienne->wynik = zmienne->kontrola_wynik;
								zmienne->czas = zmienne->kontrola_czas;
								zmienne->pauza = true;
								zmienne->LAB_czulosc_przycisku[1] = 25;
								zmienne->plansza_x = 0.0f;
								zmienne->plansza_y = 0.0f;
								while (zmienne->poziomik.etapy[zmienne->biezacy_etap] != 'l') {
									zmienne->biezacy_etap = zmienne->biezacy_etap - 1;
									if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'l') {
										zmienne->biezacy_labirynt = zmienne->biezacy_labirynt - 1;
									}
									else if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'q') {
										zmienne->biezacy_quiz = zmienne->biezacy_quiz - 1;
									}
								}

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

								if (zmienne->L_zmienne_pomocnicze != NULL) delete[] zmienne->L_zmienne_pomocnicze;
								zmienne->L_zmienne_pomocnicze = new char[zmienne->L_zmienne_pomocnicze_N[zmienne->biezacy_labirynt]];
								for (int i = 0; i < zmienne->L_zmienne_pomocnicze_N[zmienne->biezacy_labirynt]; i++) {
									zmienne->L_zmienne_pomocnicze[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].zmienne_pomocnicze[i];
								}

								stanGry = GRA_LABIRYNT;
							}
							else {//JG:Porazka (wyczerpanie cofniec)
								zmienne->ministan = 'p';
								stanGry = PODSUMOWANIE;
								zmienne->LAB_czulosc_przycisku[0] = 25;
								SetMouseCursor(1);
								zmienne->kurosr_czulosc = 0;
							}
							break;
						}
					
					}

				}
				zmienne->LAB_czulosc_przycisku[8] = 50;
				SetMouseCursor(1);
				zmienne->kurosr_czulosc = 0;
			}
		}

		//JG:PRZYCISK PAUZA
		if (zmienne->pauza_czulosc > 0) {
			zmienne->pauza_czulosc = zmienne->pauza_czulosc - 1;
		}
		else if (zmienne->pauza_czulosc != 0) {
			zmienne->pauza_czulosc = 0;
		}
		else if (IsKeyDown(KEY_Q) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > szer - 248.0f * Skala_liter && zmienne->mysz_x < szer - 178.0f * Skala_liter && zmienne->mysz_y > 410.0f * Skala_liter && zmienne->mysz_y < 480.0f * Skala_liter)) {
			zmienne->pauza = !zmienne->pauza;
			if (zmienne->pauza) zmienne->ministan = 'q';
			else getdata();
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
			zmienne->wynik = zmienne->wynik - zmienne->punkty;//JG:zapobiega "farmieniu" punktow na bezpiecznych quizach
			zmienne->wynik = zmienne->wynik - 1.0;//JG:zapobiega wybieraniu pierwszego pytania w bezpiecznym quizie 

			switch (zmienne->wyzwanie) {
			default:
			case 'b':
				zmienne->punkty = 0.0;
				zmienne->proba = 1;
				getdata();
				zmienne->ministan = 'q';
				break;
			case 's':
				if (zmienne->punkty > zmienne->punkty_straznik - TOL) {
					zmienne->punkty = 0.0;
					zmienne->proba = 1;
					getdata();
					zmienne->ministan = 'q';
					break;
				}
			case 'p':
				zmienne->plansza_x = 0.0f;
				zmienne->plansza_y = 0.0f;
				zmienne->cofniecia = zmienne->cofniecia + 1;
				zmienne->wynik = zmienne->kontrola_wynik;
				zmienne->czas = zmienne->kontrola_czas;
				while (zmienne->poziomik.etapy[zmienne->biezacy_etap] != 'l') {
					zmienne->biezacy_etap = zmienne->biezacy_etap - 1;
					if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'l') {
						zmienne->biezacy_labirynt = zmienne->biezacy_labirynt - 1;
					}
					else if (zmienne->poziomik.etapy[zmienne->biezacy_etap] == 'q') {
						zmienne->biezacy_quiz = zmienne->biezacy_quiz - 1;
					}
				}

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

				if (zmienne->L_zmienne_pomocnicze != NULL) delete[] zmienne->L_zmienne_pomocnicze;
				zmienne->L_zmienne_pomocnicze = new char[zmienne->L_zmienne_pomocnicze_N[zmienne->biezacy_labirynt]];
				for (int i = 0; i < zmienne->L_zmienne_pomocnicze_N[zmienne->biezacy_labirynt]; i++) {
					zmienne->L_zmienne_pomocnicze[i] = zmienne->poziomik.labirynty[zmienne->biezacy_labirynt].zmienne_pomocnicze[i];
				}

				stanGry = GRA_LABIRYNT;
				zmienne->pauza = true;
				break;
			}
			zmienne->LAB_czulosc_przycisku[1] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
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
	}
}