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
	if (!(flags & BUTTON_NO_OUTLINE)) {
		int pad = 5;
		float txtWidth = (float)MeasureText(text, fontSize);
		DrawRectangleLinesEx(getBoundingRect(), 2.5f, EpisodeTheme.borderColor);
		DrawRectangleRec(getBoundingRect(), Fade(EpisodeTheme.bgColor, 0.65f));
	}
	DrawText(text, x, y, fontSize, EpisodeTheme.textColor);
}
void PrzyciskTekst::drawHover(int x, int y) const {
	int pad = 5;
	float txtWidth = (float)MeasureText(text, fontSize);
	DrawRectangleRec(getBoundingRect(), ColorBrightness(EpisodeTheme.bgColor, 0.35f));
	DrawText(text, x, y, fontSize, Fade(EpisodeTheme.textColor, 0.3f));
	//helper::DrawTextBackgroundColor(text, x, y, fontSize, EpisodeTheme.textColor, colorActive);
}
void PrzyciskTekst::drawActive(int x, int y) const {
	drawHover(x, y);
}

void PrzyciskTekst::update() {
	if (flags & BUTTON_DISABLED) return;
	if (!initialized) initialize();
	handleStateChangeConditions();
	afterStateChangeLogic();

}
void PrzyciskTekst::handleStateChangeConditions() {
	int x, y;
	getDrawCoords(&x, &y);
	bool hover = helper::IsInRect(getBoundingRect(), GetMouseX(), GetMouseY());
	state = hover ? NAJECHANY : NIEAKTYWNY;
}

void PrzyciskTekst::afterStateChangeLogic() {
	if (state == NAJECHANY && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		onActivation();
	}
}

Rectangle PrzyciskTekst::getBoundingRect() const
{
	float rectX = GetScreenWidth() * rozmiar.absX;
	float rectY = GetScreenHeight() * rozmiar.absY;
	int x, y; getDrawCoords(&x, &y);
	Rectangle ret = { static_cast<float>(x) - rectX * rozmiar.offsetX, static_cast<float>(y) - rectY * rozmiar.offsetY,
		rectX * (1 + 2*rozmiar.offsetX), rectY * (1 + 2*rozmiar.offsetY)
	};
	return ret;
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