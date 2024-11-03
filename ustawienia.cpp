#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
#include <string>
namespace ustawienia {
	int volume = 35;
	PrzyciskTekst Buttons[] = {
		PrzyciskTekst("Powróć",{0, 1, 0, -1}, 30, [&] {stanGry = StanEkranu::MAIN_MENU;}),
		PrzyciskTekst("VOL", {0.2, 0.7,0,0}, 30, [&] {volume = 64; })
	};
	std::string volstr;
	sliderHorizontal Volume({ 0.25, 0.3, 0, 0 }, 0.5);
	//RadioPrzycisk lowVol("VOL<50", 0.25, 0.4, 30, BUTTON_NONE, [&] {Volume.change(25); }, [&] {return Volume.value < 50; });
	//RadioPrzycisk hiVol("VOL>50", 0.55, 0.4, 30, BUTTON_NONE, [&] {Volume.change(75); }, [&] {return Volume.value >= 50; });
	void initSettings() {
		Volume.value = volume;
		volstr = "Głośność: " + std::to_string(static_cast<int>(Volume.value)) + "%";
		Volume.onChange = [&](float changed) {
			volstr = "Głośność: " + std::to_string(static_cast<int>(changed)) + "%";
			};
	}
	void drawSettings() {
		ClearBackground(RED);
		helper::DrawTextCentered("Ustawienia", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
		DrawText(volstr.c_str(), GetScreenWidth() * 0.25, GetScreenHeight() * 0.35, 20, BLACK);
		for (auto& b : Buttons) {
			b.draw();
		}
		Volume.draw();
	}

	void updateSettings() {
		for (auto& b : Buttons) {
			b.update();
		}
		Volume.update();
	}
}
