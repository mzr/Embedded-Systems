#include <iostream>
#include <cstring>

using namespace std;

void spacesFront1(char *tab, size_t length)
{	
	for(size_t j=0; j<length-1; j++)
		for(size_t i=length-1; i>j; i--)
			if(tab[i] == ' ')
				swap(tab[i],tab[i-1]);	
}

void spacesFront2(char *tab, size_t length)
{
	int n = length - 1;
	int spaces = length - 1;

   for( int i=n; i>=0; i-- )
   {
   	if(tab[i] != ' ')
      tab[spaces--] = tab[i];
   }
     
   while( spaces >= 0 )
   	tab[spaces--] = ' ';
}



int main()
{	
	char tab1[] = 
		#include "napis"
	;

	char tab2[] = 
		#include "napis"
	;

	long s1,s2;
	long e1,e2;

	s1 = clock();
	spacesFront1(tab1,strlen(tab1));
	e1 = clock();
	cout << " " << 1.0*(e1-s1)/CLOCKS_PER_SEC << endl;

	s2 = clock();
	spacesFront2(tab2,strlen(tab2));
	e2 = clock();
	cout << " " << 1.0*(e2-s2)/CLOCKS_PER_SEC << endl;


	
	return 0;
}