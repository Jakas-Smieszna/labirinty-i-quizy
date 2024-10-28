#pragma once
#include "raylib.h"
#include <functional>
struct Przycisk {
	const char* text; // text, oczywiście
	float posX, posY; // pozycja
	int fontSize; // rozmiar czcionki 
	bool selected; // czy zaznaczony?
	bool center; // czy wyśrodkowany?
	bool enabled; // czy jest enabled?
	bool forceFitOnScreen; // czy cały przycisk ma być na ekranie? Rusza go jakby wyszedł za ekran.
	Color colorActive;
	Color colorInactive;
	std::function<void()> onActivation; // Co sie dzieje jak borowika aktywuje?
	// Tworzy nowy przycisk.
	// const char* text - tekst. Albo "taki" w cudzysłowiu albo std::string i c_str().
	// float posX - Pozycja tekstu na ekranie od 0 do 1. 0 - na lewo, 1 - na prawo, 0.5 - środek.
	// float posY - Pozycja tekstu na ekranie od 0 do 1. 0 - na górze, 1 - na dole, 0.5 - środek.
	// int fontSize - rozmiar czcionki tekstu
	// bool center - czy tekst jest wyśrodkowany
	// std::function<void()> onActivation - lambda function która się odpali gdy tekst
	// coś w stylu:
	// [&] {/* KOD */};
	// Zobaczcie mainMenu.cpp aby dokładniej obczaić o co mi chodzi z tym
	Przycisk(const char* text, float posX, float posY, int fontSize, bool center = false, std::function<void()> onActivation = [&] {}, bool forceFit = false, Color colorActive = WHITE, Color colorInactive = BLACK) {
		this->text = text;
		this->posX = posX; this->posY = posY;
		this->fontSize = fontSize;
		this->center = center;
		this->onActivation = onActivation;
		this->colorActive = colorActive;
		this->colorInactive = colorInactive;
		forceFitOnScreen = forceFit;
		selected = false;
		enabled = true;
	}
	void update(); // Update, przed rysowaniem.
	void draw(); // Logika sterująca rysowaniem:
	void drawInactive(int x, int y); // Rysowanie, gdy nie jest zaznaczony.
	void drawActive(int x, int y); // Rysowanie, gdy zaznaczony.
};