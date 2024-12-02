#pragma once
#include "raylib.h"
#include "positioning.h"
#include "IDrawable.h"
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

class _Przycisk : public IDrawable {
	typedef IDrawable super;
protected:
	//JG+:do losowej tekstury:
	float los_pole_x;
	float los_pole_y;
	//JG+:koniec

	StanPrzycisku state; // stan przycisku
	// Flagi przycisku:
	// BUTTON_NONE - dosłownie nic; default. Nie trzeba tego ustawiać.
	// BUTTON_DISABLED - czy przycisk jest wyłączony?
	// więcej sie doda jak będzie to potrzebne
	int buttonFlags;

	// Funkcja aktywacji; najłatwiej podać w konstruktorze jako lambda function
	// https://en.cppreference.com/w/cpp/language/lambda
	// tldr: coś w stylu 
	// [&] { /* KOD FUNKCJI */; }
	// przykłady w mainMenu.cpp
	std::function<void()> onActivation;
public:
	_Przycisk(Vector2 pos, Vector2 size, std::function<void()> FunkcjaAktywacji = [&] {}) :
		super(pos, size) {
		onActivation = FunkcjaAktywacji;
		buttonFlags = BUTTON_NONE;
		state = NIEAKTYWNY;

		los_pole_x = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
		los_pole_y = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
	}
	_Przycisk() : super({ 0,0 }, { 0,0 }) {
		onActivation = [&] {};
		buttonFlags = BUTTON_DISABLED;
		state = NIEAKTYWNY;

		los_pole_x = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
		los_pole_y = (float)(rand() % 51) * 0.01f * 1000.0f;//JG+
	}

	void setButtonFlags(int newFlags) { buttonFlags = newFlags; }

};

class PrzyciskTekst : public _Przycisk {
	typedef _Przycisk super;
protected:
	const char* text; // text, oczywiście
	// Te funkcje nie mogą zmienić stanu przycisku:
	void virtual drawInactive(int x, int y) const; // Rysowanie, gdy nie jest zaznaczony.
	void virtual drawHover(int x, int y) const; // Rysowanie, gdy najechany.
	void virtual drawActive(int x, int y) const; // Rysowanie, gdy jest *aktywny*
	//void getDrawCoords(int* x, int* y) const; // zwraca, przez wskaźnik, x i y koordynatów do rysowania

	void virtual handleStateChangeConditions() ;
	void afterStateChangeLogic();
	int getFontSizeScaled() const {
		float fontSize = getBoundingBox().y - 2.f;
		float scale = 1.f;
		if (GetScreenWidth() >= GetScreenHeight() * grafiki->tlo.szer / grafiki->tlo.wys) {
			scale = (float)GetScreenHeight() / OknoWysBaz;
		} else {
			scale = (float)GetScreenWidth() / OknoSzerBaz;
		}
		return static_cast<int>(fontSize * scale);
	}
public:
	// Tworzy nowy przycisk.
	// const char* text - tekst. Albo "taki" w cudzysłowiu albo std::string i c_str().
	// Vector2 pos - pozycja względem elementu macierzystego.
	// Vector2 size - rozmiar względem elementu macierzystego.
	// std::function<void()> onPress - lambda function która się odpali gdy tekst
	// coś w stylu:
	// [&] {/* KOD */};
	// Zobaczcie mainMenu.cpp aby dokładniej obczaić o co mi chodzi z tym
	// int flags - flagi; na tą chwile nieużywane
	PrzyciskTekst(
		const char* tekst, Vector2 pos, Vector2 size,
		std::function<void()> onPress = [&] {}, int flags = BUTTON_NONE) :
		super(pos, size, onPress)
	{
		text = tekst;
		setButtonFlags(flags);
	};
	virtual void update();
	virtual void draw() const;
};

struct RadioPrzyciskTekst : public PrzyciskTekst {
	std::function<bool()> activeCondition;

	RadioPrzyciskTekst(
		const char* tekst, Vector2 pos, Vector2 size,
		std::function<void()> onPress = [&] {},
		std::function<bool()> activeCond = [&] {return false; },
		int flags = BUTTON_NONE) :
		PrzyciskTekst(tekst, pos, size, onPress, flags),
		activeCondition(activeCond) {};
	void drawActive(int x, int y) const; // Rysowanie, gdy jest *aktywny*
	void handleStateChangeConditions() ;

};