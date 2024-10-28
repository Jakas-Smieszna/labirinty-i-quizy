#pragma once
#include "raylib.h"
struct slider {
	float min = 0, max = 100, value = 50;
	Color barColor = DARKGRAY;
	Color fillColor = WHITE;
	Color dotColor = GRAY;
	float posX, posY;
	float width;
	slider(const char* text, float posX, float posY, float width) : posX(posX), posY(posY), width(width) {};
	void draw();
	void update();

	float rH = 8;
	bool _dragging = false;
};