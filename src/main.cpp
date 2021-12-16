#include <array>
#include <iostream>
#include "particle.h"
#include "solarsystem.h"
#include "utils.h"
using namespace std;

int main()
{
    double xearth=0;
    double yearth=0;
    double xmoon=1;
    double ymoon=0;
    double me=1;
    double mm=1/81;
    double omega=0;
    SolarSystem baza=SolarSystem(xearth,yearth,me,xmoon,ymoon,mm,omega);
    baza.Simulate(1000,0.5,0.1);
    return 0;
}