#pragma once
#include "raylib.h"
#include "positioning.h"
#include <functional>
struct _slider {
	float min = 0, max = 1, value = 0.5;
	Color barColor = DARKGRAY;
	Color fillColor = WHITE;
	Color dotColor = GRAY;
	ScreenPos position;
	float length;
	// Wywoływana raz, gdy klikasz by ustawić slider.
	// Wywoływana WIELOKROTNIE, gdy przesuwasz slider przez kulke.
	std::function<void(float)> onChange;
	_slider(ScreenPos position, float length, std::function<void(float)> onChange = [&](float) {}) :
		position(position), length(length), onChange(onChange) {};

	void draw();
	void update();
	void change(float newVal);
	float rH = 8;
	bool _dragging = false;
	virtual Rectangle getBackgroundRect() = 0;
	virtual Rectangle getFillRect() = 0;
	virtual Vector2 getCirclePos() = 0;
	virtual void clickLogic() = 0;
	
};

struct sliderHorizontal : public _slider {
	sliderHorizontal(ScreenPos position, float length, std::function<void(float)> onChange = [&](float) {}) :
		_slider(position, length, onChange) {};

	Rectangle getBackgroundRect();
	Rectangle getFillRect();
	Vector2 getCirclePos();
	void clickLogic();
};

struct sliderVertical : public _slider {
	sliderVertical(ScreenPos position, float length, std::function<void(float)> onChange = [&](float) {}) :
		_slider(position, length, onChange) {};

	Rectangle getBackgroundRect();
	Rectangle getFillRect();
	Vector2 getCirclePos();
	void clickLogic();
};