#ifndef UTILS_H
#define UTILS_H
#include <array>
#include <random>
using namespace std;

#define G 61801235000   //stała grawitacji
#define AU 389.152937   //jednostka astronomiczna
#define MS 333054       //masa słońca
#define EP 13.55          //okres rotacji ziemi
#define ME 1            // Masa ziemi
#define MM 0.01234         //Masa księżyca
#define MD 38400        //odleglość ziemia księżyc (w km)
#define OMP_NUM 4 //ilość rdzeni

array<double,4> operator+(array<double,4> a,array<double,4> b);                     //dodawanie tablic
array<double,4> operator*(double a,array<double,4> b);                              //mnożenie tablic przez skalar
double rangle(mt19937 &generator);                                                  //generuje losowy kąt
double firstspacevel(double R,double M);                                            //pierwsza predkość kosmiczna w odległości R 
#endif