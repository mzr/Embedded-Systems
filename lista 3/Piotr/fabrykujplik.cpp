
#include<iostream>
#include<stdio.h>
#include<stdlib.h> //malloc
#include<time.h>

using namespace std;



int main()
{
    srand(time(0));

    FILE *f;

    f=fopen("plik", "wb"); //będzie bez rozszerzenia chyba, na win ok??

    for (int i=0; i<500000000; ++i) //500 000 000 bajtów to > 300 MB
    {
        int znak = (unsigned char)rand();
        //cout<<znak<<endl;
        //fputc(znak,f);
        fwrite(&znak,sizeof(char),1,f);
    } //to długo trwa

    fclose(f);

    return 0;
}
