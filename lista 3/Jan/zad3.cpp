#include <iostream>
#include <fstream>

using namespace std;


template <typename T> void showbits(T x)
{
	int i; 
	for(i=(sizeof(T)*8)-1; i>=0; i--)
		(x&(1u<<i))?putchar('1'):putchar('0');
   printf("\n");
}


void reverse1(unsigned int &x)
{
	unsigned int r = x;
	int s = 31;
	for (x >>= 1; x; x >>= 1)
	{   
  		r <<= 1;
  		r |= x & 1;
  		s--;
	}	
	x = r <<= s;
}

void reverse2(unsigned int &x)
{
	unsigned int s = 32;
	unsigned int mask = ~0;         
	while ((s >>= 1) > 0) 
	{
  		mask ^= (mask << s);
  		x = ((x >> s) & mask) | ((x << s) & ~mask);
	}
}

void reverse3(unsigned int &x)
{
	x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
	x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
	x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
	x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
	x = ( x >> 16             ) | ( x               << 16);
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

	size_t _size = size/4;
	unsigned int* _file = (unsigned int*)memblock;

	long s1,s2,s3,s4;
	long e1,e2,e3,e4;

	unsigned int tst = 1234;

	showbits(tst);
	cout << endl;

	s1 = clock();
	// reverse1(tst);
	for(size_t i=0; i<_size; i++)
		reverse1(_file[i]);
	e1 = clock();
	
	showbits(tst);
	cout << endl;

	s2 = clock();
	// reverse2(tst);
	for(size_t i=0; i<_size; i++)
		reverse2(_file[i]);
	e2 = clock();

	showbits(tst);
	cout << endl;

	s3 = clock();
	// reverse3(tst);
	for(size_t i=0; i<_size; i++)
		reverse3(_file[i]);
	e3 = clock();

	showbits(tst);
	cout << endl;

	cout << "1)\t" << 1.0*(e1-s1)/CLOCKS_PER_SEC << endl;
	cout << "2)\t" << 1.0*(e2-s2)/CLOCKS_PER_SEC << endl;
	cout << "3)\t" << 1.0*(e3-s3)/CLOCKS_PER_SEC << endl;
	return 0;
}