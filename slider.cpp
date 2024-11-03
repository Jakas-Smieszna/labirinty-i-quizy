#include "slider.h"
#include <functional>
#include <iostream>

void _slider::draw() {
	DrawRectangleRounded(getBackgroundRect(), 1, 12, barColor);
	DrawRectangleRounded(getFillRect(), 1, 12, fillColor);
	DrawCircleV(getCirclePos(), rH * 1, dotColor);
}

void _slider::update() {
	if (CheckCollisionPointCircle( GetMousePosition(), getCirclePos(), rH * 1) || _dragging){
		_dragging = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	}
	if (!_dragging && !CheckCollisionPointRec( GetMousePosition(), getBackgroundRect() )) 
	{
		return;
	}
	bool MBR = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
	if (MBR || _dragging) {
		clickLogic();
	}
}
void _slider::change(float newVal) {
	value = newVal;
	onChange(value);
}

Rectangle sliderHorizontal::getBackgroundRect()
{
	return Rectangle{ 
		GetScreenWidth() * position.absX,
		GetScreenHeight() * position.absY - rH / 2,
		GetScreenWidth() * length, 
		rH 
	};
}

Rectangle sliderHorizontal::getFillRect()
{
	return Rectangle{
		GetScreenWidth() * position.absX,
		GetScreenHeight() * position.absY - rH / 2,
		GetScreenWidth() * length * value, // value jest od 0 do 1 - procent wypełnienia
		rH
	};
}

Vector2 sliderHorizontal::getCirclePos() {
	return Vector2{
		GetScreenWidth() * (position.absX + length * value),
		GetScreenHeight() * position.absY
	};
}

void sliderHorizontal::clickLogic()
{
	float clickXNormalised = std::max(position.absX * GetScreenWidth(), std::min((position.absX + length) * GetScreenWidth(), static_cast<float>(GetMouseX())));
	clickXNormalised -= position.absX * GetScreenWidth();
	clickXNormalised /= length*GetScreenWidth();
	change(min + clickXNormalised * (max - min));
}

Rectangle sliderVertical::getBackgroundRect()
{
	return Rectangle{
	GetScreenWidth() * position.absX - rH / 2,
	GetScreenHeight() * position.absY,
	rH,
	GetScreenHeight() * length
	};
}

Rectangle sliderVertical::getFillRect()
{
	return Rectangle{
	GetScreenWidth() * position.absX - rH / 2,
	GetScreenHeight() * position.absY,
	rH,
	GetScreenHeight() * length * value
	};
}

Vector2 sliderVertical::getCirclePos() {
	return Vector2{
		GetScreenWidth() * position.absX,
		GetScreenHeight() * (position.absY + length * value)
	};
}

void sliderVertical::clickLogic()
{
	float clickYNormalised = std::max(position.absY * GetScreenHeight(), std::min((position.absY + length) * GetScreenHeight(), static_cast<float>(GetMouseY())));
	clickYNormalised -= position.absY * GetScreenHeight();
	clickYNormalised /= length * GetScreenHeight();
	change(min + clickYNormalised * (max - min));
}