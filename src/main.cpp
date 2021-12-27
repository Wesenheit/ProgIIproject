#include <array>
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include "particle.h"
#include "solarsystem.h"
#include "moonsystem.h"
#include "utils.h"
using namespace std;

int main()
{
    MoonSystem baza=MoonSystem();
    baza.Simulate(2000,2,0.0001);
    baza.Show();
    baza.Save("wyn.txt");
    return 0;
}