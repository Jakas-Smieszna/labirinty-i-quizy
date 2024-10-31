#pragma once
#include "raylib.h"

#define OknoSzerBaz 1080
#define OknoWysBaz 720
#define M_PI 3.141592653589793 //JG:ta biblioteczne niegdy mi nie dzialala :(

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

	void aktualizuj_tlo(char epizod) {
		switch (epizod) {
		default:
		case 1://JG:EP 1
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo1.png"), 1920.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
			break;
		case 2://JG:EP 2
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo2.png"), 1920.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
			break;
		case 3://JG:EP 3
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo3.png"), 1461.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
			break;
		case 4://JG:EP 4
			UnloadTexture(tlo.text);
			tlo = grafika(LoadTexture("Grafika1/Tlo4.png"), 1640.0f, 1080.0f);
			UnloadTexture(puchar.text);
			puchar = grafika(LoadTexture("Grafika1/Puchar2.png"), 280.0f, 494.0f);
			break;
		}
	}

	GRAFIKI() {
		ikona = LoadImage("Grafika1/ikona1.png");
	
		/*tlo = grafika(LoadImage("Grafika1/Tlo3.png"));*/
		tlo = grafika(LoadTexture("Grafika1/Tlo1.png"), 1920.0f, 1080.0f);
		/*tlo.text = LoadTexture("Grafika1/Tlo3.png");
		tlo.szer = 1461.0f;
		tlo.wys = 1080.0f;*/
		puchar = grafika(LoadTexture("Grafika1/Puchar1.png"), 293.0f, 471.0f);
	}

	void D_GRAFIKI() {//JG:destruktor to ZLO
		if(IsImageReady(ikona)) UnloadImage(ikona);

		tlo.D_grafika();
		puchar.D_grafika();
	}

};