#include <array>
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include "particle.h"
#include "solarsystem.h"
#include "utils.h"
using namespace std;

int main()
{
    double xearth=0;
    double yearth=0;
    double xmoon=-1;
    double ymoon=0;
    double me=1;
    double mm=1/81;
    double omega=2*M_PI;
    double rearth=6371/384000;
    double rmoon=1737.4/384000;
    SolarSystem baza=SolarSystem(xearth,yearth,me,xmoon,ymoon,mm,omega,rearth,rmoon);
    baza.Simulate(600*30,30,rmoon);
    baza.Show();
    baza.Save("back.bak");
    return 0;
}