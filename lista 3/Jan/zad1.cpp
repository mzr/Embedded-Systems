#include <iostream>
#include <fstream>
#include <time.h>
#include <sys/time.h>
#include <ctime>
#include <unistd.h>

using namespace std;

// 944933439 - zer
// 1258310522 - jedynek

unsigned int precalc1[1 << 8];
unsigned int precalc2[1 << 16];

// naive bitcount
template <typename T> inline unsigned int bitcount(T x) 
{ 
	unsigned int count = 0;
   
   for(;x!=0; x>>=1)
   	if((x & 1) == 1)
   		count++;

   return count;
}

void applyPrecalc( unsigned int *precalc, unsigned int ile)
{
	for(unsigned long long int i = 0; i< ile; i++)
		// precalc[i] = bitcount(i);
		precalc[i] = __builtin_popcount(i);
}

unsigned long int brute(unsigned char *file, size_t size)
{
	unsigned long int sum = 0;
	for(size_t i = 0; i<size; i++)
		sum += bitcount(file[i]);
		// sum += __builtin_popcount(file[i]);

	return sum;
}

unsigned long int optimal1(unsigned char *file, size_t size)
{
	unsigned long int sum = 0;
	for(size_t i = 0; i<size; i++)
		sum += precalc1[file[i]];

	return sum; 
}

unsigned long int optimal2(unsigned char *file, size_t size)
{
	unsigned long int sum = 0;
	unsigned short int *_file = (unsigned short int*)file;

	size >>= 1;
	for( size_t i=0; i<size; i++)
		sum += precalc2[_file[i]];
	
	return sum;
}


unsigned long int optimal3(unsigned char *file, size_t size)
{
	unsigned long int sum = 0;
 
   unsigned int* _file = (unsigned int*) file;
   unsigned int v;
 	
 	size >>= 2;
   for (size_t i = 0; i < size; i++) {
   	v = _file[i];
      v = v - ((v >> 1) & 0x55555555);
      v = (v & 0x33333333) + ((v >> 2) & 0x33333333);    
      sum += ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
   }
 
   return sum;
}

template <typename T> void showbits(T x)
{
	int i; 
	for(i=(sizeof(T)*8)-1; i>=0; i--)
		(x&(1u<<i))?putchar('1'):putchar('0');
    
   printf("\n");
}

int main()
{
	streampos size;
	unsigned char *memblock;

	ifstream file("random", ios::in | ios::binary | ios::ate);
	if(file.is_open())
	{
		size = file.tellg();
		memblock = new unsigned char [size];
		file.seekg(0,ios::beg);
		file.read((char*)memblock,size);
		file.close();
	}
	
	long s1,s2,s3,s4;
	long e1,e2,e3,e4;

	cout << "brute:\t\t";
	s1 = clock();
	cout << brute(memblock,size);
	e1 = clock();
	cout << " " << 1.0*(e1-s1)/CLOCKS_PER_SEC << endl;

	cout << "precalc1:\t"; 
	applyPrecalc(precalc1,1<<8);
	s2 = clock();
	cout << optimal1(memblock,size);
	e2 = clock();
	cout << " " << 1.0*(e2-s2)/CLOCKS_PER_SEC << endl;

	cout << "precalc2:\t"; 
	applyPrecalc(precalc2,1<<16);
	s3 = clock();
	cout << optimal2(memblock,size);
	e3 = clock();
	cout << " " << 1.0*(e3-s3)/CLOCKS_PER_SEC << endl;

	cout << "masks:\t\t"; 
	s4 = clock();
	cout << optimal3(memblock,size);
	e4 = clock();
	cout << " " << 1.0*(e4-s4)/CLOCKS_PER_SEC << endl;

	return 0;
}