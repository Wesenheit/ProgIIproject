#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <array>
#include <vector>
#include "particle.h"
class SolarSystem
{
    private:
        Particle sun;       //słońce
        Particle moon;      //księżyc
        Particle earth;     //ziemia
        double omega;       //częstotliwość obiegu ziemi
        vector<double> wyn; //wektor wyników
        double rmoon;       //promień księżyca
        double rearth;      //promien ziemi
        double rsun;        //promien słońca
    public:
        SolarSystem();                                          //kontruktor
        void Simulate(int n,double R,double ds);                //generuje symulację
        void Show();                                            //pokazuje wyniki
        array<double,4> Diff(const array<double,4> &a);         //zwraca pochodną wektora pozycji w danym miejscu
        void RungeKutta(Particle &par,double ds,double &S);     //rozwiazuje równanie diff(x)=x metodą runge-kuttego 4 rzedu 
        void Save(string name);                                 //zapisuje wyniki do pliku name
        void update_moon(double T);                             //aktualizuje położenie księżyca
        void update_earth(double T);                            //aktualizuje połołożenie ziemi
};
#endif