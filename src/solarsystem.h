#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <array>
#include <vector>
#include "particle.h"
class SolarSystem
{
    private:
        Particle moon;
        Particle earth;
        double omega;
        vector<double> wyn;
        double rmoon;
        double rearth;
    public:
        SolarSystem(double x1, double y1,double m1, double x2,double y2,double m2,double omega);
        void Simulate(int n,double R,double dt);
        void Show();
        void Set(double x1, double y1,double m1, double x2,double y2,double m2,double omega);
        array<double,4> Diff(const array<double,4> &a);
        void RungeKutta(Particle &par,double dt);
};
#endif