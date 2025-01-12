#pragma once

#include <cstdlib>
#include <cmath>
#include "gamestate.h"

#define M_PI 3.141592653589793 //JG:ta biblioteczne niegdy mi nie dzialala :(
#define Promien_Gracza_Wiatrak 12.0f//JG: pozwala latwo zmienic zasieg kolizji w relacji gracz-wiatrak, promien kwadratu

double Xwzo(double k, double a, double r, double znak);
double Ywzo(double k, double b, double r, double znak);
char CwiKat(double kat);

void Przeciecie_Okrag_Linia_Kat(float tab_wynikowa[4], float R, float kat, float X, float Y) {
    
    if (kat > 360.0f - TOL) kat = kat - 360.0f;
    double kat_pomocniczy = kat;
    double kat_rad = 2.0 * M_PI / 360.0 * kat_pomocniczy;

    switch (CwiKat(kat_pomocniczy)) {//cwiartka ukladu wspolrzednych z srodkiem w srodku UFO
    case '3':
        tab_wynikowa[0] = Xwzo(kat_rad, X, R, 1.0);
        tab_wynikowa[1] = Ywzo(kat_rad, Y, R, 1.0);
        break;

    case '2':
        tab_wynikowa[0] = Xwzo(kat_rad, X, R, 1.0);
        tab_wynikowa[1] = Ywzo(kat_rad, Y, R, 1.0);
        break;
    case '1':
        tab_wynikowa[0] = Xwzo(kat_rad, X, R, -1.0);
        tab_wynikowa[1] = Ywzo(kat_rad, Y, R, -1.0);
        break;
    case '4':
        /*if (spr[i].S_typ == 'p') {
            spr[i].S_x = Xwzo(U_rad_kat + PLYKAT, U_x, U_r + PLY, -1.0);
            spr[i].S_y = Ywzo(U_rad_kat + PLYKAT, U_y, U_r + PLY, -1.0);
        }
        else {*/
        tab_wynikowa[0] = Xwzo(kat_rad, X, R, -1.0);
        tab_wynikowa[1] = Ywzo(kat_rad, Y, R, -1.0);
        //}

        break;
    default:
        break;
    }

    //kat_pomocniczy = U_kat + 45 * i;
    switch (CwiKat(kat_pomocniczy)) {//cwiartka ukladu wspolrzednych z srodkiem w srodku UFO
    case '3':
        tab_wynikowa[2] = Xwzo(kat_rad, X, R, -1.0);
        tab_wynikowa[3] = Ywzo(kat_rad, Y, R, -1.0);
        break;
    case '2':

        tab_wynikowa[2] = Xwzo(kat_rad, X, R, -1.0);
        tab_wynikowa[3] = Ywzo(kat_rad, Y, R, -1.0);
        break;
    case '1':
        tab_wynikowa[2] = Xwzo(kat_rad, X, R, 1.0);
        tab_wynikowa[3] = Ywzo(kat_rad, Y, R, 1.0);
        break;
    case '4':
        tab_wynikowa[2] = Xwzo(kat_rad, X, R, 1.0);
        tab_wynikowa[3] = Ywzo(kat_rad, Y, R, 1.0);
        break;
    default:
        break;
    }


    //spr[i].S_k = U_kat + 45 * i - 90;//kat sprzetu
    //if (spr[i].S_k < 0) spr[i].S_k = spr[i].S_k + 360;
    //while (spr[i].S_k > 360) spr[i].S_k = spr[i].S_k - 360;

    //if (spr[i].S_k > 360) spr[i].S_k = spr[i].S_k - 360;

    //spr[i + 4].S_k = U_kat + 45 * (i + 4) - 90;//kat 2. sprzetu z pary
    //if (spr[i + 4].S_k < 0) spr[i + 4].S_k = spr[i + 4].S_k + 360;
    //while (spr[i + 4].S_k > 360) spr[i + 4].S_k = spr[i + 4].S_k - 360;

    //if (spr[i + 4].S_k > 360) spr[i + 4].S_k = spr[i + 4].S_k - 360;

    //U_rad_kat = U_rad_kat + pi / 4;//kat dla nastepnego sprzetu

}


double Xwzo(double k, double a, double r, double znak) {//liczenie X sprzetu
    if (abs(k - M_PI / 2.0) > TOL && abs(k - 3.0 * M_PI / 2.0) > TOL) return (a * tan(k) * tan(k) + a + znak * sqrt(r * r * (tan(k) * tan(k) + 1))) / (tan(k) * tan(k) + 1.0);
    else {
        return a;//przypadek asymptoty tangens
    }
}
double Ywzo(double k, double b, double r, double znak) {//liczenie Y sprzetu
    if (abs(k - M_PI / 2.0) > TOL && abs(k - 3.0 * M_PI / 2.0) > TOL) return (b * tan(k) * tan(k) + b + znak * tan(k) * sqrt(r * r * (tan(k) * tan(k) + 1))) / (tan(k) * tan(k) + 1.0);
    else {
        if (Ywzo(k - M_PI / 4.0, b, r, znak) > b) {//przypadek asymptoty tangens
            return (b - r);
        }
        else {
            return (b + r);
        }
    }
}


char CwiKat(double kat) {//sprawdzanie cwiartki ukl.wpolrzednych.
    while (kat <= -TOL) {
        kat = kat + 360.0;
    }
    while (kat - 360.0 >= TOL) {
        kat = kat - 360.0;
    }
    if (-TOL >= kat - 90.0 && kat >= -TOL) return '1';
    else {
        if (TOL >= kat - 180.0 && kat - 90.0 >= -TOL) return '2';
        else {
            if (-TOL >= kat - 270.0 && kat - 180.0 >= -TOL) return '3';
            else {
                if (TOL >= kat - 360.0 && kat - 270.0 >= -TOL) return '4';
                else return '1';
            }
        }
    }
}