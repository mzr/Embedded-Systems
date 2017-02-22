#include<iostream>
#include<stdio.h>
#include<stdlib.h> //malloc

#include "liczczaswin.h"

using namespace std;

void przesunBrut(char* pocz, int dl)
{
    char* wsk = pocz; //mógłbym i na pocz, ale tak ładniej chyba
    char znak;
    for(int i=0; i<dl; ++i)
    {
        znak = *wsk;
        if (znak== ' ' && i!=0)
        {
            char* zamiany = wsk;
            while (zamiany > pocz && *(zamiany-1) != ' ') //-1 ok, bo i nie 0
            {
                *(zamiany) = *(zamiany-1);
                --zamiany;
            }
            *(zamiany)=' '; //bo jeszcze ją trzeba przenieść
        }
        ++wsk;

    }
}

void przesunSpryt(char* pocz, int dl)
{
    int bylo = 0;
    char* konc = pocz+(dl-1);
    char znak;
    for(int i=0; i<dl; ++i)
    {
        znak = *konc;
        if (znak== ' ') { ++bylo; }
        else if (bylo)
        {
            *(konc) = *(konc+bylo);
            *(konc+bylo)=znak;
        }
        --konc;
    }
}

void inicjujnapis(char* pocz, int dziesznakow)
{
    char* wsk2=pocz;
    for (int i=0; i<dziesznakow; ++i)
    {
        *wsk2='a'; ++wsk2;
        *wsk2='b'; ++wsk2;
        *wsk2='c'; ++wsk2;
        *wsk2='d'; ++wsk2;
        *wsk2='e'; ++wsk2;
        *wsk2=' '; ++wsk2;
        *wsk2='f'; ++wsk2;
        *wsk2='g'; ++wsk2;
        *wsk2='h'; ++wsk2;
        *wsk2=' '; ++wsk2;

    }
}

void wypisznapis(char* pocz, int dziesznakow)
{
    char* wsk2=pocz;
    for(int i=0; i<10*dziesznakow; ++i)
    {
        cout<<*wsk2;
        wsk2++;
    }
    cout<<"\n";
}

int main()
{
    LARGE_INTEGER miejsce;
    long long poprzedni = 0;
    double czestotl = podajczestotl(&miejsce);

    int rozm = 30000; //u mnie brut to robił 4 sekundy

    char* wsk = (char*) malloc(10*rozm*sizeof(char));

    double czas=0.0;

    inicjujnapis(wsk,rozm);

    poprzedni = podajczas(&miejsce);

    przesunBrut(wsk,10*rozm); //uwaga na rozm, bo on jest kwadratowy!!

    //wypisznapis(wsk,rozm);
    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. brutalnego: "<<czas<<" ms\n";

    inicjujnapis(wsk,rozm);

    przesunSpryt(wsk,10*rozm);
    //wypisznapis(wsk,rozm);
    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. optymalnego: "<<czas<<" ms\n";
    return 0;
}
/*output przykładowy (windows):
    czas dla alg. brutalnego: 4043.35 ms
    czas dla alg. optymalnego: 1.03453 ms
*/
