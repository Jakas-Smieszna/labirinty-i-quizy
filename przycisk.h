#pragma once
#include "raylib.h"
#include "positioning.h"
#include "Grafika.h"
#include <functional>
#include <iostream>
enum StanPrzycisku {
	NIEAKTYWNY = 0,
	NAJECHANY,
	AKTYWNY
};

// flagi
#define BUTTON_NONE	(0)		// Default.
#define BUTTON_DISABLED (1<<0)	// Czy przycisk jest wyłączony?
#define BUTTON_NO_OUTLINE (1<<1) // Czy nie rysować go w prostokącie?

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
		const char* tekst, // Test
		ScreenPos position,
		int _fontSize,
		std::function<void()> onPress = [&] {},
		int flags = BUTTON_NONE) :
		_Przycisk(position, {0,0,0,0}, onPress, flags)
	{
		text = tekst;
		fontSize = _fontSize;
		//std::cout << (MeasureText(tekst, _fontSize)) << " | " << static_cast<float>(_fontSize) << std::endl;
	};
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
	Rectangle getBoundingRect() const;
	bool initialized = false;
	void initialize() {
		rozmiar = {
			static_cast<float>(MeasureText(text, fontSize)) / static_cast<float>(OknoSzerBaz),
			static_cast<float>(fontSize) / static_cast<float>(OknoWysBaz),
			0.05f,
			0.2f
		};
		initialized = true;
	}
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