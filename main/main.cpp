#include <iostream>
#include "Polinom.h"
#include <ctime>

using namespace std;

void check()
{
	Polinom p1;
	Polinom p2;
	for (int x = 0; x < 51; x++)
	{
		for (int y = 0; y < 51; y++)
		{
			for (int z = 0; z < 51; z++)
			{
				//rand() % 100 - 50
				p1 += Monom(1, fullDegrees(x, y, z));
				p2 += Monom(1, fullDegrees(x, y, z));
			}
		}
	}
	clock_t t = clock();
	Polinom p3 = p1 * p2;
	std::cout << (float) (clock() - t) / CLOCKS_PER_SEC << " s\n";
	//cout << p3.getValue(1., 1., 1.) << '\n';
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