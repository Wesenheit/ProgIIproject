#include <cmath>
#include "particle.h"
#include "utils.h"
#define G 123

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
double Force(Particle &par,const array<double,4> &position,array<double,4> &temp)
{
    double r=par.R(position);
    temp[2]+=-G*par.mass*(par.coords[0]-position[0])/pow(r,3);
    temp[3]+=-G*par.mass*(par.coords[1]-position[1])/pow(r,3);
    return r;
}
