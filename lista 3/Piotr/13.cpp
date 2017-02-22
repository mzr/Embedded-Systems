
#include<iostream>
#include<stdio.h>
#include<stdlib.h> //malloc
#include<time.h>

#include "liczczaswin.h"

using namespace std;

int liczby[100000000];
//int tab[10000000]; //nie potrzebujê kopii, bo nie modyfikujê orygina³u

int odwrocraz(int liczba)
{
    for (int i=0; i<16; ++i)
    {
        int czy1 = (liczba & (1<<i))>>i;
        int czy2 = (liczba & (1<<(31-i)))>>(31-i);
        liczba &= (~(1<<i));
        liczba &= (~(1<<(31-i))); //usuwa bity
        liczba |= czy1<<(31-i);
        liczba |= czy2<<i;
    }
    //cout<<liczba<<endl; //sprawdzałem że działa na rozm 10 - dają to samo
    return liczba;
}

int odwrocdwa(int liczba)
{
    //st¹d:  https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive
    unsigned char raz,dwa,trzy,cztery;//kolejne liczby
    raz = liczba>>24;
    dwa = (liczba<<8)>>24;
    trzy = (liczba<<16)>>24;
    cztery = (liczba<<24)>>24;

    raz = ( ((raz * 0x0802LU & 0x22110LU) | (raz * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16 );
    dwa = ( ((dwa * 0x0802LU & 0x22110LU) | (dwa * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16 );
    trzy = ( ((trzy * 0x0802LU & 0x22110LU) | (trzy * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16 );
    cztery = ( ((cztery * 0x0802LU & 0x22110LU) | (cztery * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16 );
    //rzutowanie usuwa œmieci obok; jak siê okazuje, trzeba rzutowaæ na pocz¹tku, bo inaczej Ÿle!!!
    //tzn np. te zmienne mieæ typu unsigned char
    liczba = 0;
    liczba = (cztery << 24) + (trzy << 16) + (dwa<<8) + raz;
    //cout<<liczba<<endl;
    return liczba;
}

int odwroctrzy(int liczba)
{
    //st¹d:  https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive
    liczba = ((liczba >> 1) & 0x55555555) | ((liczba & 0x55555555) << 1);
    liczba = ((liczba >> 2) & 0x33333333) | ((liczba & 0x33333333) << 2);
    liczba = ((liczba >> 4) & 0x0F0F0F0F) | ((liczba & 0x0F0F0F0F) << 4);
    liczba = ((liczba >> 8) & 0x00FF00FF) | ((liczba & 0x00FF00FF) << 8);
    liczba = ( liczba >> 16) | ( liczba << 16);
    //cout<<liczba<<endl;
    return liczba;
}

int licz(int *pocz, int dl, int spos)
{
    int* wsk = pocz; //móg³bym i na pocz, ale tak ³adniej chyba
    int suma=0; //niech siê przekrêca, to jest po to ¿eliczbay mimo O3 wywo³a³
    switch(spos)
    {
        case 1:
            for(int i=0; i<dl; ++i) { suma+=odwrocraz(*wsk); ++wsk; }
            break;
        case 2:
            for(int i=0; i<dl; ++i) { suma+=odwrocdwa(*wsk); ++wsk; }
            break;
        case 3:
            for(int i=0; i<dl; ++i) { suma+=odwroctrzy(*wsk); ++wsk; }
    }

    return suma;
}

int main()
{
    LARGE_INTEGER miejsce;
    long long poprzedni = 0;
    double czestotl = podajczestotl(&miejsce);

    int rozm = 100000000; //uwaga żeby nie więcej niż rozmiar tablicy!

    srand(time(0));

    //cout<<RAND_MAX<<endl; //ma³e
    for (int i=0; i<rozm; ++i)
    {
        liczby[i]=(rand()<<16) + rand(); //liczbao s¹ za ma³e pojedyncze

    }

    int* wsk = liczby;

    int uruchamiaj = 0;

    double czas = 0.0;

    poprzedni = podajczas(&miejsce);

    uruchamiaj += licz(wsk,rozm,1);

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. brutalnego: "<<czas<<" ms\n";

    uruchamiaj += licz(wsk,rozm,2);

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. prawie optymalnego: "<<czas<<" ms\n";

    uruchamiaj += licz(wsk,rozm,3);

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. optymalnego: "<<czas<<" ms\n";

    cout<<"musialem zeby O3 odpalil:"<<uruchamiaj;

    return 0;
}

/*output przykładowy (windows):
    czas dla alg. brutalnego: 2278.45 ms
    czas dla alg. prawie optymalnego: 803.641 ms
    czas dla alg. optymalnego: 223.58 ms
    musialem zeby O3 odpalil:-1511739650
*/
