#pragma once
#include "raylib.h"
#include <functional>
struct slider {
	float min = 0, max = 100, value = 50;
	Color barColor = DARKGRAY;
	Color fillColor = WHITE;
	Color dotColor = GRAY;
	float posX, posY;
	float width;
	// Wywoływana raz, gdy klikasz by ustawić slider.
	// Wywoływana WIELOKROTNIE, gdy przesuwasz slider przez kulke.
	std::function<void(float)> onChange;
	slider(const char* text, float posX, float posY, float width, std::function<void(float)> onChange = [&](float) {}) :
		posX(posX), posY(posY), width(width), onChange(onChange) {};
	void draw();
	void update();
	void change(float newVal);

	float rH = 8;
	bool _dragging = false;
};