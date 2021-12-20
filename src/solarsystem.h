#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <array>
#include <vector>
#include "particle.h"
class SolarSystem
{
    private:
        Particle sun;
        Particle moon;
        Particle earth;
        double omega;
        vector<double> wyn;
        double rmoon;
        double rearth;
        double rsun;
    public:
        SolarSystem();
        SolarSystem(double x1, double y1,double m1, double x2,double y2,double m2,double omega,double re, double rm);
        void Simulate(int n,double R,double dt);
        void Show();
        array<double,4> Diff(const array<double,4> &a);
        void RungeKutta(Particle &par,double dt,double &S);
        void Save(string name);
        void update_moon(double T);
        void update_earth(double T);
};
#endif