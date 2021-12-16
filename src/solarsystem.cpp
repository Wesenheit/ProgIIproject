#include <array>
#include "utils.h"
#include "solarsystem.h"
#include "particle.h"
#include <cmath>
#include <iostream>
using namespace std;

array<double,4> SolarSystem::Diff(const array<double,4> &par)
{
    array<double,4> temp;
    double r;
    for (auto a:temp)
    {
        a=0;
    }
    r=Force(earth,par,temp);
    Force(moon,par,temp);
    temp[2]+=omega*par[0]*r-2*omega*par[3];
    temp[3]+=omega*par[1]*r+2*omega*par[2];
    temp[0]=par[2];
    temp[1]=par[1];
    return temp;
}

void SolarSystem::RungeKutta(Particle &par,double ds)
{
    double dt=ds/par.velocity();
    array<double,4> position=par.getpos();
    array<double,4> k1=Diff(position);
    array<double,4> k2=Diff(position+dt/2*k1);
    array<double,4> k3=Diff(position+dt/2*k2);
    array<double,4> k4=Diff(position+dt*k3);
    array<double,4> wyn=dt/6*(k1+2*k2+2*k3+k4);
    par.update(wyn);
}

void SolarSystem::Show()
{
    for (auto a:wyn)
    {
        cout<<a<<" ";
    }
}

void SolarSystem::Set(double x1, double y1,double m1, double x2,double y2,double m2,double omega)
{
    earth=Particle(array<double,4>{x1,y1,0,0},m1);
    moon=Particle(array<double,4>{x2,y2,0,0},m2);
    this->omega=omega;
}

SolarSystem::SolarSystem(double x1, double y1,double m1, double x2,double y2,double m2,double o)
{
    array<double,4> a={x1,y1,0,0};
    array<double,4> b={x2,y2,0,0};
    earth=Particle(a,m1);
    moon=Particle(b,m2);
    omega=o;
}

void SolarSystem::Simulate(int n,double R, double ds)
{
    for (int i=0;i<n;i++)
    {
        Particle a(R);
        double S=0;
        while(a.R()>rearth && a.R(moon)>rmoon && S<2*M_PI*R*5)
        {
            RungeKutta(a,ds);
        }
        if (a.R(moon)<rmoon)
        {
            wyn.push_back(moon.angle(a.getpos()));
        }
    }
}