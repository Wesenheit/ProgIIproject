#ifndef UTILS_H
#define UTILS_H
#include "particle.h"
double Force(Particle &par,const array<double,4> &position,array<double,4> &temp);
array<double,4> operator+(array<double,4> a,array<double,4> b);
array<double,4> operator*(double a,array<double,4> b);
#endif