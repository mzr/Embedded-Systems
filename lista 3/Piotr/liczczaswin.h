#include<windows.h>
#include<iostream>

using namespace std;

long long podajczestotl(LARGE_INTEGER* wsk)
{
    //w tym o adresie wsk pojawi si� cz�stotliwo��, chyba �e nie wspiera, ale musia�by wcze�niejszy ni� XP
    if (!QueryPerformanceFrequency(wsk)) {cout<<"cz�stotliwo�� pono� 0"; return 1;}
    double czestotl = double(wsk->QuadPart)/1000.0; //przez 1000, bo w ms
        //QuadPart, bo procek ogarnia 64-bitowe
    return czestotl;
}

long long podajczas(LARGE_INTEGER* wsk)
{
    QueryPerformanceCounter(wsk); //dostanie tam ile sekund w long longu od kiedy�tam
    return wsk->QuadPart;
}

double mierzczas(LARGE_INTEGER* wsk, long long poprzedni, double czestotl)
{
    QueryPerformanceCounter(wsk);
    return (double(wsk->QuadPart-poprzedni)/czestotl);
}

