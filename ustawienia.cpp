#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
#include <string>
namespace ustawienia {
	sliderHorizontal Volume({ 0.25, 0.7, 0, 0 }, 0.5);

#define LABIRYNTX 0.04
#define QUESTIONX (LABIRYNTX+0.21)
	_Przycisk* Buttons[] = {
		new PrzyciskTekst("Powrot",{0, 1, 0.1, -1.3}, 30, [&] {stanGry = StanEkranu::MAIN_MENU;}),
		// poziom trudności labiryntu
		new RadioPrzyciskTekst("Poczatkujacy", {LABIRYNTX, 0.3, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = '0'; }, [&] {return zmienne->trudnosc_labirynt == '0'; }),
		new RadioPrzyciskTekst("Latwy", {LABIRYNTX, 0.37, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 'l'; }, [&] {return zmienne->trudnosc_labirynt == 'l'; }),
		new RadioPrzyciskTekst("Normalny", {LABIRYNTX, 0.44, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 'n'; }, [&] {return zmienne->trudnosc_labirynt == 'n'; }),
		new RadioPrzyciskTekst("Trudny", {LABIRYNTX, 0.51, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 't'; }, [&] {return zmienne->trudnosc_labirynt == 't'; }),
		new RadioPrzyciskTekst("Mistrzowski", {LABIRYNTX, 0.58, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 'm'; }, [&] {return zmienne->trudnosc_labirynt == 'm'; }),
		// poziomy trudności pytań
		new RadioPrzyciskTekst("Uczen", {QUESTIONX, 0.3, 0, 0}, 26, [&] {zmienne->trudnosc_pytania = '2'; }, [&] {return zmienne->trudnosc_pytania == '2'; }),
		new RadioPrzyciskTekst("Odkrywca", {QUESTIONX, 0.37, 0, 0}, 26, [&] {zmienne->trudnosc_pytania = '6'; }, [&] {return zmienne->trudnosc_pytania == '6'; }),
		new RadioPrzyciskTekst("Ekspert", {QUESTIONX, 0.44, 0, 0}, 26, [&] {zmienne->trudnosc_pytania = 's'; }, [&] {return zmienne->trudnosc_pytania == 's'; }),
	};
	std::string volstr;
	//RadioPrzycisk lowVol("VOL<50", 0.25, 0.4, 30, BUTTON_NONE, [&] {Volume.change(25); }, [&] {return Volume.value < 50; });
	//RadioPrzycisk hiVol("VOL>50", 0.55, 0.4, 30, BUTTON_NONE, [&] {Volume.change(75); }, [&] {return Volume.value >= 50; });
	void initSettings() {
		Volume.value = (zmienne->glosnosc)/100;
		volstr = "Glosnosc: " + std::to_string(static_cast<int>(Volume.value*100)) + "%";
		Volume.onChange = [&](float changed) {
			volstr = "Glosnosc: " + std::to_string(static_cast<int>(changed*100)) + "%";
			zmienne->glosnosc = changed * 100;
			};
	}
	void drawSettings() {
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
		}
		else {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
		}
		DrawRectangleRec({ szer * 0.005f, wys * 0.005f, szer * 0.99f, wys * 0.99f }, Fade(EpisodeTheme.bgColor, 0.5));
		helper::DrawTextCentered("Ustawienia", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
		DrawText("Poziomy Trudnosci", GetScreenWidth() * LABIRYNTX, GetScreenHeight() * 0.2, 30, WHITE);
		DrawText("Labiryntu:", GetScreenWidth() * LABIRYNTX, GetScreenHeight() * 0.25, 26, WHITE);
		DrawText("Pytan:", GetScreenWidth() * QUESTIONX, GetScreenHeight() * 0.25, 26, WHITE);
		DrawText(volstr.c_str(), GetScreenWidth() * 0.3, GetScreenHeight() * 0.65, 20, WHITE);
		for (auto& b : Buttons) {
			b->draw();
		}
		Volume.draw();
	}

	void updateSettings() {
		for (auto& b : Buttons) {
			b->update();
		}
		Volume.update();
	}
}
