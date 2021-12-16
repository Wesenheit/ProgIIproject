#include <cmath>
#include "particle.h"
#include "utils.h"
#include <random>
#include <iostream>
using namespace std;

Particle::Particle()
{
    coords=array<double,4>{0,0,0,0};
    mass=0;
}
Particle::Particle(double R,double M,mt19937 &generator)
{
    double an1=rangle(generator);
    double an2=rangle(generator);
    double temp=generator()%1000000;
    double v=(temp/1000000)*firstspacevel(R,M);
    coords=array<double,4>{R*cos(an1),R*sin(an1),v*cos(an1-an2),v*sin(an1-an2)};
    mass=0;
}
Particle::Particle(array<double,4> pos,double m)
{
    coords=pos;
    mass=m;
}

double Particle::R()
{
    double r=sqrt(coords[0]*coords[0]+coords[1]*coords[1]);
    return r;
}
double Particle::R(const Particle &a)
{
    double r=sqrt(pow(coords[0]-a.coords[0],2)+pow(coords[1]-a.coords[1],2));
    return r;
}
double Particle::R(const array<double,4> &a)
{
    double r=sqrt((coords[0]-a[0])*(coords[0]-a[0])+(coords[1]-a[1])*(coords[1]-a[1]));
    return r;
}
array<double,4> Particle::getpos()
{
    return coords;
}


void Particle::update(array<double,4> a)
{
    for (int i=0;i<4;i++)
    {
        coords[i]+=a[i];
    }
}
double Particle::velocity()
{
    double v=sqrt(coords[2]*coords[2]+coords[3]*coords[3]);
    return v;
}
double Particle::angle(const array<double,4> &position)
{
    if ((position[1]-coords[1])>0){return atan((position[1]-coords[1])/(position[0]-coords[0]));}
    else {return -atan((position[1]-coords[1])/(position[0]-coords[0]));}
}

void Particle::Show()
{
    cout<<"coordinates"<<endl;
    for (auto a:coords)
    {
        cout<<a<<" ";
    }
    cout<<endl;
    cout<<"Mass: "<<mass<<endl;
}
