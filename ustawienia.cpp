#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
namespace ustawienia {
	Przycisk Buttons[] = {
		Przycisk("Powróć", 0, 1, 30, false, [&] {stanGry = StanEkranu::MAIN_MENU;}, true)
	};
	slider Volume("Głośność", 0.25, 0.3, 0.5);
	void drawSettings() {
		ClearBackground(RED);
		helper::DrawTextCentered("Ustawienia", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
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
