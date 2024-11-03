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

	_Przycisk(ScreenPos Pozycja, ScreenPos Rozmiar, std::function<void()> FunkcjaAktywacji = [&] {}, int Flagi = BUTTON_NONE) {
		pozycja = Pozycja;
		rozmiar = Rozmiar;
		onActivation = FunkcjaAktywacji;
		flags = Flagi;
		state = NIEAKTYWNY;
	}
	_Przycisk() {
		pozycja = { 0,0,0,0 };
		rozmiar = { 0,0,0,0 };
		onActivation = [&] {};
		flags = BUTTON_DISABLED;
		state = NIEAKTYWNY;
	}

	virtual void update() = 0; // Update, przed rysowaniem.
	virtual void draw() const = 0; // Logika sterująca rysowaniem

};

struct PrzyciskTekst : public _Przycisk {
	const char* text; // text, oczywiście
	int fontSize; // rozmiar czcionki 
	Color colorActive;
	Color colorInactive;

	// Tworzy nowy przycisk.
	// const char* text - tekst. Albo "taki" w cudzysłowiu albo std::string i c_str().
	// ScreenPos position - pozycja, patrz positioning.h, ale przykłady:
	// lewy dolny róg ekranu, tak by sie przycisk mieścił: {0, 1, 0, -1}
	// środek, wyśrodkowany: {0.5, 0.5, -0.5, -0.5}
	// itp. dokładniejsze info w positioning.h
	// int fontSize - rozmiar czcionki tekstu
	// std::function<void()> onPress - lambda function która się odpali gdy tekst
	// coś w stylu:
	// [&] {/* KOD */};
	// Zobaczcie mainMenu.cpp aby dokładniej obczaić o co mi chodzi z tym
	// int flags - flagi; na tą chwile nieużywane
	PrzyciskTekst(
		const char* text, // Test
		ScreenPos position,
		int fontSize,
		std::function<void()> onPress = [&] {},
		int flags = BUTTON_NONE,
		Color colorActive = WHITE,
		Color colorInactive = BLACK) :
		_Przycisk(position, {0,0,0,0}, onPress, flags),
		text(text), fontSize(fontSize),
		colorActive(colorActive), colorInactive(colorInactive)
	{};
	void update(); // Update, przed rysowaniem.

	// Te funkcje nie mogą zmienić stanu przycisku:
	void draw() const;
	void drawInactive(int x, int y) const; // Rysowanie, gdy nie jest zaznaczony.
	void drawHover(int x, int y) const; // Rysowanie, gdy najechany.
	void drawActive(int x, int y) const; // Rysowanie, gdy jest *aktywny*
protected:
	void getDrawCoords(int* x, int* y) const; // zwraca, przez wskaźnik, x i y koordynatów do rysowania
	void handleStateChangeConditions();
	void afterStateChangeLogic();
};
/*
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
*/