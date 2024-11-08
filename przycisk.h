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

	//JG+:do losowej tekstury:
	float los_pole_x;
	float los_pole_y;
	//JG+:koniec

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

		los_pole_x = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
		los_pole_y = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
	}
	_Przycisk() {
		pozycja = { 0,0,0,0 };
		rozmiar = { 0,0,0,0 };
		onActivation = [&] {};
		flags = BUTTON_DISABLED;
		state = NIEAKTYWNY;

		los_pole_x = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
		los_pole_y = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
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
		_Przycisk(position, {0.f,0.f,0.05f,0.2f}, onPress, flags)
	{
		text = tekst;
		fontSize = _fontSize;
	};
	void update(); // Update, przed rysowaniem.

	// Te funkcje nie mogą zmienić stanu przycisku:
	void draw() const;
	void drawInactive(int x, int y) const; // Rysowanie, gdy nie jest zaznaczony.
	void drawHover(int x, int y) const; // Rysowanie, gdy najechany.
	void virtual drawActive(int x, int y) const; // Rysowanie, gdy jest *aktywny*
protected:
	void getDrawCoords(int* x, int* y) const; // zwraca, przez wskaźnik, x i y koordynatów do rysowania
	void virtual handleStateChangeConditions() ;
	void afterStateChangeLogic();
	Rectangle getBoundingRect() const;
	int getFontSizeScaled() const {
		float scale = 1.f;
		if (GetScreenWidth() >= GetScreenHeight() * grafiki->tlo.szer / grafiki->tlo.wys) {
			scale = (float)GetScreenHeight() / OknoWysBaz;
		} else {
			scale = (float)GetScreenWidth() / OknoSzerBaz;
		}
		return static_cast<int>(static_cast<float>(fontSize) * scale);
	}
};

struct RadioPrzyciskTekst : public PrzyciskTekst {
	std::function<bool()> activeCondition;

	RadioPrzyciskTekst(
		const char* tekst, // Test
		ScreenPos position,
		int _fontSize,
		std::function<void()> onPress = [&] {},
		std::function<bool()> activeCond = [&] {return false; },
		int flags = BUTTON_NONE) :
		PrzyciskTekst(tekst, position, _fontSize, onPress, flags),
		activeCondition(activeCond) {};
	void drawActive(int x, int y) const; // Rysowanie, gdy jest *aktywny*
	void handleStateChangeConditions() ;

};