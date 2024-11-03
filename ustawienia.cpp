#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
#include <string>
namespace ustawienia {
	int volume = 35;
	sliderHorizontal Volume({ 0.25, 0.7, 0, 0 }, 0.5);

#define LABIRYNTX 0.04
#define QUESTIONX (LABIRYNTX+0.21)
	_Przycisk* Buttons[] = {
		new PrzyciskTekst("Powróć",{0, 1, 0.1, -1.3}, 30, [&] {stanGry = StanEkranu::MAIN_MENU;}),
		// poziom trudności labiryntu
		new RadioPrzyciskTekst("Początkujący", {LABIRYNTX, 0.3, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = '0'; }, [&] {return zmienne->trudnosc_labirynt == '0'; }),
		new RadioPrzyciskTekst("Łatwy", {LABIRYNTX, 0.37, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 'l'; }, [&] {return zmienne->trudnosc_labirynt == 'l'; }),
		new RadioPrzyciskTekst("Normalny", {LABIRYNTX, 0.44, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 'n'; }, [&] {return zmienne->trudnosc_labirynt == 'n'; }),
		new RadioPrzyciskTekst("Trudny", {LABIRYNTX, 0.51, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 't'; }, [&] {return zmienne->trudnosc_labirynt == 't'; }),
		new RadioPrzyciskTekst("Mistrzowski", {LABIRYNTX, 0.58, 0, 0}, 26, [&] {zmienne->trudnosc_labirynt = 'm'; }, [&] {return zmienne->trudnosc_labirynt == 'm'; }),
		// poziomy trudności pytań
		new RadioPrzyciskTekst("Uczeń", {QUESTIONX, 0.3, 0, 0}, 26, [&] {zmienne->trudnosc_pytania = '2'; }, [&] {return zmienne->trudnosc_pytania == '2'; }),
		new RadioPrzyciskTekst("Odkrywca", {QUESTIONX, 0.37, 0, 0}, 26, [&] {zmienne->trudnosc_pytania = '6'; }, [&] {return zmienne->trudnosc_pytania == '6'; }),
		new RadioPrzyciskTekst("Ekspert", {QUESTIONX, 0.44, 0, 0}, 26, [&] {zmienne->trudnosc_pytania = 's'; }, [&] {return zmienne->trudnosc_pytania == 's'; }),
	};
	std::string volstr;
	//RadioPrzycisk lowVol("VOL<50", 0.25, 0.4, 30, BUTTON_NONE, [&] {Volume.change(25); }, [&] {return Volume.value < 50; });
	//RadioPrzycisk hiVol("VOL>50", 0.55, 0.4, 30, BUTTON_NONE, [&] {Volume.change(75); }, [&] {return Volume.value >= 50; });
	void initSettings() {
		Volume.value = static_cast<float>(volume)/100;
		volstr = "Głośność: " + std::to_string(static_cast<int>(Volume.value*100)) + "%";
		Volume.onChange = [&](float changed) {
			volstr = "Głośność: " + std::to_string(static_cast<int>(changed*100)) + "%";
			};
	}
	void drawSettings() {
		ClearBackground(RED);
		helper::DrawTextCentered("Ustawienia", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
		DrawText("Poziomy Trudności", GetScreenWidth() * LABIRYNTX, GetScreenHeight() * 0.2, 30, WHITE);
		DrawText("Labiryntu:", GetScreenWidth() * LABIRYNTX, GetScreenHeight() * 0.25, 26, WHITE);
		DrawText("Pytań:", GetScreenWidth() * QUESTIONX, GetScreenHeight() * 0.25, 26, WHITE);
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
