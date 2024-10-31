#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "Grafika.h"
#include "gamestate.h"
#include "przycisk.h"
#include <string>

namespace labirynt {
	

	// Rysowanie
	void drawLabirynt(GRAFIKI* grafiki, PakietZmiennych* zmienne) {
		ClearBackground(BLACK);
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
		}
		else {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
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
			napis_epizodu = MAGENTA;
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
		DrawRectangle(szer * 0.8f, 0.0f, szer * 0.21f, wys, Fade(szata_epizodu, 0.75f));
		DrawRectangle(0.0f, 0.0f, szer * 0.8f, wys * 0.05f, Fade(szata_epizodu, 0.75f));
		DrawRectangle(szer * 0.798f, 0.0f, szer * 0.003f + 1.0f, wys, BLACK);
		DrawRectangle(0.0f, wys * 0.05f, szer * 0.8f, szer * 0.003f + 1.0f, BLACK);

		DrawText(TextFormat("Epizod: %d", zmienne->epizod), 0.01f * szer, 0.01f * wys, (int)(26.0f * wys/OknoWysBaz), napis_epizodu);//JG:wyswietla biezacy epizod
		DrawText(TextFormat("Poziom: %d", zmienne->poziom), 0.11f * szer, 0.01f * wys, (int)(26.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla biezacy poziom
		DrawText(TextFormat("Czas: %0.2lf", zmienne->czas), 0.21f * szer, 0.01f * wys, (int)(26.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla biezacy czas

		DrawText(zmienne->uzytkownik, 0.81f * szer, 0.02f * wys, (int)(28.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla biezacego gracza
		DrawTexturePro(grafiki->puchar.text, { 0.0f, 0.0f, grafiki->puchar.szer, grafiki->puchar.wys }, { szer * 0.81f, wys * 0.09f, 0.09f * wys * grafiki->puchar.szer / grafiki->puchar.wys, 0.09f * wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, 0.0f));
		DrawTexturePro(grafiki->puchar.text, { 0.0f, 0.0f, grafiki->puchar.szer, grafiki->puchar.wys }, { szer * 0.96f, wys * 0.09f, 0.09f * wys * grafiki->puchar.szer / grafiki->puchar.wys, 0.09f * wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, 0.0f));
		DrawText("WYNIKI", 0.855f * szer, 0.115f * wys, (int)(36.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla naglowek

		DrawText(TextFormat("Biezacy: %0.2lf", zmienne->wynik), 0.81f * szer, 0.2f * wys, (int)(21.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla obecny wynik biezacego gracza
		DrawText(TextFormat("Rekord gracza: %0.2lf", zmienne->rekord_wlasny), 0.81f * szer, 0.24f * wys, (int)(21.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla obecny wynik biezacego gracza
		DrawText(TextFormat("Rekord lokalny: %0.2lf", zmienne->rekord_lokalny), 0.81f * szer, 0.28f * wys, (int)(21.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla obecny wynik biezacego gracza
		DrawText(TextFormat("Rekord swiata: %0.2lf", zmienne->rekord_swiata), 0.81f * szer, 0.32f * wys, (int)(21.0f * wys / OknoWysBaz), napis_epizodu);//JG:wyswietla obecny wynik biezacego gracza
		//helper::DrawTextCentered("Labirynty i Quizy", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
		// Opcje menu
		/*for (auto& B : Buttons) {
			B.draw();
		}*/
	}
	/*void updateLabirynt() {
		for (auto& B : Buttons) {
			B.update();
		}
	}*/
}