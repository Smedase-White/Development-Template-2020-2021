#pragma once
#include "Monom.h"
#include "List.h"

class Polinom
{
private:
	OrderList<Monom>* monoms;
public:
	Polinom();
	Polinom(const Monom&);
	Polinom(const Polinom&);
	~Polinom();

	Polinom& operator=(const Polinom&);
	Polinom operator+(const Polinom&) const;
	Polinom& operator+=(const Polinom&);
	Polinom operator-(const Polinom&) const;
	Polinom& operator-=(const Polinom&);
	Polinom operator*(const Polinom&) const;
	Polinom& operator*=(const Polinom&);

	double getValue(const double, const double, ...);
	double getValue(const double*&);
	double getValue(const double[VARS_COUNT]);

	int getCoef()
	{
		int result = 0;
		Iterator<Monom> i = monoms->getIterator();
		while (i.hasNext())
			result += i.next().getCoef();
		return result;
	}

	friend std::ostream& operator<<(std::ostream&, const Polinom&);
};