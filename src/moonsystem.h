#ifndef MoonSystem_H
#define MoonSystem_H
#include <array>
#include <vector>
#include "particle.h"
class MoonSystem
{
    private:
        Particle moon;      //księżyc
        Particle earth;     //ziemia
        double omega;       //częstotliwość obiegu ziemi
        vector<double> wyn; //wektor wyników
        double rmoon;       //promień księżyca
        double rearth;      //promien ziemi
    public:
        MoonSystem();                                          //kontruktor
        void Simulate(int n,double R,double ds);                //generuje symulację
        void Show();                                            //pokazuje wyniki
        array<double,4> Diff(const array<double,4> &a);         //zwraca pochodną wektora pozycji w danym miejscu
        void RungeKutta(Particle &par,double ds,double &S);     //rozwiazuje równanie diff(x)=x metodą runge-kuttego 4 rzedu 
        void Save(string name);                                 //zapisuje wyniki do pliku name
        void update_moon(double T);                             //aktualizuje położenie księżyca
};
#endif