#include "przycisk.h"
#include <vector>
#include <string>
#include "wybor_poziomu.h"
#include "raylib.h"
#include "Grafika.h"
#include "funkcjePomocnicze.h"
#include "gamestate.h"

namespace wybor_poziomu {
    _Przycisk* Buttons[] = {
        /*
        new RadioPrzyciskTekst("Poziom 1", {0.14, 0.3}, { 0.2, 0.1 }, [&] {zmienne->poziom = 1; zmienne->epizod_doc = 1; }, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 11; }),
        new RadioPrzyciskTekst("Poziom 2", {0.14, 0.4}, { 0.2, 0.1 }, [&] {zmienne->poziom = 2;zmienne->epizod_doc = 1;}, [&] {return zmienne->poziom+10*zmienne->epizod_doc == 12;}),
        new RadioPrzyciskTekst("Poziom 3", {0.14, 0.5}, { 0.2, 0.1 }, [&] {zmienne->poziom = 3;zmienne->epizod_doc = 1;}, [&] {return zmienne->poziom+10*zmienne->epizod_doc == 13;}),
        new RadioPrzyciskTekst("Poziom 4", {0.14, 0.6}, { 0.2, 0.1 }, [&] {zmienne->poziom = 4;zmienne->epizod_doc = 1;}, [&] {return zmienne->poziom+10*zmienne->epizod_doc == 14;}),
        new RadioPrzyciskTekst("Poziom 5", {0.14, 0.7}, { 0.2, 0.1 }, [&] {zmienne->poziom = 5;zmienne->epizod_doc = 1;}, [&] {return zmienne->poziom+10*zmienne->epizod_doc == 15;}),

        new RadioPrzyciskTekst("Poziom 1", {0.34, 0.3}, { 0.2, 0.1 }, [&] {zmienne->poziom = 1;zmienne->epizod_doc = 2;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 21;}),
        new RadioPrzyciskTekst("Poziom 2", {0.34, 0.4}, { 0.2, 0.1 }, [&] {zmienne->poziom = 2;zmienne->epizod_doc = 2;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 22;}),
        new RadioPrzyciskTekst("Poziom 3", {0.34, 0.5}, { 0.2, 0.1 }, [&] {zmienne->poziom = 3;zmienne->epizod_doc = 2;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 23;}),
        new RadioPrzyciskTekst("Poziom 4", {0.34, 0.6}, { 0.2, 0.1 }, [&] {zmienne->poziom = 4;zmienne->epizod_doc = 2;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 24;}),
        new RadioPrzyciskTekst("Poziom 5", {0.34, 0.7}, { 0.2, 0.1 },, [&] {zmienne->poziom = 5;zmienne->epizod_doc = 2;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 25;}),

        new RadioPrzyciskTekst("Poziom 1", {0.54, 0.3}, { 0.2, 0.1 }, [&] {zmienne->poziom = 1;zmienne->epizod_doc = 3;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 31;}),
        new RadioPrzyciskTekst("Poziom 2", {0.54, 0.4}, { 0.2, 0.1 }, [&] {zmienne->poziom = 2;zmienne->epizod_doc = 3;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 32;}),
        new RadioPrzyciskTekst("Poziom 3", {0.54, 0.5}, { 0.2, 0.1 }, [&] {zmienne->poziom = 3;zmienne->epizod_doc = 3;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 33;}),
        new RadioPrzyciskTekst("Poziom 4", {0.54, 0.6}, { 0.2, 0.1 }, [&] {zmienne->poziom = 4;zmienne->epizod_doc = 3;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 34;}),
        new RadioPrzyciskTekst("Poziom 5", {0.54, 0.7}, { 0.2, 0.1 }, [&] {zmienne->poziom = 5;zmienne->epizod_doc = 3;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 35;}),

        new RadioPrzyciskTekst("Poziom 1", {0.74, 0.3}, { 0.2, 0.1 }, [&] {zmienne->poziom = 1;zmienne->epizod_doc = 4;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 41;}),
        new RadioPrzyciskTekst("Poziom 2", {0.74, 0.4}, { 0.2, 0.1 }, [&] {zmienne->poziom = 2;zmienne->epizod_doc = 4;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 42;}),
        new RadioPrzyciskTekst("Poziom 3", {0.74, 0.5}, { 0.2, 0.1 }, [&] {zmienne->poziom = 3;zmienne->epizod_doc = 4;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 43;}),
        new RadioPrzyciskTekst("Poziom 4", {0.74, 0.6}, { 0.2, 0.1 }, [&] {zmienne->poziom = 4;zmienne->epizod_doc = 4;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 44;}),
        new RadioPrzyciskTekst("Poziom 5", {0.74, 0.7}, { 0.2, 0.1 }, [&] {zmienne->poziom = 5;zmienne->epizod_doc = 4;}, [&] {return zmienne->poziom + 10 * zmienne->epizod_doc == 45;}),
        */
        new PrzyciskTekst("Powrot",{0, 8}, {0, 0.2}, [&] {stanGry = StanEkranu::MAIN_MENU; })
        /*
        new PrzyciskTekst("QUIZ", {0.37, 0.85, 0, 0}, 20, [&] {stanGry = StanEkranu::GRA_QUIZ; }),
        new PrzyciskTekst("LABIRYNT", {0.54, 0.85, 0, 0}, 20, [&] {stanGry = StanEkranu::GRA_LABIRYNT; })
        */

    };

    void drawLevelMenu() {
        float szer = (float)GetScreenWidth();
        float wys = (float)GetScreenHeight();
        if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
            DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
        }
        else {
            DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
        }
        DrawRectangleRec({ szer * 0.005f, wys * 0.005f, szer * 0.99f, wys * 0.99f }, Fade(EpisodeTheme.bgColor, 0.5));
        helper::DrawTextCentered("Wybierz Poziom:", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 40, WHITE);
        helper::DrawTextCentered("Rozdzial I:", GetScreenWidth() / 5, GetScreenHeight() * 0.10 + 80, 20, WHITE);
        helper::DrawTextCentered("Rozdzial II:", 2 * GetScreenWidth() / 5, GetScreenHeight() * 0.10 + 80, 20, WHITE);
        helper::DrawTextCentered("Rozdzial III:", 3 * GetScreenWidth() / 5, GetScreenHeight() * 0.10 + 80, 20, WHITE);
        helper::DrawTextCentered("Rozdzial IV:", 4 * GetScreenWidth() / 5, GetScreenHeight() * 0.10 + 80, 20, WHITE);
        for (auto& B : Buttons) {
            B->draw();
        }
    }

    void updateLevelMenu() {
        for (const auto& B : Buttons) {
            B->update();
        }
    }
}