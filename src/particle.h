#ifndef PARTICLE_H
#define PARTICLE_H
#include <array>
#include <random>

using namespace std;
class Particle
{
    friend class SolarSystem;
    friend class MoonSystem;
    private:
        array<double,4> coords;                         //kolejno x,y,vx,vy
        double mass;                                    //masa
    public:
        Particle();                                     //kontruktor zerowy
        Particle(array<double,4> pos,double mass);      //konstruktor niezerowy
        Particle(double R,double M,mt19937 &generator); //kontruktor losujacy prędkość w odległości R 
        Particle(double R,double v,double vk,mt19937 &generator);
        double R();                                     //zwraca odległość od początku układu współrzędnych
        double R(const Particle &a);                    //zwraca odległość od ciała a
        double R(const array<double,4> &position);      //zwraca odległość od miejscu w tablicy position
        array<double,4> getpos();                       //zwraca wektor położenia
        void update(array<double,4> a);                 //zwieksza wektor o wektor a
        double velocity();                              //zwraca wartość prędkości
        void Show();                                    //pokazuje wektor polożenia oraz masę
        friend void Force(Particle &par,const array<double,4> &position,array<double,4> &temp);    //siła działajca na czastkę
        friend double angle(Particle &one, Particle &two,Particle &three);                                         //zwraca kąt pomiedzy dwoma ciałami
};
#endif