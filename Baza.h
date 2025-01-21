#pragma once
#include <iostream>
#include <sqlite3.h>
#include "gamestate.h"
const int Number_Of_Questions = 96;

static int callback1(void* NotUsed, int argc, char** argv, char** azColName)
{
   //std::cout << argv[0] << "\n";
   //zmienne->pytanie = argv[0];
   int ind = 1;
   while (argv[0][ind]!='@')
   {
      ind++;
   }
   if (zmienne->pytanie != NULL) delete zmienne->pytanie;
   zmienne->pytanie = new char[ind + 1];
   for (int i = 0; i < ind+1; i++)
   {
      if (argv[0][i] != '@')
      {
         zmienne->pytanie[i] = argv[0][i];
      }
      else
      {
         zmienne->pytanie[i] = '\0';
      }

   }
   return 0;
}

static int callback3(void* NotUsed, int argc, char** argv, char** azColName)
{
   //std::cout << argv[0] << "\n";
   //zmienne->odp_wytlumaczenie = argv[0];
   int ind = 1;
   while (argv[0][ind] != '@')
   {
      ind++;
   }
   if (zmienne->odp_wytlumaczenie != NULL) delete zmienne->odp_wytlumaczenie;
   zmienne->odp_wytlumaczenie = new char[ind + 1];
   for (int i = 0; i < ind + 1; i++)
   {
      if (argv[0][i] != '@')
      {
         zmienne->odp_wytlumaczenie[i] = argv[0][i];
      }
      else
      {
         zmienne->odp_wytlumaczenie[i] = '\0';
      }

   }
   return 0;
}

double strtoint(char* s)
{
   double result=0;
   int i = 0;
   if (!(s[0] > '0' && s[0] <= '9')){
       return 0;
   }
   else {
       while(s[i] >= '0' && s[i] <= '9'){
           result = 10 * result + (double)(s[i] - '0');
           i++;
       }
   }
   /*for (int i = 0; i < s.size(); i++)
   {
      result *= 10;
      result += s[i];
   }*/
   return result;
}

int jarjar = 0;//JG: wyglada na to, ze i w for 2 zawsze bedzie rowne 0, nawet jak zostanie zdefiniowane poza for (zeruje sie przy kazdym kolejnym wykonaniu). Zmienna globalna nieelegancko rozwiazuje problem.

static int callback2(void* NotUsed, int argc, char** argv, char** azColName)
{
   char* result;
   int ind = 0;
   for (int i = 0; i < argc; i++)
   {
      std::cout << azColName[i] << ": " << argv[i] << "\n";
   }
   for (int i = 0; i < argc; i++)
   {
      zmienne->punkty_odpowiedzi[jarjar] = (strtoint(argv[i]));
      jarjar = jarjar + 1;
   }
   return 0;
}

std::string inttostr(int n)
{
   std::string result = "";
   while (n > 0)
   {
      char c = (n % 10) + '0';
      result = result + c;
      n /= 10;
   }
   return result;
}

void getdata()
{
   srand(time(0));
   sqlite3* database;
   const char* dir;
   if (zmienne->trudnosc_pytania == '2')
   {
      dir = "latwe.db";
   }
   else if (zmienne->trudnosc_pytania == '6')
   {
      dir = "srednie.db";
   }
   else if (zmienne->trudnosc_pytania == 's')
   {
      dir = "trudne.db";
   }
   int exit = sqlite3_open(dir, &database);
   if (exit != SQLITE_OK)
   {
      //std::cerr << "Blad otwierania bazy danych: " << sqlite3_errmsg(database) << std::endl;
      return;
   }
   else
   {
      //std::cout << "Baza danych otwarta (lub utworzona) pomyslnie." << std::endl;
   }
   int random = rand() % Number_Of_Questions + 1;
   std::string ID = inttostr(random);
   std::string query = "SELECT CONTENT FROM QUESTION WHERE ID = ";
   std::string explanation = "SELECT EXPLANATION FROM QUESTION WHERE ID = ";
   std::string points = "SELECT POINTS FROM ANSWERS WHERE QUESTION_ID = ";
   query = query + ID;
   explanation = explanation + ID;
   points = points + ID;
   jarjar = 0;
   sqlite3_exec(database, query.c_str(), callback1, NULL, NULL);
   sqlite3_exec(database, points.c_str(), callback2, NULL, NULL);
   sqlite3_exec(database, explanation.c_str(), callback3, NULL, NULL);
   double maxi = zmienne->punkty_odpowiedzi[0];
   double maxiind = 0;
   for (int i = 1; i < 4; i++)
   {
      if (zmienne->punkty_odpowiedzi[i] > maxi)
      {
         maxi = zmienne->punkty_odpowiedzi[i];
         maxiind = i;
      }
   }
   zmienne->odp_pop = 'A' + (char)maxiind;
   int ind = 0;;;;;;
   std::cout << zmienne->pytanie;
}
