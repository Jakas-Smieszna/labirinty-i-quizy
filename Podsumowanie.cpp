#include "Podsumowanie.h"
#include "gamestate.h"
#include "przycisk.h"
#include "funkcjePomocnicze.h"

namespace podsumowanie {
	/*_Przycisk* Buttons[] = {
		new PrzyciskTekst("Wroc do Menu",{0, 1, 0.1, -1.3}, 30, [&] {stanGry = StanEkranu::MAIN_MENU;
		if (!(zmienne->wynik < zmienne->rekord_wlasny + TOL)) zmienne->rekord_wlasny = zmienne->wynik;
		if (!(zmienne->wynik < zmienne->rekord_lokalny + TOL)) zmienne->rekord_lokalny = zmienne->wynik;
		if (!(zmienne->wynik < zmienne->rekord_swiata + TOL)) zmienne->rekord_swiata = zmienne->wynik;
			}) 
	};*/

	void drawPodsumowanie() {

		if (zmienne->kurosr_czulosc == 0) SetMouseCursor(1);
		else if (zmienne->kurosr_czulosc > 0) zmienne->kurosr_czulosc = zmienne->kurosr_czulosc - 1;
		else zmienne->kurosr_czulosc = 0;

		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		float Skala_liter = 1.f;

		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = (float)GetScreenHeight() / OknoWysBaz;
		}
		else {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = (float)GetScreenWidth() / OknoSzerBaz;
		}
		if (700.0f * Skala_liter > wys) Skala_liter = Skala_liter = wys / OknoWysBaz;//JG: przy wyjatkowo wrednym skalowaniu okna bez tego zabezpieczenia zawartosc moze "rozszerzyc" sie poza okno. Dotyczy duzych paneli

		float szer_pom = 880.0f * Skala_liter;
		float wys_pom = 620.0f * Skala_liter;
		char* napis_pom = NULL;
		if (zmienne->ministan == 'z') {
			napis_pom = "POZIOM UKONCZONY";
		}
		else if (zmienne->ministan == 'p') {
			napis_pom = "POZIOM NIEUKONCZONY";
		}
		else {
			napis_pom = "BLAD W KODZIE";
		}
		
