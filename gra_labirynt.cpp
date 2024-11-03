#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "Grafika.h"
#include "gamestate.h"
#include "przycisk.h"
#include <string>

namespace labirynt {
	

	// Rysowanie
	void drawLabirynt(GRAFIKI* grafiki, PakietZmiennych* zmienne) {
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

		DrawText(zmienne->uzytkownik, szer - 258.0f * Skala_liter, 13.5f * Skala_liter, (int)(26.0f * Skala_liter), napis_epizodu);//JG:wyswietla biezacego gracza
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
		DrawTexturePro(grafiki->pole1.text, {zmienne->LAB_zaczep_dec_przycisku[0], zmienne->LAB_zaczep_dec_przycisku[1], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f}, {szer - 246.0f * Skala_liter, 412.0f * Skala_liter, 66.0f * Skala_liter, 66.0f * Skala_liter}, {0.0f, 0.0f}, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
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
		DrawLineEx({szer - 257.0f * Skala_liter, 516.0f * Skala_liter}, { szer - 229.0f * Skala_liter, 544.0f * Skala_liter}, 1.5f * Skala_liter, ColorBrightness(napis_epizodu, -0.3f));
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


	void updateLabirynt(PakietZmiennych* zmienne, grafika* tlo) {
		
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
		
		/*for (auto& B : Buttons) {
			B.update();
		}*/
	}


}