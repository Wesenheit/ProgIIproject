#include <cmath>
#include <random>
#include <chrono>
#include <iostream>
#include "particle.h"
#include "utils.h"
using namespace std;

array<double,4> operator+(array<double,4> a,array<double,4> b)
{
    array<double,4> wyn;
    for (int i=0;i<4;i++)
    {
        wyn[i]=a[i]+b[i];
    }
    return wyn;
}
array<double,4> operator*(double a,array<double,4> b)
{
    array<double,4> wyn;
    for (int i=0;i<4;i++)
    {
        wyn[i]=a*b[i];
    }
    return wyn;
}
void Force(Particle &par,const array<double,4> &position,array<double,4> &temp)
{
    double r=par.R(position);
    temp[2]+=G*par.mass*(par.coords[0]-position[0])/pow(r,3);
    temp[3]+=G*par.mass*(par.coords[1]-position[1])/pow(r,3);
}


double rangle(mt19937 &generator)
{
    double temp=generator()%1000000;
    return temp*2*M_PI/1000000;
}

double firstspacevel(double R,double M)
{
    return sqrt(G*M/R);
}

double angle(Particle &one, Particle &two)
{
    if (two.coords[0]-one.coords[0]<0)
    {
        return atan((two.coords[1]-one.coords[1])/(two.coords[0]-one.coords[0]));
    }
    else
    {
        return -atan((two.coords[1]-one.coords[1])/(two.coords[0]-one.coords[0]));
    }
}