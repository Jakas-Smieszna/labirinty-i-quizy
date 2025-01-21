#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
#include "instrukcja.h"
#include "DivideText.h"
#include <string>

#define SLAJDY 9

namespace instrukcja {

	/*_Przycisk* Buttons[] = {
		new PrzyciskTekst("Powrot",{0, 1, 0.1, -1.3}, 30, [&] {stanGry = StanEkranu::MAIN_MENU; }),

	};
	void drawInstruction() {
		ClearBackground(BLUE);
		helper::DrawTextCentered("Instrukcja", GetScreenWidth() / 2, GetScreenHeight() * 0.10, 30, WHITE);
		double height = 0.20;
		vector<string> lines = DivideText("Instrukcja.txt");
		for (int i = 0; i < 14 && i<lines.size(); i++)
		{
			DrawText(lines[i].c_str(), 10, GetScreenHeight() * (height + 0.05 * i), 20, BLACK);
		}
		for (auto& b : Buttons) {
			b->draw();
		}
	}

	void updateInstruction() {
		for (auto& b : Buttons) {
			b->update();
		}
	}MF*/


	//JG:
	void drawInstruction() {

		if (zmienne->kurosr_czulosc == 0) SetMouseCursor(1);
		else if (zmienne->kurosr_czulosc > 0) zmienne->kurosr_czulosc = zmienne->kurosr_czulosc - 1;
		else zmienne->kurosr_czulosc = 0;

		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		float Skala_liter = 1.f;

		if (szer >= wys * grafiki->tlo.szer / grafiki->tlo.wys) {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, szer, szer * grafiki->tlo.wys / grafiki->tlo.szer }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = (float)GetScreenHeight() / OknoWysBaz;
		}
		else {
			DrawTexturePro(grafiki->tlo.text, { 0.0f, 0.0f, grafiki->tlo.szer, grafiki->tlo.wys }, { 0.0f, 0.0f, wys * grafiki->tlo.szer / grafiki->tlo.wys, wys }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, -0.25f));
			Skala_liter = (float)GetScreenWidth() / OknoSzerBaz;
		}
		if (700.0f * Skala_liter > wys) Skala_liter = Skala_liter = wys / OknoWysBaz;//JG: przy wyjatkowo wrednym skalowaniu okna bez tego zabezpieczenia zawartosc moze "rozszerzyc" sie poza okno. Dotyczy duzych paneli

		float szer_pom = 880.0f * Skala_liter;
		float wys_pom = 620.0f * Skala_liter;
		char* napis_pom = NULL;
		char* napis_pom2 = NULL;

		switch (zmienne->biezacy_etap) {
		default:
		case 0:
			napis_pom = "Przygoda wzywa!";
			napis_pom2 = "Niespodziewanie budzisz sie w obcym sobie miejscu. Szybko rozgladasz sie. Otacza cie wielka, otwarta przestrzen. Wtedy dostrzegasz sciezke, na ktorej stoisz. To labirynt! Tylko taki bez scian. Czujesz, ze musisz sie stad wszybko wydostac!\nCelem gry jest przejsc wszystkie labirynty i quizy aby powrocic do macierzystego swiata. Czeka cie jednak 20 pelnych wyzwan poziomow. Kazdy poziom sklada sie z 1 lub kilku quizow i labiryntow. Aby zmienic poziom trudnosci, wejdz w ustawienia w menu glownym. Do zaliczenia quizow musisz zebrac odpowiednia lczbe punktow za poprawne odpowiedzi w ograniczonej liczbie prob. Aby przejsc labirynt musisz przejsc od pola start (lub wejscie) do pola meta (drzwi) unikajac po drodze kolczatek i wiatrakow, a takze probujac nie spasc (nie schodzac ze sciezki), Aby sie przemieszczac w labiryncie, uzyj myszy. Ruch kursorem bedzie odpowiednio odzwierciedlany ruchem twojego awatara na planszy. Warto wykonywac delikatne, kontrolowane ruchy. Aby sie wspomoc w sterowaniu uzyj klawisza Q do zatrzymywania i wznawiania gry. Pauza to dobry sposob, by bez ruchu na planszy przesunac kursor w dogodniejsze wzgledem nastepnych ruchow miejsce. Na panelach u gory i po prawej znajdziesz dodatkowe informacje o stanie rozgrywki (np. twoj wynik czy pozostale cofniecia). Niezaleznie od tego czy na mysl o zblizajacej sie wedrowce przechodza cie ciary, czy ekscytacja, powodzenia wedrowcze!\0";
			break;
		case 1:
			napis_pom = "Poziomy trudnosci";
			napis_pom2 = "Przed rozpoczeciem gry mozesz zmienic poziom trudnosci w ustawieniach (sekcje mozesz wybrac w menu glownym). Poziom trudnosci sklada sie na 2 skladowe - trudnosc labiryntu i quizu:\nTrudnosc labiryntu:\nPoczatkujacy: -30% do tempa obrotu i ladowania wiatrakow oraz szybkosci opuszczania pozycji kolczatek. +30% do opoznienia w czasie wszystkich etapow znikania i pojawiania sie.\nLatwy: -15% do tempa obrotu i ladowania wiatrakow oraz szybkosci opuszczania pozycji kolczatek. +15% do opoznienia w czasie wszystkich etapow znikania i pojawiania sie.\nNormalny: normalne tempo akcji.\nTrudny: +5% do tempa obrotu i ladowania wiatrakow oraz szybkosci opuszczania pozycji kolczatek. -5% do opoznienia w czasie wszystkich etapow znikania i pojawiania sie.\nMistrzowski: +10% do tempa obrotu i ladowania wiatrakow oraz szybkosci opuszczania pozycji kolczatek. -10% do opoznienia w czasie wszystkich etapow znikania i pojawiania sie.\nTrudnosc quizu:\nUczen: pytania dedykowane osobom mlodszym.\nOdkrywca: pytania dedykowane osobom o przecientnej wiedzy.\nEkspert: pytania dedykowane osobom o bardziej zaawansowanej wiedzy lub szukajocym wiekszego wyzwania.\0";
			break;
		case 2:
			napis_pom = "Rozgrywka - dane I";
			napis_pom2 = "W trakcie rozgrywki znajdziesz na panelach rozne parametry:\nGorny panel:\nEpizod, poziom, trudnosc - informacje o numerze poziomu i epizodu oraz wybrany poziom trudnosci.\nCzas - ilosc czasu, ktora uplynela od rozpoczecia poziomu (w sekundach).\nPrawy panel dla labiryntu:\nWyniki - podaje twoj biezacy wynik oraz rekordy ustanowione na danym poziomie (przy obowiazujacej trudnosci). Wartosc w nawiasie to obecny wynik podstawiony do ostatecznej premi za ukonczenie poziomu (wartosc jaka mialby po ukonczeniu poziomu).\nRuch [Q] - jak wlaczany to ruch po labiryncie jest aktywny, mija tez czas rozgrywki. Wylaczony - mozna ruszac kursorem bez przesuwania sie po labiryncie, a czas jest zatrzymany.\nLimit czasu - jesli czas gry przekroczy ta wartosc, natychmiast przegrasz.\nCofniecia - gdy zostaniesz zbity lub spadniesz cofasz sie do punktu kontrolnego placac 1 cofnieciem. Parametr pokazuje uzyta/maksymalna ilosc. Jesli cofniecia sie wyczerpia, przegrywasz.\nCzas i wynik PK - pokazuje czas i wynik jakie zostana przywrocone po cofnieciu do punktu kontrolnego. Wynik uwzglednia kare za kolejne cofniecie.\0";
			break;
		case 3:
			napis_pom = "Rozgrywka - dane II";
			napis_pom2 = "";
			break;
		case 4:
			napis_pom = "Rozgrywka - dane III";
			napis_pom2 = "Prawy panel - quiz (tylko dane odmienne od tych z panelu labiryntu):\nWyzwanie - okresla zagrozenie w razie niepowodzenia quizu:\n-> Bezpieczny - w razie porazki mozesz przystapic do quizu ponownie kosztem paru punktow (ale nie cofniec).\n-> Pulapka - w razie porazki zostajeszz cofniety/a do punktu kontrolnego (kosztuje cofniecie).\n-> Straznik - to czy w razie porazki cofniesz sie do PK czy do poczatku quizu zalezy od ilosci zdobytych punktow.\nProby - ilosc wykorrzystanych/maksymalna liczbe pytan przed rozpatrzeniem porazki.\nPunkty - punkty zdobyte w quizie.\nProg punktowy - mnimalna liczba punktow wymaganych do wygrania quizu.\nPoza wymienionymi w prawym panelu znajduja sie tez 3 przyciski i 1 suwak niezaleznie od trybu gry (opisane od lewej do prawej):\nPauza [skr.klaw. Q] - zatrzymuje lub wznawia gre. Podczas quizu oznacza ponowne losowanie pytania.\nWroc do menu [skr.klaw. P + O] - natychmiastowy powrot do menu glownego.\nWroc do punktu kontrolnego [skr.klaw. K + L] - za 1 cofniecie cofa gracza do ostatniego punktu kontrolnego - startu lub wejscia w labiryncie.\nSuwak - pozwala regulowac glosnosc. Jego konce sa przyciskami pozwalajacymi natychmiast ustwaic skrajne wartosci (lewy - wylacz, prawy - maksimum).\0";
			break;
		case 5:
			napis_pom = "Labirynt I";
			napis_pom2 = "Aby przejsc labirynt, musisz przejsc od punktu start (lub wejscie) do pola drzwi (lub meta) i KLIKNAC na nim. Zostaniesz przeniesiony/a do nastepnego etapu poziomu (quizu lub labiryntu) lub w przypadku mety poziom ukonczysz. Jesli twoj awatar nie bedzie dotykal zadnego pola, na ktorym moglby stac i spadnie lub dotknie wiatraka/kolczatki/plomieni to zostaniesz cofniety/a do punktu kontrolnego. Labirynty moga zawierac rozne elementy:\nPole - zwykle pole. Mozesz na nim stac, by nie spasc. Moze zawierac start, wejscie, mete lub drzwi. Niektore pola moga poawiac sie i znikac po aktywacji odpowiednich przyciskow lub po uplywie okreslonego czasu.\nPrzycisk - jesli na nim klikniesz mozesz go wcisnac lub odcisnac gdy jest wcisniety. Niektore przyciski moga po wcisnieciu/ocisnieciu sie zablokowac, uniemozliwajac ponowna aktywacje/deaktywacje. Przyciski moga aktywowac pojawianie i znikanie pol, wiatrakow, zatrzymywac/wznawiac obrot lub zmieniac jego kierunek dla wiatrakow. Maja tez wszystkie wlasciwosci zwyklego pola niebaedacego koncem ani poczatkiem labiryntu. Niektore przyciski opozniaja tez czasowe etapy znikania pol.\nMagiczny ogien - pojawia sie na niekturych znikajacych polach. O ile znikajace/pojawiajace sie pola moga juz podtrzymywac gracza n a swojej czesci w trakcie animacji, to palace sie pola bija natycmiast przy kontackie.\0";
			break;
		case 6:
			napis_pom = "Labirynt II";
			napis_pom2 = "Wiatraki - wiatraki znajduja sie na polach i bija gracza przy kontakcie z ich lopatami. Gdy sie obracaja, przewaznie mozna je ominac kozystajac z rotacji. Gdy stoja w miejscu i nie da sie ich minac, trzeba szukac odpowiedniego przycisku. Niektore wiatraki przyspieszaja na chwile co pewien czas - warto na nie uwazac.\nKolczatki - bija przy kontakcie. Poruszaja sie po trasach w lini prostej na 5 pol lub po okregu o promieniu 1 pola, zatrzymujac sie w okreslonych czesciach/czesci trasy na okolo sekunde.\nW niektorych labiryntach sa tez pewne elementy losowe (np. losowa pozycja wlasciwego przycisku). Labirynty 4. epizodu posiadaja przezroczyste, trudniejsze do obserwacji przeroczyste elementy - warto patrzzec uwaznie by sie nie pomylic.\0";
			break;
		case 7:
			napis_pom = "Elementy labiryntow";
			napis_pom2 = "";
			break;
		case 8:
			napis_pom = "Quiz";
			napis_pom2 = "Poczas quizu przeczytaj uwaznie pytanie (znajdujace sie tuz pod opisem fabularnym) oraz odpowiedzi ponizej, a nastepnie zaznacz kliknieciem 1 z 4 przyciskow A, B, C, D pod panelem quizu, tak by zaznaczony byl ten odpowiadajacy poprawnej odpowiedzi. Nastepnie wcisnij przycisk z ptasziem (fajka) by zatwierdzi� swoja odpowiedz. Panel wyswietli skutek twojej odpowiedzi, a po kliknieciu strzalki mozesz przejsc do kolejnego pytania/etapu poziomu.\nEfekty odpowiedzi:\nSukces - zdobyles/as maksymalna ilosc punktow za pytanie dzieki poprawnej odpowiedzi.\nPowoli do przodu - zdobyles/as troche punktow za czesciowo poprawna odpowiedz.\nNiepowodzenie - nie zdobyles/as punktow - zla odpowiedz.\nDroga wolna - uzbierales/as dosc punktow by ukonczyc ten quiz - mozesz przejsc do kolejnego etapu poziomu (ktorym moze tez byc jego ukonczenie).\nPorazka - nawet jesli odpowiedz byla poprawna, ilosc pytan sie wyczerpala, a ty wciaz nie masz dosc punktow - oznacza przegranie quizu (patrz Rozgrywka dane III).\nMozesz tez korzystac ze skrotow klawiszowych:\nODP A [skr.klaw. A]\tODP B [skr.klaw. W]\tODP C [skr.klaw. S]\nODP D [skr.klaw. D]\tZATWIERDZ [skr.klaw. R]\0";
			break;
		case 9:
			napis_pom = "Wyniki";
			napis_pom2 = "Ponizej znajduje sie wzor obliczajacy kocowy wynik, na podstawie posiadanych punktow i innych zmiennych:\nWYNIK KONCOWY = WYNIK x (1.0 + (LIMIT_CZASU - CZAS) / (LIMIT_CZAS + CZAS)) x (1.0 + (LIMIT_COFNIECIA - COFNIECIA) / LIMIT_COFNIECIA).\nW grze istnieja 3 rodzaje rekordow:\nRekord gracza - rekord uzytkownika na tym poziomie przy biezacej trudnosci.\nRekord lokalny - rekord ukonczenia poziomu wsrod wszystkich lokalnych uzytkownikow w tym egzemplarzu aplikacji i dla obecnej trudnosci.\nRekord tworcow - tylko 1 rekord dla wszystkich trudnosci, otrzymany przez tworcow gry na najwyzszej trudnosci.\0";
			break;
		}

		DrawRectangle(0.5f * (szer - szer_pom), 0.5f * (wys - wys_pom), szer_pom, wys_pom, Fade(EpisodeTheme.bgColor, 0.75f));
		DrawRectangle(0.5f * (szer - szer_pom) - 1.0f * Skala_liter, 0.5f * (wys - wys_pom) - 1.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
		DrawRectangle(0.5f * (szer + szer_pom) - 1.0f * Skala_liter, 0.5f * (wys - wys_pom) - 1.0f * Skala_liter, 3.0f * Skala_liter, wys_pom + 2.0f * Skala_liter, BLACK);
		DrawRectangle(0.5f * (szer - szer_pom) - 1.0f * Skala_liter, 0.5f * (wys + wys_pom) - 1.0f * Skala_liter, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);
		DrawRectangle(0.5f * (szer - szer_pom) - 1.0f * Skala_liter, 0.5f * (wys - wys_pom) - 1.0f * Skala_liter, szer_pom + 2.0f * Skala_liter, 3.0f * Skala_liter, BLACK);

		helper::DrawTextCentered(napis_pom, 0.5f * szer + 5.0f * Skala_liter, 0.5f * (wys - wys_pom) + 15.0f * Skala_liter, 35.0f * Skala_liter, BLACK);//JG 'cien'
		helper::DrawTextCentered(napis_pom, 0.5f * szer, 0.5f * (wys - wys_pom) + 10.0f * Skala_liter, 35.0f * Skala_liter, EpisodeTheme.textColor);

		switch (zmienne->biezacy_etap) {
		case 3:
		case 7:
			DrawTexturePro(grafiki->slajd.text, { 0.0f, 0.0f, grafiki->slajd.szer, grafiki->slajd.wys }, { 0.5f * (szer - szer_pom) + 20.0f * Skala_liter, 0.5f * (wys - wys_pom) + 50.0f * Skala_liter, szer_pom - 40.0f * Skala_liter, wys_pom - 70.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, WHITE);
			break;
		default:
			break;
		}

		int linia_dlugosc = (int)((szer_pom - 25.0f * Skala_liter) / (8.0f * Skala_liter));
		if (Skala_liter < 0.60f) linia_dlugosc = (int)((szer_pom - 25.0f * Skala_liter) / (11.0f * Skala_liter));
		else if (Skala_liter < 0.67f) linia_dlugosc = (int)((szer_pom - 25.0f * Skala_liter) / (9.0f * Skala_liter));
		int j = 0;
		int i = 0;
		float nowa_linia = 60.0f * Skala_liter;

		bool sekcja_tekstu = true;
		bool sekcja_tekstu2 = true;
		while (sekcja_tekstu2) {
			sekcja_tekstu = true;
			while (sekcja_tekstu) {
				i = 0;
				char* linia = new char[linia_dlugosc + 1];
				for (i; i < linia_dlugosc && napis_pom2[j] != '\n' && napis_pom2[j] != '\0'; i++) {
					if (!(i == 0 && napis_pom2[j] == ' ')) linia[i] = napis_pom2[j];
					else i--;
					j++;
				}
				linia[i] = '\0';
				if (napis_pom2[j] == '\n') {
					sekcja_tekstu = false;
					j++;
				}
				else if (napis_pom2[j] == '\0') { 
					sekcja_tekstu = false; 
					sekcja_tekstu2 = false;
				}
				while (linia[i] != ' ' && sekcja_tekstu) {
					linia[i] = '\0';
					i--;
					j--;
				}
				DrawText(linia, 0.5f * (szer - szer_pom) + 10.0 * Skala_liter, 0.5f * (wys - wys_pom) + nowa_linia, (int)(15.0f * Skala_liter), EpisodeTheme.textColor);
				delete[] linia;
				nowa_linia = nowa_linia + 24.0f * Skala_liter;
			}
		}


		//JG:PANEL PRZYCISKOW
		DrawRectangle(18.0f * Skala_liter + 0.5f * (szer - szer_pom), -32.0f * Skala_liter + 0.5f * (wys + wys_pom), szer_pom - 36.0f * Skala_liter, 64.0f * Skala_liter, BLACK);//JG:kontur przyciskow

		//JG:PRZYCISK POPRZEDNI
		DrawRectangle(20.0f * Skala_liter + 0.5f * (szer - szer_pom), -30.0f * Skala_liter + 0.5f * (wys + wys_pom), 279.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
		float jasnosc_pom = 0.0f;
		if (zmienne->biezacy_etap == 0) {//JG: bedzie uzyte gdy pojawi sie system odbokowan poziomow
			jasnosc_pom = -0.75f;
		}
		else if (zmienne->LAB_czulosc_przycisku[9] == 0 && zmienne->mysz_x > 20.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 299.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
		}
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[24], zmienne->LAB_zaczep_dec_przycisku[25], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 22.0f * Skala_liter + 0.5f * (szer - szer_pom), -28.0f * Skala_liter + 0.5f * (wys + wys_pom), 275.0f * Skala_liter, 56.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawText("Poprzedni", 80.0f * Skala_liter + 0.5f * (szer - szer_pom), -16.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(33.0f * Skala_liter), BLACK);//JG:cien napisu przycisku
		DrawText("Poprzedni", 78.0f * Skala_liter + 0.5f * (szer - szer_pom), -18.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(33.0f * Skala_liter), EpisodeTheme.textColor);//JG:napis przycisku


		//JG:PRZYCISK POWROT DO MENU
		DrawRectangle(301.0f * Skala_liter + 0.5f * (szer - szer_pom), -30.0f * Skala_liter + 0.5f * (wys + wys_pom), 278.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
		jasnosc_pom = 0.0f;
		if (zmienne->LAB_czulosc_przycisku[10] == 0 && zmienne->mysz_x > 301.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 579.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
		}
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[26], zmienne->LAB_zaczep_dec_przycisku[27], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 303.0f * Skala_liter + 0.5f * (szer - szer_pom), -28.0f * Skala_liter + 0.5f * (wys + wys_pom), 274.0f * Skala_liter, 56.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawText("Menu glowne", 336.0f * Skala_liter + 0.5f * (szer - szer_pom), -16.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(33.0f * Skala_liter), BLACK);//JG:cien napisu przycisku
		DrawText("Menu glowne", 334.0f * Skala_liter + 0.5f * (szer - szer_pom), -18.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(33.0f * Skala_liter), EpisodeTheme.textColor);//JG:napis przycisku


		//JG:PRZYCISK NASTEPNY
		DrawRectangle(581.0f * Skala_liter + 0.5f * (szer - szer_pom), -30.0f * Skala_liter + 0.5f * (wys + wys_pom), 279.0f * Skala_liter, 60.0f * Skala_liter, EpisodeTheme.textColor);
		jasnosc_pom = 0.0f;
		if (zmienne->biezacy_etap == SLAJDY) {//JG: bedzie uzyte gdy pojawi sie system odbokowan poziomow
			jasnosc_pom = -0.75f;
		}
		else if (zmienne->LAB_czulosc_przycisku[11] == 0 && zmienne->mysz_x > 581.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 860.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)) {
			jasnosc_pom = -0.5f;
			SetMouseCursor(4);
			zmienne->kurosr_czulosc = 1;
		}
		DrawTexturePro(grafiki->pole1.text, { zmienne->LAB_zaczep_dec_przycisku[28], zmienne->LAB_zaczep_dec_przycisku[29], grafiki->pole1.szer * 0.5f, grafiki->pole1.wys * 0.5f }, { 583.0f * Skala_liter + 0.5f * (szer - szer_pom), -28.0f * Skala_liter + 0.5f * (wys + wys_pom), 275.0f * Skala_liter, 56.0f * Skala_liter }, { 0.0f, 0.0f }, 0.0f, ColorBrightness(WHITE, jasnosc_pom));
		DrawText("Nastepny", 638.0f * Skala_liter + 0.5f * (szer - szer_pom), -16.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(33.0f * Skala_liter), BLACK);//JG:cien napisu przycisku
		DrawText("Nastepny", 636.0f * Skala_liter + 0.5f * (szer - szer_pom), -18.0f * Skala_liter + 0.5f * (wys + wys_pom), (int)(33.0f * Skala_liter), EpisodeTheme.textColor);//JG:napis przycisku




		/*for (auto& b : Buttons) {
			b->draw();
		}*/

	}
	void updateInstruction(grafika* tlo) {

		//JG:USTAWIANIE ZMIENNYCH ZWIAZANYCH Z WYMIARAMI OKNA
		float szer = (float)GetScreenWidth();
		float wys = (float)GetScreenHeight();
		float Skala_liter = 1.0;
		if (szer >= wys * tlo->szer / tlo->wys) {
			Skala_liter = wys / OknoWysBaz;
		}
		else {
			Skala_liter = szer / OknoSzerBaz;
		}
		if (700.0f * Skala_liter > wys) Skala_liter = Skala_liter = wys / OknoWysBaz;//JG: przy wyjatkowo wrednym skalowaniu okna bez tego zabezpieczenia zawartosc moze "rozszerzyc" sie poza okno. Dotyczy duzych paneli

		float szer_pom = 880.0f * Skala_liter;
		float wys_pom = 620.0f * Skala_liter;

		//JG:AKTUALIZACJA DANYCH KURSORA
		if (IsCursorOnScreen()) {
			zmienne->mysz_pop_x = zmienne->mysz_x;
			zmienne->mysz_pop_y = zmienne->mysz_y;
			zmienne->mysz_x = GetMouseX();
			zmienne->mysz_y = GetMouseY();
		}

		//JG:PRZYCISK POPRZEDNI
		if (zmienne->LAB_czulosc_przycisku[9] > 0) {
			zmienne->LAB_czulosc_przycisku[9] = zmienne->LAB_czulosc_przycisku[9] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[9] != 0) {
			zmienne->LAB_czulosc_przycisku[9] = 0;
		}
		else if (zmienne->biezacy_etap > 0 && ((IsKeyDown(KEY_P) && (IsKeyDown(KEY_O))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 20.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 299.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom)))) {

			zmienne->biezacy_etap = zmienne->biezacy_etap - 1;
			grafiki->aktualizuj_slajd(zmienne->biezacy_etap);

			zmienne->LAB_czulosc_przycisku[9] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}

		//JG:PRZYCISK >> MENU GLOWNE
		if (zmienne->LAB_czulosc_przycisku[10] > 0) {
			zmienne->LAB_czulosc_przycisku[10] = zmienne->LAB_czulosc_przycisku[10] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[10] != 0) {
			zmienne->LAB_czulosc_przycisku[10] = 0;
		}
		else if ((IsKeyDown(KEY_L) && (IsKeyDown(KEY_K))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 301.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 579.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom))) {

			stanGry = StanEkranu::MAIN_MENU;

			zmienne->LAB_czulosc_przycisku[10] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}



		//JG:PRZYCISK >> NASTEPNY
		if (zmienne->LAB_czulosc_przycisku[11] > 0) {
			zmienne->LAB_czulosc_przycisku[11] = zmienne->LAB_czulosc_przycisku[10] - 1;
		}
		else if (zmienne->LAB_czulosc_przycisku[11] != 0) {
			zmienne->LAB_czulosc_przycisku[11] = 0;
		}
		else if ( zmienne->biezacy_etap < SLAJDY && (((IsKeyDown(KEY_M) && (IsKeyDown(KEY_N))) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && zmienne->mysz_x > 581.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_x < 860.0f * Skala_liter + 0.5f * (szer - szer_pom) && zmienne->mysz_y > -30.0f * Skala_liter + 0.5f * (wys + wys_pom) && zmienne->mysz_y < 30.0f * Skala_liter + 0.5f * (wys + wys_pom))))) {

			zmienne->biezacy_etap = zmienne->biezacy_etap + 1;
			grafiki->aktualizuj_slajd(zmienne->biezacy_etap);

			zmienne->LAB_czulosc_przycisku[11] = 25;
			SetMouseCursor(1);
			zmienne->kurosr_czulosc = 0;
		}
	}
}