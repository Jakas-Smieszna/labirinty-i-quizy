#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "Grafika.h"
#include "gamestate.h"
#include "przycisk.h"
#include "wybor_uzytkownika.h"
#include <string>
#include <vector>

namespace wybor_uzytkownika {
		_Przycisk* Buttons[] = {
		new PrzyciskTekst("Powróæ",{0, 1, 0.1, -1.3}, 30, [&] {stanGry = StanEkranu::MAIN_MENU; }),
		new RadioPrzyciskTekst(zmienne->users[0].c_str(),{0.5, 0.2, -0.5, -0.5}, 30, [&] {zmienne->nazwa_uzytkownika = zmienne->users[0]; }, [&] {return zmienne->nazwa_uzytkownika == zmienne->users[0]; }),
		new RadioPrzyciskTekst(zmienne->users[1].c_str(),{0.5, 0.3, -0.5, -0.5}, 30, [&] {zmienne->nazwa_uzytkownika = zmienne->users[1]; }, [&] {return zmienne->nazwa_uzytkownika == zmienne->users[1]; }),
		new RadioPrzyciskTekst(zmienne->users[2].c_str(),{0.5, 0.4, -0.5, -0.5}, 30, [&] {zmienne->nazwa_uzytkownika = zmienne->users[2]; }, [&] {return zmienne->nazwa_uzytkownika == zmienne->users[2]; }),
		new RadioPrzyciskTekst(zmienne->users[3].c_str(),{0.5, 0.5, -0.5, -0.5}, 30, [&] {zmienne->nazwa_uzytkownika = zmienne->users[3]; }, [&] {return zmienne->nazwa_uzytkownika == zmienne->users[3]; }),
		new RadioPrzyciskTekst(zmienne->users[4].c_str(),{0.5, 0.6, -0.5, -0.5}, 30, [&] {zmienne->nazwa_uzytkownika = zmienne->users[4]; }, [&] {return zmienne->nazwa_uzytkownika == zmienne->users[4]; }),
	};

	void drawUserMenu() {
		ClearBackground(DARKGREEN);
		helper::DrawTextCentered("Wybierz uzytkownika:", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 40, WHITE);
		for (auto& B : Buttons) {
			B->draw();
		}
	}
	void updateUserMenu() {
		for (auto& B : Buttons) {
			B->update();
		}
	}
}