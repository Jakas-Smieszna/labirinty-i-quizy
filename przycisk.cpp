#include "przycisk.h"
#include "funkcjePomocnicze.h"
void Przycisk::draw() const {
	if (flags & BUTTON_DISABLED) return;
	int x, y;
	getDrawCoords(&x, &y);
	switch (state) {
		case NIEAKTYWNY:
			drawInactive(x, y);
			break;
		case NAJECHANY:
			drawHover(x, y);
			break;
		case AKTYWNY:
			drawActive(x, y);
			break;
	}
}

void Przycisk::drawInactive(int x, int y) const {
	if(flags & BUTTON_CENTER)
		helper::DrawTextCentered(text, x, y, fontSize, colorInactive);
	else
		DrawText(text, x, y, fontSize, colorInactive);
}
void Przycisk::drawHover(int x, int y) const {
	if (flags & BUTTON_CENTER)
		helper::DrawTextCenteredBackgroundColor(text, x, y, fontSize, colorInactive, colorActive);
	else
		helper::DrawTextBackgroundColor(text, x, y, fontSize, colorInactive, colorActive);
}
void Przycisk::drawActive(int x, int y) const {
	drawHover(x, y);
}

void Przycisk::update() {
	if (flags & BUTTON_DISABLED) return;
	handleStateChangeConditions();
	afterStateChangeLogic();

}
void Przycisk::handleStateChangeConditions() {
	int x, y;
	getDrawCoords(&x, &y);
	bool hover = false;
	if (flags & BUTTON_CENTER)
		hover = helper::IsInTextAreaCentered(text, x, y, fontSize, GetMouseX(), GetMouseY());
	else
		hover = helper::IsInTextArea(text, x, y, fontSize, GetMouseX(), GetMouseY());
	state = hover ? NAJECHANY : NIEAKTYWNY;
}

void Przycisk::afterStateChangeLogic() {
	if (state == NAJECHANY && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		onPress();
	}
}

void Przycisk::getDrawCoords(int* x, int* y) const {
	*x = GetScreenWidth() * posX, *y = GetScreenHeight() * posY;
	if (flags & BUTTON_FIT) { // jak musi być na ekranie to yyy przesuwam
		*x = std::max(0, std::min(GetScreenWidth() - MeasureText(text, fontSize), *x));
		*y = std::max(0, std::min(GetScreenHeight() - fontSize, *y));
	}
}

void RadioPrzycisk::drawActive(int x, int y) const {
	if (flags & BUTTON_CENTER)
		helper::DrawTextCenteredBackgroundColor(text, x, y, fontSize, colorInactive, colorActive, 4);
	else
		helper::DrawTextBackgroundColor(text, x, y, fontSize, colorInactive, colorActive, 4);
}
void RadioPrzycisk::handleStateChangeConditions() {
	Przycisk::handleStateChangeConditions();
	if (activeCondition())
		state = AKTYWNY;
}