#pragma once
// Struct do przechowywania pozycji na ekranie.
// absX, absY - float od 0 do 1; miejsce na ekranie jako % odpowiednio szerokości (od lewej do prawej) i wysokości (od góry do dołu)
// offsetX, offsetY - float do przechowywania offsetu przycisku (Jednostka: odpowiednio iloraz szerokośći i wysokośći przycisku)
// tzn przykład
// masz przycisk i chcesz by był w lewym dolnym rogu ekranu:
// pozycja wtedy to będzie {0, 1, 0, -1}
// lewy dolny róg ekranu (0, 1)
// offset - o jedną wysokość przycisku w górę (0, -1)
// przesunięcie po prostu względem tej pozycji absolutnej cnie
struct ScreenPos {
	float absX, absY;
	float offsetX, offsetY;
};