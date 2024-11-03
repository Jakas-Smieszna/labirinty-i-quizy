#include "mainMenu.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include <string>
namespace menu {
	// Definicja Przycisków w menu
	_Przycisk* Buttons[] = {
		new PrzyciskTekst("Wybierz Poziom", {0.5, 0.3, -0.5, 0}, 30),
		new PrzyciskTekst("Instrukcja",{0.5, 0.4, -0.5, 0}, 20),
		new PrzyciskTekst("Zmień Użytkownika", {0.5, 0.5, -0.5, 0}, 20),
		new PrzyciskTekst("Ustawienia", {0.5, 0.6, -0.5, 0}, 20, [&] {stanGry = StanEkranu::USTAWIENIA;}),
		new PrzyciskTekst("Twórcy", {0.5, 0.7, -0.5, 0}, 20, [&] {stanGry = StanEkranu::TWÓRCY;}),
		new PrzyciskTekst("Wyjdź", {0.5, 0.8, -0.5, 0}, 20, [&] {stanGry = StanEkranu::EXIT;}),
	};

	// Rysowanie
	void drawMainMenu() {
		ClearBackground(DARKGREEN);
		// Tekst Główny
		helper::DrawTextCentered("Labirynty i Quizy", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 40, WHITE);
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