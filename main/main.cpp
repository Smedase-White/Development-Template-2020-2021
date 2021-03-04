#include <iostream>
#include "Polinom.h"
#include <ctime>

using namespace std;

void check()
{
	Polinom p1;
	Polinom p2;
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			for (int z = 0; z < 11; z++)
			{
				p1 += Monom(rand() % 100 - 50, fullDegrees(x, y, z));
				p2 += Monom(rand() % 100 - 50, fullDegrees(x, y, z));
			}
		}
	}
	time_t t = time(0);
	Polinom p3 = p1 * p2;
	std::cout << time(0) - t << '\n';
	cout << p3.getValue(1., 1., 1.) << '\n';
}

int main()
{
	for (int i = 0; i < 3; i++)
	{
		cout << i << ": ";
		check();
	}
	return 0;
}