#pragma once
#include "raylib.h"

#define OknoSzerBaz 1080
#define OknoWysBaz 720

//JG:OBIEKT GRAFICZNY Z ROZNYMI DANYMI
class grafika {
public:
	Texture2D text;
	float szer;
	float wys;
	/*grafika(Image imag0) {
		text = LoadTextureFromImage(imag0);
		Rectangle pom = GetImageAlphaBorder(imag0, 1.0f);
		szer = pom.width;
		wys = pom.height;
	}*/
	grafika(Texture2D text0, float s0, float w0) {
		text = text0;
		//Rectangle pom = GetImageAlphaBorder(imag0, 1000.0f);
		szer = s0;
		wys = w0;
	}
	grafika() {
		text = LoadTextureFromImage(GenImageColor(1.0f, 1.0f, WHITE));
		szer = 0.0f;
		wys = 0.0f;
	}
	void D_grafika() {//JG:destruktor to ZLO
		if (IsTextureReady(text)) UnloadTexture(text);
	}
};

//JG:LISTA UZYWANYCH GRAFIK
class GRAFIKI {
public:
	Image ikona;

	grafika tlo;
	grafika puchar;
	grafika pole1;
	grafika wiatrak1;
	grafika jez1;
	grafika awatar;

	void aktualizuj_tlo(char epizod) {
		switch (epizod) {
		default:
		case 1://JG:EP 1
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo1.png"), 1920.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
			UnloadTexture(pole1.text);
			pole1 = grafika(LoadTexture("Grafika1/Pole1.png"), 1000.0f, 1000.0f);
			UnloadTexture(wiatrak1.text);
			wiatrak1 = grafika(LoadTexture("Grafika1/Wiatrak11.png"), 1000.0f, 1000.0f);
			UnloadTexture(jez1.text);
			jez1 = grafika(LoadTexture("Grafika1/Jez1.png"), 500.0f, 500.0f);
			break;
		case 2://JG:EP 2
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo2.png"), 1920.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
			UnloadTexture(pole1.text);
			pole1 = grafika(LoadTexture("Grafika1/Pole2.png"), 1000.0f, 1000.0f);
			UnloadTexture(wiatrak1.text);
			wiatrak1 = grafika(LoadTexture("Grafika1/Wiatrak21.png"), 1000.0f, 1000.0f);
			UnloadTexture(jez1.text);
			jez1 = grafika(LoadTexture("Grafika1/Jez2.png"), 500.0f, 500.0f);
			break;
		case 3://JG:EP 3
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo3.png"), 1461.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
			UnloadTexture(pole1.text);
			pole1 = grafika(LoadTexture("Grafika1/Pole3.png"), 1000.0f, 1000.0f);
			UnloadTexture(wiatrak1.text);
			wiatrak1 = grafika(LoadTexture("Grafika1/Wiatrak31.png"), 1000.0f, 1000.0f);
			UnloadTexture(jez1.text);
			jez1 = grafika(LoadTexture("Grafika1/Jez3.png"), 500.0f, 500.0f);
			break;
		case 4://JG:EP 4
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo4.png"), 1640.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar2.png"), 280.0f, 494.0f);
			UnloadTexture(pole1.text);
			pole1 = grafika(LoadTexture("Grafika1/Pole4.png"), 1000.0f, 1000.0f);
			UnloadTexture(wiatrak1.text);
			wiatrak1 = grafika(LoadTexture("Grafika1/Wiatrak41.png"), 1000.0f, 1000.0f);
			UnloadTexture(jez1.text);
			jez1 = grafika(LoadTexture("Grafika1/Jez4.png"), 500.0f, 500.0f);
			break;
		}
	}

	GRAFIKI() {
		ikona = LoadImage("Grafika1/Ikona2.png");
	
		/*tlo = grafika(LoadImage("Grafika1/Tlo3.png"));*/
		tlo = grafika(LoadTexture("Grafika1/Tlo1.png"), 1920.0f, 1080.0f);
		/*tlo.text = LoadTexture("Grafika1/Tlo3.png");
		tlo.szer = 1461.0f;
		tlo.wys = 1080.0f;*/
		puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
		pole1 = grafika(LoadTexture("Grafika1/Pole1.png"), 1000.0f, 1000.0f);
		wiatrak1 = grafika(LoadTexture("Grafika1/Wiatrak11.png"), 1000.0f, 1000.0f);
		jez1 = grafika(LoadTexture("Grafika1/Jez1.png"), 500.0f, 500.0f);
		awatar = grafika(LoadTexture("Grafika1/Kotel1.png"), 334.0f, 433.0f);
	}

	void D_GRAFIKI() {//JG:destruktor daje mniejsza kontrole ze wzgledu na automatyczna aktywacje
		if(IsImageReady(ikona)) UnloadImage(ikona);

		tlo.D_grafika();
		puchar.D_grafika();
		pole1.D_grafika();
		wiatrak1.D_grafika();
		jez1.D_grafika();
		awatar.D_grafika();
	}

};

extern GRAFIKI* grafiki;

struct Theme {
	Color textColor;
	Color borderColor;
	Color bgColor;
	Font textFont;
	bool fontInit = false;
	Theme() { textColor = borderColor = bgColor = BLACK; LoadFontEx("resources/arial.ttf", 32, nullptr, 0);; }
	void Update(int episodenum) {
		switch (episodenum) {
		default:
		case 1:
			bgColor = BROWN;
			textColor = YELLOW;
			break;
		case 2:
			bgColor = DARKGREEN;
			textColor = ColorBrightness(SKYBLUE, 0.15f);
			break;
		case 3:
			bgColor = DARKGRAY;
			textColor = RED;
			break;
		case 4:
			bgColor = BLACK;
			textColor = WHITE;
			break;
		}
		if (!fontInit) {
			fontInit = true;
			textFont = GetFontDefault();
			//textFont = LoadFont("Fonts/Inconsolata/static/Inconsolata_Expanded-Medium.ttf");
			//SetTextureFilter(textFont.texture, TEXTURE_FILTER_BILINEAR);
		}
	}
	~Theme() {
		UnloadFont(textFont);
	}
};

// szata epizodu; do przycisków, głównie.
extern Theme EpisodeTheme;