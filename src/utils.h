#ifndef UTILS_H
#define UTILS_H
#include "particle.h"


#define G 61801235000
#define AU 389152.937
#define MS 333054
#define EP 14
#define ME 1
#define MM 1/81
#define MD 38400

void Force(Particle &par,const array<double,4> &position,array<double,4> &temp);
array<double,4> operator+(array<double,4> a,array<double,4> b);
array<double,4> operator*(double a,array<double,4> b);
double rangle(mt19937 &generator);
double firstspacevel(double R,double M);
double angle(Particle &one, Particle &two);
#endif