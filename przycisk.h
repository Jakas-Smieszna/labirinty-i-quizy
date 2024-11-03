#pragma once
#include "raylib.h"
#include "positioning.h"
#include <functional>
enum StanPrzycisku {
	NIEAKTYWNY = 0,
	NAJECHANY,
	AKTYWNY
};

// flagi
#define BUTTON_NONE	(0)		// Default.
#define BUTTON_DISABLED (1<<0)	// Czy przycisk jest wyłączony?

struct _Przycisk {
	ScreenPos pozycja; // pozycja przycisku na ekranie
	ScreenPos rozmiar; // rozmiar przycisku na ekranie
	StanPrzycisku state; // stan przycisku
	// Flagi przycisku:
	// BUTTON_NONE - dosłownie nic; default. Nie trzeba tego ustawiać.
	// BUTTON_DISABLED - czy przycisk jest wyłączony?
	// więcej sie doda jak będzie to potrzebne
	int flags;

	// Funkcja aktywacji; najłatwiej podać w konstruktorze jako lambda function
	// https://en.cppreference.com/w/cpp/language/lambda
	// tldr: coś w stylu 
	// [&] { /* KOD FUNKCJI */; }
	// przykłady w mainMenu.cpp
	std::function<void()> onActivation;

};

struct PrzyciskTekst : public _Przycisk {
	const char* text; // text, oczywiście
	int fontSize; // rozmiar czcionki 
	Color colorActive;
	Color colorInactive;

	// Tworzy nowy przycisk.
	// const char* text - tekst. Albo "taki" w cudzysłowiu albo std::string i c_str().
	// float posX - Pozycja tekstu na ekranie od 0 do 1. 0 - na lewo, 1 - na prawo, 0.5 - środek.
	// float posY - Pozycja tekstu na ekranie od 0 do 1. 0 - na górze, 1 - na dole, 0.5 - środek.
	// int fontSize - rozmiar czcionki tekstu
	// bool center - czy tekst jest wyśrodkowany
	// std::function<void()> onPress - lambda function która się odpali gdy tekst
	// coś w stylu:
	// [&] {/* KOD */};
	// Zobaczcie mainMenu.cpp aby dokładniej obczaić o co mi chodzi z tym
	Przycisk(
		const char* text, // Test
		float posX,
		float posY,
		int fontSize,
		int flags = BUTTON_NONE,
		std::function<void()> onPress = [&] {},
		Color colorActive = WHITE,
		Color colorInactive = BLACK) :
		text(text), posX(posX), posY(posY), fontSize(fontSize), flags(flags), onPress(onPress),
		colorActive(colorActive), colorInactive(colorInactive)
	{
		state = NIEAKTYWNY;
	}
	void update(); // Update, przed rysowaniem.

	// Te funkcje nie mogą zmienić stanu przycisku:
	void draw() const; // Logika sterująca rysowaniem:
	void drawInactive(int x, int y) const; // Rysowanie, gdy nie jest zaznaczony.
	void drawHover(int x, int y) const; // Rysowanie, gdy najechany.
	void drawActive(int x, int y) const; // Rysowanie, gdy jest *aktywny*
protected:
	void getDrawCoords(int* x, int* y) const; // zwraca, przez wskaźnik, x i y koordynatów do rysowania
	void handleStateChangeConditions();
	void afterStateChangeLogic();
};

struct RadioPrzycisk : public Przycisk {
	std::function<bool()> activeCondition;

	RadioPrzycisk(
		const char* text, // Test
		float posX,
		float posY,
		int fontSize,
		int flags,
		std::function<void()> onPress = [&] {},
		std::function<bool()> activeCondition = [&] {return false; },
		Color colorActive = WHITE,
		Color colorInactive = BLACK) :
		Przycisk(text, posX, posY, fontSize, flags, onPress, colorActive, colorInactive),
		activeCondition(activeCondition) {};
	void drawActive(int x, int y) const; // Rysowanie, gdy jest *aktywny*
	void handleStateChangeConditions();

};