#include <iostream>
#include <fstream>

using namespace std;

size_t countInt(unsigned int v)
{
	v = v - ((v >> 1) & 0x55555555);
   v = (v & 0x33333333) + ((v >> 2) & 0x33333333);    
	return ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
}


size_t count1(unsigned char* file, size_t size)
{
	size_t sum = 0;
	unsigned int *_file = (unsigned int*)file;
	size /= 4;
	for(size_t i = 0; i<size; i++)
		if(countInt(~_file[i]) >= 2)
			sum ++;

	return sum;
}

size_t count2(unsigned char* file, size_t size)
{
	size_t sum = 0;
	unsigned int *_file = (unsigned int*)file;
	size /= 4;
	for(size_t i = 0; i<size; i++)
		if(__builtin_popcount(~_file[i]) >= 2)
			sum ++;

	return sum;
}

size_t count3(unsigned char* file, size_t size)
{
	size_t sum = 0;
	unsigned int *_file = (unsigned int*)file;
	size /= 4;
	for(size_t i = 0; i<size; i++)
	{
		unsigned int count = 0;
   		unsigned int check = ~_file[i];
   		for(; check!=0; check>>=1){
   			if((check & 1) == 1)
   				count++;
   			if(count >= 2){
   				sum++;
   				break;
   			}
   		}
	}
	return sum;
}

size_t count4(unsigned char* file, size_t size)
{
	size_t sum = 0;
	unsigned int *_file = (unsigned int*)file;
	size >>= 2;
	for(size_t i = 0; i<size; i++)
	{
		unsigned int neg = ~_file[i];
		if(neg & (neg-1) )
			sum++;
	}
	return sum;
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
	
	s1 = clock();
	cout << count1(memblock,size) << endl;
	e1 = clock();

	s2 = clock();
	cout << count2(memblock,size) << endl;
	e2 = clock();

	s3 = clock();
	cout << count3(memblock,size) << endl;
	e3 = clock();

	s4 = clock();
	cout << count4(memblock,size) << endl;
	e4 = clock();

	cout << "1)\t" << 1.0*(e1-s1)/CLOCKS_PER_SEC << endl;
	cout << "2)\t" << 1.0*(e2-s2)/CLOCKS_PER_SEC << endl;
	cout << "3)\t" << 1.0*(e3-s3)/CLOCKS_PER_SEC << endl;
	cout << "4)\t" << 1.0*(e4-s4)/CLOCKS_PER_SEC << endl;

	return 0;
}