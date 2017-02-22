
#include<iostream>
#include<stdio.h>
#include<stdlib.h> //malloc
#include<time.h>
#include<windows.h>

#include "liczczaswin.h"

using namespace std;

unsigned int liczby[100000000];

int licz1(unsigned int *pocz, int dl)
{
    unsigned int* wsk = pocz; //móg³bym i na pocz, ale tak ³adniej chyba
    int suma=0;
    for(int i=0; i<dl; ++i)
    {
        short j=0; unsigned int k=~(*wsk); //nie ma znacz. czy unsigned dla bitów, ale bez tego siê nie skoñczy bo 0
        //mia³ byæ brut, to bêdzie brut
        for(; k; k>>=1) { j+=k&1; /*cout<<(k&1)<<' ';*/ }
        //cout<<"!"<<j<<endl;
        if (j>=2) ++suma;
        ++wsk;
    }

    return suma;
}

int licz2(unsigned int *pocz, int dl)
{
    unsigned int* wsk = pocz; //móg³bym i na pocz, ale tak ³adniej chyba
    int suma=0;

    for(int i=0; i<dl; ++i)
    {
        int k=~(*wsk); //int nie ma znaczenia dla bitów
        //stąd : https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
        /*nawiasowanie!*/ if ( (k & (k-1)) != 0) ++suma; //wtedy negacja nie jest potêg¹ dwójki ani zerem, czyli ma >= 2 bity zapalone
        //tylko dla potêgi 2'ki przy -1 zniknie najznaczniejszy bit i siê nie z-enduje (&)
        ++wsk;
    }

    return suma;
}

int main()
{
    srand(time(0));

    LARGE_INTEGER miejsce;
    long long poprzedni = 0;
    double czestotl = podajczestotl(&miejsce);

    int rozm = 100000000; //uwaga żeby nie więcej niż rozmiar tablicy!
    //100 mln intów to 100*10^6*32 bitów, czyli jest 300MB (to > 300*10^24*8)

    //cout<<RAND_MAX<<endl; //ma³e
    for (int i=0; i<rozm; ++i)
    {
        liczby[i]=(rand()<<16) + rand(); //bo s¹ za ma³e pojedyncze
        //liczby[i]=~1; //działa - po tym daje że 0 liczb
        //cout<<liczby[i]<<endl;
    }


    unsigned int* wsk = liczby;

    double czas = 0.0;

    poprzedni = podajczas(&miejsce);

    cout<<licz1(wsk,rozm)<<endl;

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. brutalnego: "<<czas<<" ms\n";

    cout<<licz2(wsk,rozm)<<endl;

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. optymalnego: "<<czas<<" ms\n";

    return 0;
}

/*output przykładowy (windows):
    100000000
    czas dla alg. brutalnego: 2341.69 ms
    100000000
    czas dla alg. optymalnego: 72.5742 ms
*/
