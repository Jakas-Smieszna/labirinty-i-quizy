#include "credits.h"
#include "gamestate.h"
#include "przycisk.h"

namespace credits {
	_Przycisk* Buttons[] = {
		new PrzyciskTekst("Powróć",{0, 1, 0.1, -1.3}, 30, [&] {stanGry = StanEkranu::MAIN_MENU; })
	};

	void drawCredits() {
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
		}
		else {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
		}
		DrawRectangleRec({ szer * 0.005f, wys * 0.005f, szer * 0.99f, wys * 0.99f }, Fade(EpisodeTheme.bgColor, 0.5));
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