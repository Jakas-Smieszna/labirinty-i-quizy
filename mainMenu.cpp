#include "mainMenu.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include <string>
namespace menu {
	// Definicja Przycisków w menu
	Przycisk Buttons[] = {
		Przycisk("Wybierz Poziom", 0.5, 0.3, 20, BUTTON_CENTER),
		Przycisk("Instrukcja", 0.5, 0.4, 20, BUTTON_CENTER),
		Przycisk("Zmień Użytkownika", 0.5, 0.5, 20, BUTTON_CENTER),
		Przycisk("Ustawienia", 0.5, 0.6, 20, BUTTON_CENTER, [&] {stanGry = StanEkranu::USTAWIENIA;}),
		Przycisk("Twórcy", 0.5, 0.7, 20, BUTTON_CENTER, [&] {stanGry = StanEkranu::TWÓRCY;}),
		Przycisk("Wyjdź", 0.5, 0.8, 20, BUTTON_CENTER, [&] {stanGry = StanEkranu::EXIT;}),
	};

	// Rysowanie
	void drawMainMenu() {
		ClearBackground(DARKGREEN);
		// Tekst Główny
		helper::DrawTextCentered("Labirynty i Quizy", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
		// Opcje menu
		for (auto& B : Buttons) {
			B.draw();
		}
	}
	void updateMainMenu() {
		for (auto& B : Buttons) {
			B.update();
		}
	}
}