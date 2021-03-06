#include <iostream>
#include "Polinom.h"
#include <ctime>

using namespace std;

void check()
{
	Polinom p1;
	Polinom p2;
	unsigned int* a = new unsigned int[3];
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			for (int z = 0; z < 11; z++)
			{
				//rand() % 100 - 50
				fullDegrees b(a);
				a[0] = x; a[1] = y; a[2] = z;
				p1 += Monom(1, b);
				p2 += Monom(1, b);
			}
		}
	}
	//cout << p1;
	clock_t t = clock();
	Polinom p3 = p1 * p2;
	std::cout << (float) (clock() - t) / CLOCKS_PER_SEC << " s\n";
	const double _values[VARS_COUNT] = { 1, 1 ,1 };
	cout << p3.getValue(_values) << '\n';
	cout << p3.getCoef() << '\n';
}

int main()
{
	for (int i = 0; i < 1; i++)
	{
		cout << i << ": ";
		check();
	}
	return 0;
}