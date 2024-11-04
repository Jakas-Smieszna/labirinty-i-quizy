#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
#include "instrukcja.h"
#include "DivideText.h"

namespace instrukcja {
	Przycisk Buttons[] = {
		Przycisk("Powróæ", 0, 1, 30, false, [&] {stanGry = StanEkranu::MAIN_MENU; }, true)
	};
	void drawInstruction() {
		ClearBackground(BLUE);
		helper::DrawTextCentered("Instrukcja", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
		double height = 0.20;
		vector<string> lines = DivideText("Instrukcja.txt");
		for (int i = 0; i < 14 && i<lines.size(); i++)
		{
			DrawText(lines[i].c_str(), 10, GetScreenHeight() * (height + 0.05*i), 20, BLACK);
		}
		for (auto& b : Buttons) {
			b.draw();
		}
	}

	void updateInstruction() {
		for (auto& b : Buttons) {
			b.update();
		}
	}
}