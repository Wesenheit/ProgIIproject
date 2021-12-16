#include <array>
#include "utils.h"
#include "solarsystem.h"
#include "particle.h"
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>

#ifdef PARA
#include <omp.h>
#define OMP_NUM 10
#endif

using namespace std;

array<double,4> SolarSystem::Diff(const array<double,4> &par)
{
    array<double,4> temp={0,0,0,0};
    double r;
    r=Force(earth,par,temp);
    Force(moon,par,temp);
    temp[2]+=omega*par[0]*r-2*omega*par[3];
    temp[3]+=omega*par[1]*r+2*omega*par[2];
    temp[0]=par[2];
    temp[1]=par[3];
    return temp;
}

void SolarSystem::RungeKutta(Particle &par,double ds,double &S)
{
    ds=ds*(1.000001-exp(-(par.R(moon)-rmoon)/100));
    double dt=ds/par.velocity();
    array<double,4> position=par.getpos();
    array<double,4> k1=Diff(position);
    array<double,4> k2=Diff(position+dt/2*k1);
    array<double,4> k3=Diff(position+dt/2*k2);
    array<double,4> k4=Diff(position+dt*k3);
    array<double,4> wyn=dt/6*(k1+2*k2+2*k3+k4);
    par.update(wyn);
    S+=ds;
}

void SolarSystem::Show()
{
    for (auto a:wyn)
    {
        cout<<a<<" ";
    }
    cout<<endl;
}

void SolarSystem::Save(string name)
{
    ofstream out;
    out.open(name,ios_base::app);
    for (auto a:wyn)
    {
        out<<a<<" ";
    }
    out.close();
}

void SolarSystem::Set(double x1, double y1,double m1, double x2,double y2,double m2,double omega)
{
    earth=Particle(array<double,4>{x1,y1,0,0},m1);
    moon=Particle(array<double,4>{x2,y2,0,0},m2);
    this->omega=omega;
}

SolarSystem::SolarSystem(double x1, double y1,double m1, double x2,double y2,double m2,double o,double re, double rm)
{
    array<double,4> a={x1,y1,0,0};
    array<double,4> b={x2,y2,0,0};
    earth=Particle(a,m1);
    moon=Particle(b,m2);
    omega=o;
    rearth=re;
    rmoon=rm;
}

void SolarSystem::Simulate(int n,double R, double ds)
{
    #ifdef PARA
    omp_set_num_threads(OMP_NUM);
    #endif
    mt19937 generator;
    #pragma omp parallel for schedule(dynamic)
    for (int i=0;i<n;i++)
    {
        Particle a(R,earth.mass+moon.mass,generator);
        #pragma omp critical
        cout<<"Calulating "<<i<<"th particle"<<endl;
        double S=0;
        while(a.R()>rearth && a.R(moon)>rmoon && S<2*M_PI*R*5)
        {
            RungeKutta(a,ds,S);
        }
        if (a.R(moon)<rmoon)
        {
            #pragma omp critical
            wyn.push_back(moon.angle(a.getpos()));
        }
    }
}