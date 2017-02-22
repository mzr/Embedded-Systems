
#include<iostream>
#include<stdio.h>
#include<stdlib.h> //malloc
#include<windows.h>

#include "liczczaswin.h"

using namespace std;
//żeby przerobić na C, trzeba pewnie zm. wypisywanie bo nie ma cin
//bez using, i też -std=c99 w opcjach kompilatora, bo inaczej nie można inic. w for...


int liczbrut(unsigned char* pocz, unsigned char* konc)
{
    int licznik=0; unsigned char teraz;
    //cout<<*pocz<<" "<<*konc<<endl;
    for(unsigned char* i=pocz; i<konc; ++i) //ogarnia ¿e zwiêkszyæ o rozm. char
    {
        teraz = *i;
        short j=0; unsigned char k=teraz;
        //for(j=0; k; j++) k^= k& -k;
        //miał być brut, to będzie brut
        for(; k; k>>=1) j+=k&1;
        licznik+=(int)j;
    }
    return licznik;
}

int liczraz(unsigned char* pocz, unsigned char* konc, short* pre)
{
    int licznik=0; unsigned char teraz;
    //cout<<*pocz<<" "<<*konc<<endl;
    for(unsigned char* i=pocz; i<konc; ++i) //ogarnia ¿e zwiêkszyæ o rozm. char
    {
        teraz = *i;
        licznik += (int)*(pre+teraz);
    }
    return licznik;
}

int liczdwa(unsigned short* pocz, unsigned short* konc, short* pre)
{
    int licznik=0; unsigned short teraz;
    //cout<<*pocz<<" "<<*konc<<endl;
    for(unsigned short* i=pocz; i<konc; ++i) //ogarnia że zwiększyć o rozm. char
    {
        teraz = *i;
        licznik += (int)*(pre+teraz);
    }
    return licznik;
}

int licztrzy(unsigned short* pocz, unsigned short* konc)
{

    int licznik=0;
    unsigned short k; //chociaż na shortach żeby był jakiś zysk z tego że nie po bitach
    for(unsigned short* i=pocz; i<konc; ++i) //ogarnia że zwiększyć o rozm. char
    {
        //wzięte ze slajdów
        k=*i;
        k -= ((k >> 1) & 0x55555555);
        k = (k & 0x33333333) + ((k >> 2) & 0x33333333);
        k = (k + (k >> 4)) & 0x0F0F0F0F;
        k = (k * 0x01010101) >> 24;
        licznik+=(int)k;
    }
    return licznik;
}

int main()
{
    LARGE_INTEGER miejsce;
    long long poprzedni = 0;
    double czestotl = podajczestotl(&miejsce);

    FILE *f;

    f=fopen("plik", "rb"); //dla "plik.txt gdzie 5 spacji po 1 widać że działa"
    fseek(f,0,SEEK_END); //daje wskaźnik na koniec
    int rozm = ftell(f); //mówi ile od początku, jak "rb" otwarty, to w bajtach
                         //ale char ma bajt, więc i tak to samo
    rewind(f);
    cout<<"rozm.: "<<rozm<<endl;
    char* jakoChar;
    short* jakoShort;



    jakoChar = (char*)malloc((rozm+rozm%2)*sizeof(char));
    jakoShort = (short*)jakoChar;
    if(jakoChar==NULL){cout<<"błąd alokacji"; return 0;}

    char* wsk = jakoChar;

    char tenznak;

    /*while((tenznak=fgetc(f)) != EOF) //można by też użyć (ptr* dokąd, jakiego rozm zmienna, ile zmiennych, plik)
    {
        *wsk = tenznak;
        ++wsk;
    }*/ //to nie działało, chyba rozpoznał coś po drodze jako EOF

    fread(jakoChar, sizeof(char), rozm, f);

    fclose(f);

    if(rozm%2 != 0) *(jakoChar+rozm) = (char)(0); //to jest 0 i nie zmieni liczby, a nie wyjdzie poza pamięć na pewno

    short tabchar[256];
    short tabshort[65536];

    unsigned char zaschar = 255;
    unsigned short zasshort = 65535;
    for (int i=0; i<=zaschar; ++i)
    {
        short j; unsigned char k=i;
        for(j=0; k; j++) k^= k& -k;
        tabchar[i]=j;
    }

    for (int i=0; i<=zasshort; ++i)
    {
        short j; unsigned short k=i;
        for(j=0; k; j++) k^= k& -k;
        tabshort[i]=j;
    }

    //cout<<tabshort[1]<<endl<<tabshort[3]<<endl;

    int zapaloneraz, zapalonedwa, zapalonetrzy;

    zapaloneraz=zapalonedwa=zapalonetrzy=0; //inta nie współdzieli

    char* koniecpliku = jakoChar + rozm;

    poprzedni = podajczas(&miejsce);

    double czas=0.0;

    cout<<liczbrut((unsigned char*)jakoChar,(unsigned char*)koniecpliku)<<endl;

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. brutalnego: "<<czas<<" ms\n";

    cout<<liczraz((unsigned char*)jakoChar,(unsigned char*)koniecpliku,tabchar)<<endl;

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. precalc 256: "<<czas<<" ms\n";

    cout<<liczdwa((unsigned short*)jakoChar,(unsigned short*)koniecpliku,tabshort)<<endl;

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. precalc 65536: "<<czas<<" ms\n";

    cout<<licztrzy((unsigned short*)jakoChar,(unsigned short*)koniecpliku)<<endl;

    czas = mierzczas(&miejsce, poprzedni, czestotl);
    poprzedni = podajczas(&miejsce);
    cout<<"czas dla alg. lepsze maski bez precalc: "<<czas<<" ms\n";

    return 0;
}

/*output przykładowy (windows):
    rozm.: 500000000
    2000000796
    czas dla alg. brutalnego: 4557.54 ms
    2000000796
    czas dla alg. precalc 256: 271.39 ms
    2000000796
    czas dla alg. precalc 65536: 163.992 ms
    2000000796
    czas dla alg. lepsze maski bez precalc: 640.454 ms

*/
