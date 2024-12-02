#include "credits.h"
#include "gamestate.h"
#include "przycisk.h"

namespace credits {
	_Przycisk* Buttons[] = {
		new PrzyciskTekst("Powróć",{0, 8}, {0, 0.2}, [&] {stanGry = StanEkranu::MAIN_MENU; })
	};

	void drawCredits() {
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		float scale = 1.f;
		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			scale = (float)GetScreenHeight() / OknoWysBaz;
		}
		else {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			scale = (float)GetScreenWidth() / OknoSzerBaz;
		}
		DrawRectangleRec({ szer * 0.005f, wys * 0.005f, szer * 0.99f, wys * 0.99f }, Fade(EpisodeTheme.bgColor, 0.5));

		DrawText("Projekt stworzony przez studentow Informatyki Technicznej", szer * 0.025, wys * 0.05, scale * 30, WHITE);
		DrawText("Akademii Gorniczo-Hutniczej w Krakowie jako projekt zaliczeniowy", szer * 0.025, wys * 0.1, scale * 30, WHITE);
		DrawText("na przedmiot \"Inzynieria Oprogramowania\".", szer * 0.025, wys * 0.15, scale * 30, WHITE);
		DrawText("Zespol M. Fido/J. Gas/M. Gladysiak/A. Grudniok", szer * 0.025, wys * 0.2, scale * 30, WHITE);
		DrawText("W naszym projekcie wykorzystalismy biblioteke \"Raylib\" (raylib.com). ", szer * 0.025, wys * 0.3, scale * 30, WHITE);
		
		for (auto& b : Buttons) {
			b->draw();
		}

	}
	void updateCredits() {
		for (auto& b : Buttons) {
			b->update();
		}
	}
}