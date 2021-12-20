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
    double rmoon=1737.4/MD;
    SolarSystem baza=SolarSystem();
    baza.Simulate(1000000,AU*1.52,rmoon);
    baza.Show();
    //baza.Save("back.bak");
    return 0;
}