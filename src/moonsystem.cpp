/*
ustawiamy ziemię w środku układu współrzędnych  efektywnie ją unieruchamiając. Przejście do tego układu współrzędnych rekompensujemy dwiema siłami, siłą pływową 2GM/R^3*r oraz 
siłą coriolisa. Oprócz tego mamy siłą pochodzącą od mobilnego księżyca oraz ziemi. 
*/
#include <array>
#include "utils.h"
#include "moonsystem.h"
#include "particle.h"
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <ctime>

#ifdef PARA
#include <omp.h>
#endif

using namespace std;

array<double,4> MoonSystem::Diff(const array<double,4> &par)
{
    array<double,4> temp={0,0,0,0};
    Force(earth,par,temp);
    Force(moon,par,temp);
    temp[2]+=2*G*MS/pow(AU,3)*par[0];   //siła pływowa od słońca
    temp[2]+=2*omega*par[3];           //siła coriolisa
    temp[3]+=-2*omega*par[2];            //siła coriolisa
    temp[0]=par[2];                     //definicja
    temp[1]=par[3];                     //definicja
    return temp;
}

void MoonSystem::RungeKutta(Particle &par,double ds,double &T)
{
    update_moon(T);         //aktualizujemy pozycję księżyca
    if (par.R(moon)<0.5)    //jak jesteśmy blisko księżyca to zwiększamy dokładność
    {
        ds=rmoon/200*(1-exp(-(par.R(moon)-rmoon)/2));  //gdy zbliżamy się do księżyca to wykładniczo spada nam długość kroku
    }
    else
    {
        ds=ds*(1.000001-exp(-par.R(earth)));   //tutaj tak samo ale zależy to od odległości od ziemi
    }
    double dt=ds/par.velocity()+0.0000000000000001;                //konwertujemy stały krok odległości na krok czasowy plus pewna stała
    array<double,4> position=par.getpos();      //bierzym gdzie znajduje się cząteczka
    array<double,4> k1=Diff(position);          
    array<double,4> k2=Diff(position+dt/2*k1);
    array<double,4> k3=Diff(position+dt/2*k2);
    array<double,4> k4=Diff(position+dt*k3);
    array<double,4> wyn=dt/6*(k1+2*k2+2*k3+k4);
    par.update(wyn);                            //updatujemy pozycję naszego obiektu
    T+=dt;
}

void MoonSystem::Show()
{
    for (auto a:wyn)
    {
        cout<<a<<" ";
    }
    cout<<endl;
}

void MoonSystem::Save(string name)
{
    if (wyn.size()>0)
    {
        ofstream out;
        out.open(name,ios_base::app);
        for (auto a:wyn)
        {
            out<<a<<" ";
        }
        out<<endl;
        out.close();
    }
}

MoonSystem::MoonSystem()
{
    earth=Particle(array<double,4>{0,0,0,0},ME);
    moon=Particle(array<double,4>{1,0,0,0},MM);
    omega=2*M_PI/EP;       
    rearth=6371/MD;
    rmoon=1737.4/MD;
}
void MoonSystem::update_moon(double T)
{
    moon.coords[0]=cos(T);
    moon.coords[1]=sin(T);
}


void MoonSystem::Simulate(int n,double R, double ds)
{
    #ifdef PARA
    omp_set_num_threads(OMP_NUM);
    #endif
    mt19937 generator(time(NULL));
    #pragma omp parallel for schedule(dynamic) firstprivate(moon,earth,omega,rmoon,rearth,R) shared(wyn,generator)
    for (int i=0;i<n;i++)
    {
        Particle a;
        #pragma omp critical
        {
            Particle temp(R,firstspacevel(1.52*AU,MS),firstspacevel(AU,MS),generator); //bierzemy ciała losowym położeniu oraz losowej prędkości o długości pierwszej prędkości kosmicznej
            a=temp;                                                                    //na orbicie marsa i transformujemy do układu w którym ziemia spoczywa.
        }
        
        #pragma omp critical
        cout<<"Calculating "<<i<<"th particle"<<endl;
        
        double T=0;
        while(a.R(earth)<5*R && a.R(earth)>rearth && a.R(moon)>rmoon && T<3) //gdy cząsteczka oddali się na 5 razy początkowy dystans to kończymy, jak wleci w księżyc lub ziemię tak samo oraz gdy miną 3 okresy synodyczne
        {
            RungeKutta(a,ds,T);
        }
        if (a.R(moon)<rmoon)
        {
            #pragma omp critical
            wyn.push_back(angle(earth,moon,a));
        }
    }
}