		DrawRectangle(0.5f * (szer - szer_pom) , 0.5f * (wys - wys_pom), szer_pom, wys_pom, Fade(EpisodeTheme.bgColor, 0.75f));
		DrawRectangle(0.5f * (szer - szer_pom) - 1.0f * Skala_liter, 0.5f * (wys - wys_pom) - 1.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
		DrawRectangle(0.5f * (szer + szer_pom) - 1.0f * Skala_liter, 0.5f * (wys - wys_pom) - 1.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
		DrawRectangle(0.5f * (szer - szer_pom) - 1.0f * Skala_liter, 0.5f * (wys + wys_pom) - 1.0f * Skala_liter, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);
		DrawRectangle(0.5f * (szer - szer_pom) - 1.0f * Skala_liter, 0.5f * (wys - wys_pom) - 1.0f * Skala_liter, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);

		helper::DrawTextCentered(napis_pom, 0.5f * szer + 5.0f * Skala_liter, 0.5f * (wys - wys_pom) + 15.0f * Skala_liter, 50.0f * Skala_liter, BLACK);//JG 'cien'
		helper::DrawTextCentered(napis_pom, 0.5f * szer, 0.5f * (wys - wys_pom) + 10.0f * Skala_liter, 50.0f * Skala_liter, EpisodeTheme.textColor);

		DrawText(("Gracz: " + zmienne->nazwa_uzytkownika).c_str(), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 93.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
		DrawText(("Gracz: " + zmienne->nazwa_uzytkownika).c_str(), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 90.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla biezacego gracza
		DrawText(TextFormat("Epizod: %d", zmienne->epizod), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 133.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
		DrawText(TextFormat("Epizod: %d", zmienne->epizod), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 130.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla biezacy epizod
		DrawText(TextFormat("Poziom: %d", zmienne->poziom), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 173.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
		DrawText(TextFormat("Poziom: %d", zmienne->poziom), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 170.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla biezacy poziom

		char* trudnosc_napis = "";
		//MG: nie by³oby najwydajniej u¿yæ mapy?
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
		DrawText(trudnosc_napis, 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 213.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
		DrawText(trudnosc_napis, 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 210.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla biezacy poziom trudnosci
		DrawText(TextFormat("Czas przechodzenia: %0.2lfs/%0.2lfs", zmienne->czas, zmienne->limit_czas), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 253.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
		DrawText(TextFormat("Czas przechodzenia: %0.2lfs/%0.2lfs", zmienne->czas, zmienne->limit_czas), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 250.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla biezacy czas
		DrawText(TextFormat("Cofniecia: %d/%d", zmienne->cofniecia, zmienne->limit_cofniecia), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 293.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
		DrawText(TextFormat("Cofniecia: %d/%d", zmienne->cofniecia, zmienne->limit_cofniecia), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 290.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:Liczba wykorzystanych cofniec na limit

		//JG:brak rekordow - TAK. Jakis rekord - else
		if (zmienne->wynik < zmienne->rekord_wlasny + TOL && zmienne->wynik < zmienne->rekord_lokalny + TOL && zmienne->wynik < zmienne->rekord_swiata + TOL) {
			DrawText(TextFormat("Wynik: %0.2lf", zmienne->wynik), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 333.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
			DrawText(TextFormat("Wynik: %0.2lf", zmienne->wynik), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 330.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla obecny wynik biezacego gracza
			DrawText(TextFormat("Twoj rekord: %0.2lf", zmienne->rekord_wlasny), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 373.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
			DrawText(TextFormat("Twoj rekord: %0.2lf", zmienne->rekord_wlasny), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 370.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik biezacego gracza
			DrawText(TextFormat("Rekord lokalny: %0.2lf", zmienne->rekord_lokalny), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 413.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
			DrawText(TextFormat("Rekord lokalny: %0.2lf", zmienne->rekord_lokalny), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 410.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik w tej aplikacji
			DrawText(TextFormat("Rekord swiata: %0.2lf", zmienne->rekord_swiata), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 453.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
			DrawText(TextFormat("Rekord swiata: %0.2lf", zmienne->rekord_swiata), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 450.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik dla tego poziomu na swiecie
		}
		else {
			DrawText(TextFormat("Wynik: %0.2lf   (NOWY REKORD!)", zmienne->wynik), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 333.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
			DrawText(TextFormat("Wynik: %0.2lf   (NOWY REKORD!)", zmienne->wynik), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 330.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla obecny wynik biezacego gracza
			
			if (zmienne->wynik < zmienne->rekord_wlasny + TOL) {//JG:jak nie pobito
				DrawText(TextFormat("Twoj rekord: %0.2lf", zmienne->rekord_wlasny), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 373.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
				DrawText(TextFormat("Twoj rekord: %0.2lf", zmienne->rekord_wlasny), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 370.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik biezacego gracza
			}
			else {//JG:jak pobito
				DrawText(TextFormat("Twoj rekord: %0.2lf   (poprzedni: %0.2lf)", zmienne->wynik, zmienne->rekord_wlasny), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 373.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
				DrawText(TextFormat("Twoj rekord: %0.2lf   (poprzedni: %0.2lf)", zmienne->wynik, zmienne->rekord_wlasny), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 370.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik biezacego gracza
			}

			if (zmienne->wynik < zmienne->rekord_lokalny + TOL) {//JG:jak nie pobito
			DrawText(TextFormat("Rekord lokalny: %0.2lf", zmienne->rekord_lokalny), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 413.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
			DrawText(TextFormat("Rekord lokalny: %0.2lf", zmienne->rekord_lokalny), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 410.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik w tej aplikacji
			}
			else {//JG:jak pobito
				DrawText(TextFormat("Rekord lokalny: %0.2lf   (poprzedni: %0.2lf)", zmienne->wynik, zmienne->rekord_lokalny), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 413.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
				DrawText(TextFormat("Rekord lokalny: %0.2lf   (poprzedni: %0.2lf)", zmienne->wynik, zmienne->rekord_lokalny), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 410.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik w tej aplikacji
			}

			if (zmienne->wynik < zmienne->rekord_swiata + TOL) {//JG:jak nie pobito
			DrawText(TextFormat("Rekord swiata: %0.2lf", zmienne->rekord_swiata), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 453.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
			DrawText(TextFormat("Rekord swiata: %0.2lf", zmienne->rekord_swiata), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 450.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik dla tego poziomu na swiecie
			}
			else {//JG:jak pobito
				DrawText(TextFormat("Rekord swiata: %0.2lf   (poprzedni: %0.2lf)", zmienne->wynik, zmienne->rekord_swiata), 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 453.0f * Skala_liter, (int)(36.0f * Skala_liter), BLACK);//JG:cien
				DrawText(TextFormat("Rekord swiata: %0.2lf   (poprzedni: %0.2lf)", zmienne->wynik, zmienne->rekord_swiata), 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 450.0f * Skala_liter, (int)(36.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla najlepszy wynik dla tego poziomu na swiecie
			}

			DrawText("Wybierz jeden z ponizszych przyciskow by zapisac rekordy.", 0.5f * (szer - szer_pom) + 53.0f * Skala_liter, 0.5f * (wys - wys_pom) + 503.0f * Skala_liter, (int)(26.0f * Skala_liter), BLACK);//JG:cien
			DrawText("Wybierz jeden z ponizszych przyciskow by zapisac rekordy.", 0.5f * (szer - szer_pom) + 50.0f * Skala_liter, 0.5f * (wys - wys_pom) + 500.0f * Skala_liter, (int)(26.0f * Skala_liter), EpisodeTheme.textColor);//JG:wyswietla komunikat o tym jak zapisac rekord

		}

		//JG:PANEL PRZYCISKOW
		DrawRectangle(18.0f * Skala_liter + 0.5f * (szer - szer_pom), -32.0f * Skala_liter + 0.5f * (wys + wys_pom), szer_pom - 36.0f * Skala_liter, 64.0f * Skala_liter, BLACK);//JG:kontur przyciskow

		//JG:PRZYCISK WROC DO MENU
		DrawRectangle(20.0f * Skala_liter + 0.5f * (szer - szer_pom), -30.0f * Skala_liter + 0.5f * (wys + wys_pom), 279.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
		float jasnosc_pom = 0.0f;
		if (zmienne->LAB_czulosc_przycisku[9] == 0 && zmienne->mysz_x > 20.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 299.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
		}
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[24], zmienne->LAB_zaczep_dec_przycisku[25], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 22.0f * Skala_liter + 0.5f * (szer - szer_pom), -28.0f * Skala_liter + 0.5f * (wys + wys_pom), 275.0f * Skala_liter, 56.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawText("Wroc do Menu", 72.0f * Skala_liter + 0.5f * (szer - szer_pom), -12.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(26.0f * Skala_liter), BLACK);//JG:cien napisu przycisku
		DrawText("Wroc do Menu", 70.0f * Skala_liter + 0.5f * (szer - szer_pom), -14.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(26.0f * Skala_liter), EpisodeTheme.textColor);//JG:napis przycisku


		//JG:PRZYCISK ROZEGRAJ PONOWNIE
		DrawRectangle(301.0f * Skala_liter + 0.5f * (szer - szer_pom), -30.0f * Skala_liter + 0.5f * (wys + wys_pom), 278.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
		jasnosc_pom = 0.0f;
		if (zmienne->LAB_czulosc_przycisku[10] == 0 && zmienne->mysz_x > 301.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 579.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
		}
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[26], zmienne->LAB_zaczep_dec_przycisku[27], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 303.0f * Skala_liter + 0.5f * (szer - szer_pom), -28.0f * Skala_liter + 0.5f * (wys + wys_pom), 274.0f * Skala_liter, 56.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawText("Rozegraj ponownie", 324.0f * Skala_liter + 0.5f * (szer - szer_pom), -12.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(26.0f * Skala_liter), BLACK);//JG:cien napisu przycisku
		DrawText("Rozegraj ponownie", 322.0f * Skala_liter + 0.5f * (szer - szer_pom), -14.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(26.0f * Skala_liter), EpisodeTheme.textColor);//JG:napis przycisku


		//JG:PRZYCISK NASTEPNY POZIOM
		DrawRectangle(581.0f * Skala_liter + 0.5f * (szer - szer_pom), -30.0f * Skala_liter + 0.5f * (wys + wys_pom), 279.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
		jasnosc_pom = 0.0f;
		if ( (zmienne->poziom == 5 && zmienne->epizod == 4) || zmienne->ministan == 'p') {//JG: bedzie uzyte gdy pojawi sie system odbokowan poziomow
			jasnosc_pom = -0.75f;
		}
		else if (zmienne->LAB_czulosc_przycisku[11] == 0 && zmienne->mysz_x > 581.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 860.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
		}
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[28], zmienne->LAB_zaczep_dec_przycisku[29], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 583.0f * Skala_liter + 0.5f * (szer - szer_pom), -28.0f * Skala_liter + 0.5f * (wys + wys_pom), 275.0f * Skala_liter, 56.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawText("Nastepny poziom", 624.0f * Skala_liter + 0.5f * (szer - szer_pom), -12.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(26.0f * Skala_liter), BLACK);//JG:cien napisu przycisku
		DrawText("Nastepny poziom", 622.0f * Skala_liter + 0.5f * (szer - szer_pom), -14.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(26.0f * Skala_liter), EpisodeTheme.textColor);//JG:napis przycisku




		/*for (auto& b : Buttons) {
			b->draw();
		}*/

	}
	void updatePodsumowanie(grafika* tlo) {

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
		if (700.0f * Skala_liter > wys) Skala_liter = Skala_liter = wys / OknoWysBaz;//JG: przy wyjatkowo wrednym skalowaniu okna bez tego zabezpieczenia zawartosc moze "rozszerzyc" sie poza okno. Dotyczy duzych paneli

		float szer_pom = 880.0f * Skala_liter;
		float wys_pom = 620.0f * Skala_liter;

		//JG:AKTUALIZACJA DANYCH KURSORA
		if (IsCursorOnScreen()) {
			zmienne->mysz_pop_x = zmienne->mysz_x;
			zmienne->mysz_pop_y = zmienne->mysz_y;
			zmienne->mysz_x = GetMouseX();
			zmienne->mysz_y = GetMouseY();
		}

		//JG:PRZYCISK >> WROC DO MENU
		if (zmienne->LAB_czulosc_przycisku[9] > 0) {
			zmienne->LAB_czulosc_przycisku[9] = zmienne->LAB_czulosc_przycisku[9] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[9] != 0) {
			zmienne->LAB_czulosc_przycisku[9] = 0;
		}
		else if ((IsKeyDown(KEY_P) && (IsKeyDown(KEY_O))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 20.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 299.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom))) {
			
			if (!(zmienne->wynik < zmienne->rekord_wlasny + TOL)) zmienne->rekord_wlasny = zmienne->wynik;
			if (!(zmienne->wynik < zmienne->rekord_lokalny + TOL)) zmienne->rekord_lokalny = zmienne->wynik;
			if (!(zmienne->wynik < zmienne->rekord_swiata + TOL)) zmienne->rekord_swiata = zmienne->wynik;

			stanGry = MAIN_MENU;
			zmienne->LAB_czulosc_przycisku[9] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}

		//JG:PRZYCISK >> ROZEGRAJ PONOWNIE
		if (zmienne->LAB_czulosc_przycisku[10] > 0) {
			zmienne->LAB_czulosc_przycisku[10] = zmienne->LAB_czulosc_przycisku[10] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[10] != 0) {
			zmienne->LAB_czulosc_przycisku[10] = 0;
		}
		else if ((IsKeyDown(KEY_L) && (IsKeyDown(KEY_K))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 301.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 579.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom))) {

			if (!(zmienne->wynik < zmienne->rekord_wlasny + TOL)) zmienne->rekord_wlasny = zmienne->wynik;
			if (!(zmienne->wynik < zmienne->rekord_lokalny + TOL)) zmienne->rekord_lokalny = zmienne->wynik;
			if (!(zmienne->wynik < zmienne->rekord_swiata + TOL)) zmienne->rekord_swiata = zmienne->wynik;

			zmienne->plansza_x = 0.0f;//JG:zerowanie zmiennych pod rozegranie poziomu
			zmienne->plansza_y = 0.0f;
			zmienne->punkty = 0.0;
			zmienne->biezacy_etap = 0;
			zmienne->cofniecia = 0;
			zmienne->czas = 0.0;
			zmienne->biezacy_labirynt = 0;
			zmienne->biezacy_quiz = 0;
			zmienne->kontrola_czas = 0.0;
			zmienne->proba = 1;
			zmienne->wynik = 100.0;//JG:STARTOWY WYNIK NA POZIOMIE (balansuje dodatkowe punkty zdobyte w trakcie i premie na koniec
			zmienne->kontrola_wynik = zmienne->wynik;
			zmienne->opoznienie = 0;

			if (zmienne->L_widzialnosc != NULL) delete[] zmienne->L_widzialnosc;
			zmienne->L_widzialnosc = new int[zmienne->L_widzialnosc_N[0]];
			for (int i = 0; i < zmienne->L_widzialnosc_N[0]; i++) {
				zmienne->L_widzialnosc[i] = zmienne->poziomik.labirynty[0].widzialnosc[i];
			}

			if (zmienne->L_etapy_znikania != NULL) delete[] zmienne->L_etapy_znikania;
			zmienne->L_etapy_znikania = new char[zmienne->L_etapy_znikania_N[0]];
			for (int i = 0; i < zmienne->L_etapy_znikania_N[0]; i++) {
				zmienne->L_etapy_znikania[i] = zmienne->poziomik.labirynty[0].etapy_znikania[i];
			}

			if (zmienne->L_zmienne_pomocnicze != NULL) delete[] zmienne->L_zmienne_pomocnicze;
			zmienne->L_zmienne_pomocnicze = new char[zmienne->L_zmienne_pomocnicze_N[0]];
			for (int i = 0; i < zmienne->L_zmienne_pomocnicze_N[0]; i++) {
				zmienne->L_zmienne_pomocnicze[i] = zmienne->poziomik.labirynty[0].zmienne_pomocnicze[i];
			}

			for (int i = 0; i < zmienne->L_wiatraki_N[0]; i++) {
				zmienne->poziomik.labirynty[0].wiatraki[i].rotacja = 0;
			}

			for (int i = 0; i < zmienne->L_wiatraki_przyspieszane_N[0]; i++) {
				zmienne->poziomik.labirynty[0].etapy_wiatraki[i] = -301;
			}

			zmienne->pauza = true;
			if (zmienne->poziomik.etapy[0] == 'l') {//JG:ustawia stan gry zaleznie od pierwszego etapu poziomu
				stanGry = StanEkranu::GRA_LABIRYNT;

			}
			else if (zmienne->poziomik.etapy[0] == 'q') {
				zmienne->odp_zaznaczona = 'A';
				zmienne->ministan = 'q';
				zmienne->proba_max = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_proby;
				zmienne->punkty_wymagane = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_prog_punktowy;
				zmienne->punkty_straznik = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_prog_bezpieczenstwa;
				zmienne->wyzwanie = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_wyzwanie;
				stanGry = StanEkranu::GRA_QUIZ;
			}

			zmienne->LAB_czulosc_przycisku[10] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}



		//JG:PRZYCISK >> NASTEPNY POZIOM
		if (zmienne->LAB_czulosc_przycisku[11] > 0) {
			zmienne->LAB_czulosc_przycisku[11] = zmienne->LAB_czulosc_przycisku[10] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[11] != 0) {
			zmienne->LAB_czulosc_przycisku[11] = 0;
		}
		else if ( !(zmienne->poziom == 5 && zmienne->epizod == 4) && zmienne->ministan != 'p' && ((IsKeyDown(KEY_M) && (IsKeyDown(KEY_N))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 581.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 860.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)))) {

			if (!(zmienne->wynik < zmienne->rekord_wlasny + TOL)) zmienne->rekord_wlasny = zmienne->wynik;
			if (!(zmienne->wynik < zmienne->rekord_lokalny + TOL)) zmienne->rekord_lokalny = zmienne->wynik;
			if (!(zmienne->wynik < zmienne->rekord_swiata + TOL)) zmienne->rekord_swiata = zmienne->wynik;

			if (zmienne->poziom < 5) {
				zmienne->poziom = zmienne->poziom + 1;
				zmienne->poziom_doc = zmienne->poziom_doc + 1;
			}
			else {
				zmienne->poziom = 1;
				zmienne->poziom_doc = 1;
				if (zmienne->epizod < 4) {
					zmienne->epizod = zmienne->epizod + 1;
					zmienne->epizod = zmienne->epizod_doc;
					grafiki->aktualizuj_tlo(zmienne->epizod);
					EpisodeTheme.Update(zmienne->epizod);
					zmienne->epizod_doc = zmienne->epizod_doc + 1;
				}
				else {
					zmienne->epizod = 1;
					zmienne->epizod = zmienne->epizod_doc;
					grafiki->aktualizuj_tlo(zmienne->epizod);
					EpisodeTheme.Update(zmienne->epizod);
					zmienne->epizod_doc = 1;
				}
			}

			zmienne->plansza_x = 0.0f;//JG:zerowanie zmiennych pod rozegranie poziomu
			zmienne->plansza_y = 0.0f;
			zmienne->punkty = 0.0;
			zmienne->biezacy_etap = 0;
			zmienne->cofniecia = 0;
			zmienne->czas = 0.0;
			zmienne->biezacy_labirynt = 0;
			zmienne->biezacy_quiz = 0;
			zmienne->kontrola_czas = 0.0;
			zmienne->proba = 1;
			zmienne->wynik = 100.0;//JG:STARTOWY WYNIK NA POZIOMIE (balansuje dodatkowe punkty zdobyte w trakcie i premie na koniec
			zmienne->kontrola_wynik = zmienne->wynik;
			zmienne->opoznienie = 0;

			if (zmienne->L_widzialnosc != NULL) delete[] zmienne->L_widzialnosc;
			zmienne->L_widzialnosc = new int[zmienne->L_widzialnosc_N[0]];
			for (int i = 0; i < zmienne->L_widzialnosc_N[0]; i++) {
				zmienne->L_widzialnosc[i] = zmienne->poziomik.labirynty[0].widzialnosc[i];
			}

			if (zmienne->L_etapy_znikania != NULL) delete[] zmienne->L_etapy_znikania;
			zmienne->L_etapy_znikania = new char[zmienne->L_etapy_znikania_N[0]];
			for (int i = 0; i < zmienne->L_etapy_znikania_N[0]; i++) {
				zmienne->L_etapy_znikania[i] = zmienne->poziomik.labirynty[0].etapy_znikania[i];
			}

			if (zmienne->L_zmienne_pomocnicze != NULL) delete[] zmienne->L_zmienne_pomocnicze;
			zmienne->L_zmienne_pomocnicze = new char[zmienne->L_zmienne_pomocnicze_N[0]];
			for (int i = 0; i < zmienne->L_zmienne_pomocnicze_N[0]; i++) {
				zmienne->L_zmienne_pomocnicze[i] = zmienne->poziomik.labirynty[0].zmienne_pomocnicze[i];
			}

			for (int i = 0; i < zmienne->L_wiatraki_N[0]; i++) {
				zmienne->poziomik.labirynty[0].wiatraki[i].rotacja = 0;
			}

			for (int i = 0; i < zmienne->L_wiatraki_przyspieszane_N[0]; i++) {
				zmienne->poziomik.labirynty[0].etapy_wiatraki[i] = -301;
			}

			zmienne->pauza = true;
			if (zmienne->poziomik.etapy[0] == 'l') {//JG:ustawia stan gry zaleznie od pierwszego etapu poziomu
				stanGry = StanEkranu::GRA_LABIRYNT;

			}
			else if (zmienne->poziomik.etapy[0] == 'q') {
				zmienne->odp_zaznaczona = 'A';
				zmienne->ministan = 'q';
				zmienne->proba_max = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_proby;
				zmienne->punkty_wymagane = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_prog_punktowy;
				zmienne->punkty_straznik = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_prog_bezpieczenstwa;
				zmienne->wyzwanie = zmienne->poziomik.quizy[zmienne->biezacy_quiz].Q_wyzwanie;
				stanGry = StanEkranu::GRA_QUIZ;
			}

			zmienne->LAB_czulosc_przycisku[11] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}



		/*for (auto& b : Buttons) {
			b->update();
		}*/
	}
}