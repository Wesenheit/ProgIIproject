#ifndef PARTICLE_H
#define PARTICLE_H
#include <array>
#include <random>
using namespace std;
class Particle
{
    public:
        array<double,4> coords;
        double mass;
    public:
        Particle();
        Particle(array<double,4> pos,double mass);
        Particle(double R,double M,mt19937 &generator);
        double R();
        double R(const Particle &a);
        double R(const array<double,4> &position);
        array<double,4> getpos();
        void update(array<double,4> a);
        double velocity();
        void Show();
};
#endif