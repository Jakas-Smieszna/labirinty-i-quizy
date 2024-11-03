#include "slider.h"
#include <functional>
#include <iostream>

void slider::draw() {
	DrawRectangleRounded(Rectangle{ GetScreenWidth() * posX,GetScreenHeight() * posY - rH / 2,
		GetScreenWidth() * width, rH },
		1, 12, barColor);
	DrawRectangleRounded(Rectangle{ GetScreenWidth() * posX,GetScreenHeight() * posY - rH / 2,
		GetScreenWidth() * width * ((value - min) / max), rH},
		1, 12, fillColor);
	DrawCircleV(Vector2{ GetScreenWidth() * (posX + width * ((value - min) / max)), GetScreenHeight()* posY },
		rH * 1, dotColor);
}

void slider::update() {
	if (CheckCollisionPointCircle(
		GetMousePosition(), 
		Vector2{ GetScreenWidth() * (posX + width * ((value - min) / max)), GetScreenHeight() * posY },
		rH * 1) || _dragging){
		_dragging = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	}
	if (!_dragging && !CheckCollisionPointRec(
		Vector2{ static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) },
		Rectangle{ GetScreenWidth() * posX,GetScreenHeight() * posY - rH / 2, GetScreenWidth() * width, rH })
		) 
	{
		return;
	}
	bool MBR = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
	if (MBR || _dragging) {
		float clickXNormalised = std::max(posX * GetScreenWidth(), std::min((posX + width) * GetScreenWidth(), static_cast<float>(GetMouseX())));
		clickXNormalised -= posX * GetScreenWidth();
		clickXNormalised /= (width) * GetScreenWidth();
		change(min + clickXNormalised * (max - min));
	}
}
void slider::change(float newVal) {
	value = newVal;
	onChange(value);
}
