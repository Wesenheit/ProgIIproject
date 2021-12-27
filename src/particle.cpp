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
    double an1=rangle(generator);       //losowy kąt wektora wodzącego
    double an2=rangle(generator)/2;     //losowy kąt wzgledem wektora wodzacego
    double temp=generator()%1000000;    //losowanie prędkości
    double v=(temp/1000000)*firstspacevel(R,M);
    coords=array<double,4>{R*cos(an1),R*sin(an1),-v*sin(an1+an2),+v*cos(an1+an2)};
    mass=0; //masa będzie zerowa bo nie ma ona znaczenia
}
Particle::Particle(double R,double v,double vk, mt19937 &generator) //generujemy ciało w odległości R z prędkością v w losowym kieunku a potem przenosimy ją do układu ziemi
{
    double an1=rangle(generator);       //losowy kąt wektora wodzącego
    double an2=rangle(generator)/2;     //losowy kąt wzgledem wektora wodzacego
    coords=array<double,4>{R*cos(an1),R*sin(an1),v*cos(an2),v*sin(an2)+vk};
    mass=0; //masa będzie zerowa bo nie ma ona znaczenia
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
void Force(Particle &par,const array<double,4> &position,array<double,4> &temp)
{
    double r=par.R(position);
    temp[2]+=G*par.mass*(par.coords[0]-position[0])/pow(r,3);
    temp[3]+=G*par.mass*(par.coords[1]-position[1])/pow(r,3);
}

double angle(Particle &one, Particle &two,Particle &three)
{
    array<double,2>r1={one.coords[0]-two.coords[0],one.coords[1]-two.coords[1]};
    array<double,2>r2={three.coords[0]-two.coords[0],three.coords[1]-two.coords[1]};
    return atan2(r1[0],r1[1])-atan2(r2[0],r2[1]);
}