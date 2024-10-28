#include "przycisk.h"
#include "funkcjePomocnicze.h"
void Przycisk::draw() {
	int x = GetScreenWidth() * posX, y = GetScreenHeight() * posY;
	if (forceFitOnScreen) {
		x = std::max(0, std::min(GetScreenWidth() - MeasureText(text, fontSize), x));
		y = std::max(0, std::min(GetScreenHeight() - fontSize, y));
	}
	if (selected)
		drawActive(x, y);
	else
		drawInactive(x, y);
}

void Przycisk::drawInactive(int x, int y) {
	if(center)
		helper::DrawTextCentered(text, x, y, fontSize, colorInactive);
	else
		DrawText(text, x, y, fontSize, colorInactive);
}
void Przycisk::drawActive(int x, int y) {
	if (center)
		helper::DrawTextCenteredBackgroundColor(text, x, y, fontSize, colorInactive, colorActive);
	else
		helper::DrawTextBackgroundColor(text, x, y, fontSize, colorInactive, colorActive);
}
void Przycisk::update() {
	int x = GetScreenWidth() * posX, y = GetScreenHeight() * posY;
	if (forceFitOnScreen) {
		x = std::max(0, std::min(GetScreenWidth() - MeasureText(text, fontSize), x));
		y = std::max(0, std::min(GetScreenHeight() - fontSize, y));
	}
	if (center)
		selected = helper::IsInTextAreaCentered(text, x, y, fontSize, GetMouseX(), GetMouseY());
	else
		selected = helper::IsInTextArea(text, x, y, fontSize, GetMouseX(), GetMouseY());

	if (selected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		onActivation();
	}
}