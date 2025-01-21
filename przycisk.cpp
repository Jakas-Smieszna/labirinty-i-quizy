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
	Rectangle pom = getBoundingRect();//JG mod MG0
	if (!(flags & BUTTON_NO_OUTLINE)) {
		DrawRectangleRec({ pom.x - 2.5f * SCALING, pom.y - 2.5f * SCALING, pom.width + 5.0f * SCALING, pom.height + 5.0f * SCALING }, BLACK);//JG mod MG0 kontur
		DrawRectangleRec({pom.x - 1.5f *SCALING, pom.y - 1.5f * SCALING, pom.width + 3.0f *SCALING, pom.height + 3.0f * SCALING}, EpisodeTheme.textColor);//JG mod MG0
		DrawTexturePro(grafiki->pole1.text, {los_pole_x, los_pole_y, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, pom, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, 0.0f));//JG+
		/*DrawRectangleLinesEx(getBoundingRect(), 2.5f, EpisodeTheme.borderColor);
		DrawRectangleRec(getBoundingRect(), Fade(EpisodeTheme.bgColor, 0.65f));*/
	}
	DrawTextEx(EpisodeTheme.textFont, text, {(float)x, (float)y}, getFontSizeScaled(), SCALING, EpisodeTheme.textColor);
}
void PrzyciskTekst::drawHover(int x, int y) const {
	//DrawRectangleRec(getBoundingRect(), ColorBrightness(EpisodeTheme.bgColor, 0.35f));
	Rectangle pom = getBoundingRect();//JG mod MG0
	DrawRectangleRec({ pom.x - 2.5f * SCALING, pom.y - 2.5f * SCALING, pom.width + 5.0f * SCALING, pom.height + 5.0f * SCALING }, BLACK);//JG mod MG0 kontur
	DrawRectangleRec({ pom.x - 1.5f * SCALING, pom.y - 1.5f * SCALING, pom.width + 3.0f * SCALING, pom.height + 3.0f * SCALING }, EpisodeTheme.textColor);//JG mod MG0
	DrawTexturePro(grafiki->pole1.text, { los_pole_x, los_pole_y, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, pom, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.5f));//JG+
	DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, EpisodeTheme.textColor);//JG mod MG0
	//DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, Fade(EpisodeTheme.textColor, 0.3f));
}
void PrzyciskTekst::drawActive(int x, int y) const {
	//drawHover(x, y);
	Rectangle pom = getBoundingRect();//JG mod MG0
	DrawRectangleRec({ pom.x - 2.5f * SCALING, pom.y - 2.5f * SCALING, pom.width + 5.0f * SCALING, pom.height + 5.0f * SCALING }, BLACK);//JG mod MG0 kontur
	DrawRectangleRec({ pom.x - 1.5f * SCALING, pom.y - 1.5f * SCALING, pom.width + 3.0f * SCALING, pom.height + 3.0f * SCALING }, EpisodeTheme.textColor);//JG mod MG0
	DrawTexturePro(grafiki->pole1.text, { los_pole_x, los_pole_y, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, pom, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.75f));//JG+
	DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, EpisodeTheme.textColor);//JG mod MG0
	//DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, Fade(EpisodeTheme.textColor, 0.3f));
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
		PlaySound(sound);
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
	//DrawRectangleRec(getBoundingRect(), ColorBrightness(EpisodeTheme.bgColor, -0.35f));
	//DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, Fade(EpisodeTheme.textColor, 0.3f));
	Rectangle pom = getBoundingRect();//JG mod MG0
	DrawRectangleRec({ pom.x - 2.5f * SCALING, pom.y - 2.5f * SCALING, pom.width + 5.0f * SCALING, pom.height + 5.0f * SCALING }, BLACK);//JG mod MG0 kontur
	DrawRectangleRec({ pom.x - 1.5f * SCALING, pom.y - 1.5f * SCALING, pom.width + 3.0f * SCALING, pom.height + 3.0f * SCALING }, EpisodeTheme.textColor);//JG mod MG0
	DrawTexturePro(grafiki->pole1.text, { los_pole_x, los_pole_y, grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, pom, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.75f));//JG+
	DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, EpisodeTheme.textColor);//JG mod MG0
	//DrawTextEx(EpisodeTheme.textFont, text, { (float)x, (float)y }, getFontSizeScaled(), SCALING, Fade(EpisodeTheme.textColor, 0.3f));
}
//void RadioPrzyciskTekst::handleStateChangeConditions()  {//MG0
//	PrzyciskTekst::handleStateChangeConditions();
//	if (activeCondition() && state != NAJECHANY)
//		state = AKTYWNY;
//}
void RadioPrzyciskTekst::handleStateChangeConditions() {
	PrzyciskTekst::handleStateChangeConditions();
	if (activeCondition())//JG mod MG0
		state = AKTYWNY;
}