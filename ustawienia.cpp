#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
#include <string>
namespace ustawienia {
	Przycisk Buttons[] = {
		Przycisk("Powróć", 0, 1, 30, false, [&] {stanGry = StanEkranu::MAIN_MENU;}, true)
	};
	std::string volstr;
	int volume = 35;
	slider Volume("Głośność", 0.25, 0.3, 0.5);
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
