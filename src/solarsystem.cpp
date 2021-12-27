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
#endif

using namespace std;

array<double,4> SolarSystem::Diff(const array<double,4> &par)
{
    array<double,4> temp={0,0,0,0};
    Force(sun,par,temp);
    Force(earth,par,temp);
    Force(moon,par,temp);
    temp[0]=par[2];
    temp[1]=par[3];
    return temp;
}

void SolarSystem::RungeKutta(Particle &par,double ds,double &T)
{
    update_earth(T);
    update_moon(T);
    if (par.R(moon)<30)
    {
        ds=rmoon/20*(1.000001-exp(-par.R(moon)*1000));
    }
    else
    {
        ds=ds*(1.000001-exp(-par.R(earth)*1000));
    }
    double dt=ds/par.velocity();
    array<double,4> position=par.getpos();
    array<double,4> k1=Diff(position);
    array<double,4> k2=Diff(position+dt/2*k1);
    array<double,4> k3=Diff(position+dt/2*k2);
    array<double,4> k4=Diff(position+dt*k3);
    array<double,4> wyn=dt/6*(k1+2*k2+2*k3+k4);
    par.update(wyn);
    T+=dt;
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
    if (wyn.size()>0)
    {
        ofstream out;
        out.open(name,ios_base::app);
        for (auto a:wyn)
        {
            out<<a<<" ";
        }
        out<<endl;
        out.close();
    }
}

SolarSystem::SolarSystem()
{
    sun=Particle(array<double,4>{0,0,0,0}, MS );
    earth=Particle(array<double,4>{AU,0,0,0},ME);
    moon=Particle(array<double,4>{AU+1,0,0,0},MM);
    omega=sqrt(G*MS/pow(AU,3));
    rearth=6371/MD;
    rmoon=1737.4/MD;
    rsun=696342/MD;
}
void SolarSystem::update_moon(double T)
{
    moon.coords[0]=earth.coords[0]+cos(T);
    moon.coords[1]=earth.coords[1]+sin(T);
}

void SolarSystem::update_earth(double T)
{
    earth.coords[0]=AU*cos(omega*T);
    earth.coords[1]=AU*sin(omega*T);
}

void SolarSystem::Simulate(int n,double R, double ds)
{
    #ifdef PARA
    omp_set_num_threads(OMP_NUM);
    #endif
    mt19937 generator;

    #pragma omp parallel for schedule(dynamic) firstprivate(moon,earth,sun,rmoon,rsun,rearth,omega) shared(wyn)
    for (int i=0;i<n;i++)
    {
        Particle a(R,sun.mass,generator);
        /*
        #pragma omp critical
        cout<<"Calulating "<<i<<"th particle"<<endl;
        */
        double T=0;
        while(a.R()<2*AU && a.R()>rsun && a.R(earth)>rearth && a.R(moon)>rmoon && T<3*EP)
        {
            RungeKutta(a,ds,T);
        }
        if (a.R(moon)<rmoon)
        {
            #pragma omp critical
            wyn.push_back(angle(earth,moon,a));
        }
    }
}