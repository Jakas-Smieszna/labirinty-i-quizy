#include "ustawienia.h"
#include "funkcjePomocnicze.h"
#include "raylib.h"
#include "gamestate.h"
#include "przycisk.h"
#include "slider.h"
#include "instrukcja.h"
#include "fstream"
#include <vector>

using namespace std;

vector <string> DivideText(string s)
{
   fstream a(s);
   vector <string> lines;
   int charmax = (GetScreenWidth() * 0.7) / 10;
   string input, tekst = "";
   while (a >> input)
   {
      tekst = tekst + input + ' ';
      if (tekst.size() > charmax)
      {
         lines.push_back(tekst);
         tekst = "";
      }
   }
   return lines;
}