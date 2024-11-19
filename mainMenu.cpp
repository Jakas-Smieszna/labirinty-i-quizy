#include "mainMenu.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "Grafika.h"
#include "ustawienia.h"
#include "gamestate.h"
#include "przycisk.h"
#include <string>
namespace menu {
	// Definicja Przycisków w menu
	_Przycisk* Buttons[] = {
		new PrzyciskTekst("Wybierz Poziom", {0.5, 0.3, -0.5, 0}, 30, [&] { {stanGry = StanEkranu::WYBOR_POZIOMU; }}),
		new PrzyciskTekst("Instrukcja",{0.5, 0.4, -0.5, 0}, 20, [&] { {stanGry = StanEkranu::INSTRUKCJA; }}),
		new PrzyciskTekst("Zmień Użytkownika", {0.5, 0.5, -0.5, 0}, 20, [&] { {stanGry = StanEkranu::WYBOR_UZYTKOWNIKA; }}),
		new PrzyciskTekst("Ustawienia", {0.5, 0.6, -0.5, 0}, 20, [&] {stanGry = StanEkranu::USTAWIENIA; ustawienia::initSettings();}),
		new PrzyciskTekst("Twórcy", {0.5, 0.7, -0.5, 0}, 20, [&] {stanGry = StanEkranu::TWORCY;}),
		new PrzyciskTekst("Wyjdź", {0.5, 0.8, -0.5, 0}, 20, [&] {stanGry = StanEkranu::EXIT;}),
#ifdef _DEBUG // tego w Release nie będzie
		new PrzyciskTekst("QUIZ", {0.2, 0.2, 0, 0}, 20, [&] {stanGry = StanEkranu::GRA_QUIZ; }),
		new PrzyciskTekst("LABIRYNT", {0.2, 0.3, 0, 0}, 20, [&] {stanGry = StanEkranu::GRA_LABIRYNT; })
#endif // _DEBUG // tego w Release nie będzie

	};

	// Rysowanie
	void drawMainMenu() {
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		float Skala_liter;//JG+
		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, {0.0f, 0.0f}, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = wys / OknoWysBaz;//JG+
		}
		else {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = szer / OknoSzerBaz;//JG+
		}

		//JG+poczatek - panelek
		float szer_pom = 500.0 * Skala_liter;
		float wys_pom = 560.0f * Skala_liter;
		float x_pom = (szer - szer_pom) * 0.5f;
		float y_pom = (wys - wys_pom) * 0.5f + 60.0f * Skala_liter;
		DrawRectangle(x_pom, y_pom, szer_pom, wys_pom, Fade(EpisodeTheme.bgColor, 0.75f));
		DrawRectangle(x_pom - 1.0f * Skala_liter, y_pom - 1.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
		DrawRectangle(x_pom - 1.0f * Skala_liter + szer_pom, y_pom - 1.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
		DrawRectangle(x_pom - 1.0f * Skala_liter, y_pom - 1.0f * Skala_liter + wys_pom, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);
		DrawRectangle(x_pom - 1.0f * Skala_liter, y_pom - 1.0f * Skala_liter, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);
		//JG+koniec
		
		//DrawTexturePro(tlo.text, {0.0f, 0.0f, tlo.szer, tlo.wys}, {0.0f, 0.0f, tlo.szer, tlo.wys}, {0.0f, 0.0f}, 0.0f, WHITE);
		// Tekst Główny
		helper::DrawTextCentered("Labirynty i Quizy", GetScreenWidth() / 2 + 5.0f * Skala_liter, y_pom - 95.0f * Skala_liter, 75.0f * Skala_liter, BLACK);//JG mod MG0 'cien'
		helper::DrawTextCentered("Labirynty i Quizy", GetScreenWidth() / 2, y_pom - 100.0f * Skala_liter, 75.0f * Skala_liter, EpisodeTheme.textColor);//JG mod MG0
		//helper::DrawTextCentered("Labirynty i Quizy", GetScreenWidth() / 2, (60.0f + 0.5f * (wys - wys_pom)) * 0.5f * Skala_liter, 40.0f * Skala_liter, EpisodeTheme.textColor);//JG mod MG0
		//helper::DrawTextCentered("Labirynty i Quizy", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 40, WHITE);
		// Opcje menu
		for (auto& B : Buttons) {
			B->draw();
		}
	}
	void updateMainMenu() {
		for (auto& B : Buttons) {
			B->update();
		}
	}
}