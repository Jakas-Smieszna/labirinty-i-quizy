#pragma once
#include "raylib.h"
namespace helper {
	// Funkcja rysuje tekst tak, aby "środek" tekstu był na posX.
	// Łatwe centrowanie tekstu horyzontalnie. Troche jak środkowanie paragrafu w Wordzie ale nie do końca.
	// Wywołuj: `helper::DrawTextCentered(...)`
	// ... no bo namespace
	inline void DrawTextCentered(const char *text, int posX, int posY, int fontSize, Color color) {
		int txtWidth = MeasureText(text, fontSize);
		DrawText(text, posX - txtWidth/2, posY, fontSize, color);
	}
	// Rysuje tekst z jakimś kolorem tła.
	// Padding pozwala zwiększenie obszaru z takim kolorem tła o kilka pikseli,
	// aby tekst nie wyglądał zbyt nienaturalnie.
	inline void DrawTextBackgroundColor(const char* text, int posX, int posY, int fontSize, Color color, Color background, int padding = 1) {
		DrawRectangle(posX - padding, posY - padding, MeasureText(text, fontSize) + 2*padding, fontSize + 2*padding, background);
		DrawText(text, posX, posY, fontSize, color);
	}
	// DrawTextCentered(), ale z tłem.
	inline void DrawTextCenteredBackgroundColor(const char* text, int posX, int posY, int fontSize, Color color, Color background, int padding = 1) {
		int txtWidth = MeasureText(text, fontSize);
		DrawTextBackgroundColor(text, posX - txtWidth / 2, posY, fontSize, color, background, padding);
	}
	// Pozwala sprawdzić, czy dany punkt (posX, posY)
	// jest na danym tekście.
	// areaXstart, areaYstart - lewy górny róg prostokąta
	// areaXend, areaYend - prawy dolny róg prostokąta
	// posX, posY - odpowiednio X i Y badanego punktu.
	// zwraca `false` jeżeli nie jest, a `true` jeżeli jest (jak, zakładam, się domyśleliście)
	inline bool IsInArea(int areaXstart, int areaYstart, int areaXend, int areaYend, int posX, int posY) {
		if (posX < areaXstart || posX > areaXend || posY < areaYstart || posY > areaYend)
			return false; // nie jest to raczej w naszym prostokącie

		return true; // jak powyższy if nie przeszedł to jest git
	}
	// Pozwala sprawdzić, czy dany punkt (posX, posY)
	// jest na danym tekście.
	// const char* text - ww. dany tekst
	// int textX, int textY - pozycja ww. danego tekstu
	// int fontSize - rozmiar czcionki ww. danego tekstu
	// int posX, int posY - rozmiar ww. danego punktu
	inline bool IsInTextArea(const char* text, int textX, int textY, int fontSize, int posX, int posY) {
		int txtWidth = MeasureText(text, fontSize);
		return IsInArea(textX, textY, textX + txtWidth, textY + fontSize, posX, posY);
	}
	// Pozwala sprawdzić, czy dany punkt (posX, posY)
	// jest na danym wyśrodkowanym tekście.
	// const char* text - ww. dany wyśrodkowany tekst
	// int textX, int textY - pozycja ww. danego wyśrodkowanego tekstu
	// int fontSize - rozmiar czcionki ww. danego wyśrodkowanego tekstu
	// int posX, int posY - rozmiar ww. danego punktu
	inline bool IsInTextAreaCentered(const char* text, int textX, int textY, int fontSize, int posX, int posY) {
		int txtWidth = MeasureText(text, fontSize);
		return IsInArea(textX - txtWidth/2, textY, textX + txtWidth/2, textY + fontSize, posX, posY);
	}
}