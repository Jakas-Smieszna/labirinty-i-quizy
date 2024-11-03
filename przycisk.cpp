#include "Przycisk.h"
#include "funkcjePomocnicze.h"
void PrzyciskTekst::draw() const {
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

void PrzyciskTekst::drawInactive(int x, int y) const {
	//if(flags & BUTTON_CENTER)
	//	helper::DrawTextCentered(text, x, y, fontSize, colorInactive);
	//else
	DrawText(text, x, y, fontSize, colorInactive);
}
void PrzyciskTekst::drawHover(int x, int y) const {
	//if (flags & BUTTON_CENTER)
	//	helper::DrawTextCenteredBackgroundColor(text, x, y, fontSize, colorInactive, colorActive);
	//else
	helper::DrawTextBackgroundColor(text, x, y, fontSize, colorInactive, colorActive);
}
void PrzyciskTekst::drawActive(int x, int y) const {
	drawHover(x, y);
}

void PrzyciskTekst::update() {
	if (flags & BUTTON_DISABLED) return;
	handleStateChangeConditions();
	afterStateChangeLogic();

}
void PrzyciskTekst::handleStateChangeConditions() {
	int x, y;
	getDrawCoords(&x, &y);
	bool hover = false;
	//if (flags & BUTTON_CENTER)
	//	hover = helper::IsInTextAreaCentered(text, x, y, fontSize, GetMouseX(), GetMouseY());
	//else
	hover = helper::IsInTextArea(text, x, y, fontSize, GetMouseX(), GetMouseY());
	state = hover ? NAJECHANY : NIEAKTYWNY;
}

void PrzyciskTekst::afterStateChangeLogic() {
	if (state == NAJECHANY && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		onActivation();
	}
}

void PrzyciskTekst::getDrawCoords(int* x, int* y) const {
	*x = GetScreenWidth() * pozycja.absX, *y = GetScreenHeight() * pozycja.absY;
	*x += static_cast<int>(MeasureText(text, fontSize) * pozycja.offsetX);
	*y += static_cast<int>(fontSize * pozycja.offsetY);
}
/*
void RadioPrzyciskTekst::drawActive(int x, int y) const {
	if (flags & BUTTON_CENTER)
		helper::DrawTextCenteredBackgroundColor(text, x, y, fontSize, colorInactive, colorActive, 4);
	else
		helper::DrawTextBackgroundColor(text, x, y, fontSize, colorInactive, colorActive, 4);
}
void RadioPrzyciskTekst::handleStateChangeConditions() {
	PrzyciskTekst::handleStateChangeConditions();
	if (activeCondition())
		state = AKTYWNY;
}
*/