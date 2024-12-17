#pragma once
#include <iostream>
#include <sqlite3.h>
#include "gamestate.h"
const int Number_Of_Questions = 10;

static int callback1(void* NotUsed, int argc, char** argv, char** azColName)
{
   //std::cout << argv[0] << "\n";
   //zmienne->pytanie = argv[0];
   int ind = 1;
   while (argv[0][ind]!='@')
   {
      ind++;
   }
   if (zmienne->pytanie != NULL)delete zmienne->pytanie;
   //zmienne->pytanie = new char[ind];
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


int strtoint(std::string s)
{
   int result=0;
   for (int i = 0; i < s.size(); i++)
   {
      result *= 10;
      result += s[i];
   }
   return result;
}

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
      zmienne->punkty_odpowiedzi[i] = strtoint(argv[i]);
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
   const char* dir = "baza.db";
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
   std::string points = "SELECT POINTS FROM ANSWERS WHERE QUESTION_ID = ";
   query = query + ID;
   points = points + ID;
   sqlite3_exec(database, query.c_str(), callback1, NULL, NULL);
   sqlite3_exec(database, points.c_str(), callback2, NULL, NULL);
   int maxi = zmienne->punkty_odpowiedzi[0];
   int maxiind = 0;
   for (int i = 1; i < 4; i++)
   {
      if (zmienne->punkty_odpowiedzi[i] > maxi)
      {
         int maxi = zmienne->punkty_odpowiedzi[i];
         int maxiind = i;
      }
   }
   zmienne->odp_pop = 'A' + maxiind;
   int ind = 0;
   std::cout << zmienne->pytanie;
}
