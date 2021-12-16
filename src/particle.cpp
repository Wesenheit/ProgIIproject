#include <cmath>
#include "particle.h"
#include <cstdlib> 
#include <ctime> 

#define G 100


Particle::Particle()
{
    coords=array<double,4>{0,0,0,0};
    mass=0;
}
Particle::Particle(double R)
{
    double an;
    
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
    double r=sqrt((coords[0]-a.coords[0])*(coords[0]-a.coords[1])+(coords[1]-a.coords[1])*(coords[1]-a.coords[1]));
    return r;
}
double Particle::R(const array<double,4> &a)
{
    double r=sqrt((coords[0]-a[0])*(coords[0]-a[1])+(coords[1]-a[1])*(coords[1]-a[1]));
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
    return atan((position[1]-coords[1])/(position[1]-coords[1]));
}
