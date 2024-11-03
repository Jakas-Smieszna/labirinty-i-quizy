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

#define SCALING (1.f)

void PrzyciskTekst::drawInactive(int x, int y) const {
	if (!(flags & BUTTON_NO_OUTLINE)) {
		DrawRectangleLinesEx(getBoundingRect(), 2.5f, EpisodeTheme.borderColor);
		DrawRectangleRec(getBoundingRect(), Fade(EpisodeTheme.bgColor, 0.65f));
	}
	DrawTextEx(EpisodeTheme.textFont, text, {(float)x, (float)y}, getFontSizeScaled(), SCALING, EpisodeTheme.textColor);
}
void PrzyciskTekst::drawHover(int x, int y) const {
	DrawRectangleRec(getBoundingRect(), ColorBrightness(EpisodeTheme.bgColor, 0.35f));
	DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, Fade(EpisodeTheme.textColor, 0.3f));
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
	/*
	float rectX = MeasureText(text, getFontSizeScaled());// *rozmiar.absX;
	float rectY = static_cast<float>(getFontSizeScaled());// *rozmiar.absY;
	*/
	Vector2 rectPos = MeasureTextEx(EpisodeTheme.textFont, text, getFontSizeScaled(), SCALING);
	int x, y; getDrawCoords(&x, &y);
	return Rectangle{ 
		static_cast<float>(x) - rectPos.x * rozmiar.offsetX,
		static_cast<float>(y) - rectPos.y * rozmiar.offsetY,
		rectPos.x * (1 + 2*rozmiar.offsetX),
		rectPos.y * (1 + 2*rozmiar.offsetY)
	};
}

void PrzyciskTekst::getDrawCoords(int* x, int* y) const {
	*x = GetScreenWidth() * pozycja.absX, *y = GetScreenHeight() * pozycja.absY;
	*x += static_cast<int>(MeasureText(text, getFontSizeScaled()) * pozycja.offsetX);
	*y += static_cast<int>(getFontSizeScaled() * pozycja.offsetY);
}

void RadioPrzyciskTekst::drawActive(int x, int y) const {
	DrawRectangleRec(getBoundingRect(), ColorBrightness(EpisodeTheme.bgColor, -0.35f));
	DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, Fade(EpisodeTheme.textColor, 0.3f));
}
void RadioPrzyciskTekst::handleStateChangeConditions()  {
	PrzyciskTekst::handleStateChangeConditions();
	if (activeCondition() && state != NAJECHANY)
		state = AKTYWNY;
}