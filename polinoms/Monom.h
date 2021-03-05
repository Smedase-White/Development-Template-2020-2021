#pragma once
#include <iostream>
#include <cmath>
#include <stdarg.h>

typedef unsigned int degree_storage;

const unsigned int MONOM_BASE = 101;
const unsigned int VARS_COUNT = 3;
const degree_storage MAX_COMPESSED_DEGREE = pow(MONOM_BASE, VARS_COUNT);

struct fullDegrees
{
	unsigned int values[VARS_COUNT];
	fullDegrees(const degree_storage& compressedDegrees)
	{
		if (compressedDegrees >= MAX_COMPESSED_DEGREE)
			throw std::logic_error("Invalie compressed degree.");
		degree_storage temp = compressedDegrees;
		for (unsigned int& d: values)
		{ 
			d = temp % MONOM_BASE; 
			temp /= MONOM_BASE; 
		} 
	};
	fullDegrees(const unsigned int*& pDegrees)
	{ 
		for (int i = 0; i < VARS_COUNT; i++)
			if (pDegrees[i] >= MONOM_BASE)
				throw std::logic_error("Invalie degree.");
			else
				values[i] = pDegrees[i];
	};
	fullDegrees(const unsigned int x1, const unsigned int x2, ...)
	{
		va_list vars;
		va_start(vars, x1);
		if (x1 >= MONOM_BASE)
			throw std::logic_error("Invalie degree.");
		values[0] = x1;
		int temp;
		for (int i = 1; i < VARS_COUNT; i++)
		{
			temp = va_arg(vars, int);
			if (temp >= MONOM_BASE)
				throw std::logic_error("Invalie degree.");
			else
				values[i] = temp;
		}
		va_end(vars);
	};
};

struct compressedDegrees
{
	degree_storage value;
	compressedDegrees(const degree_storage& compressedDegrees = 0)
	{
		if (compressedDegrees >= MAX_COMPESSED_DEGREE)
			throw std::logic_error("Invalie compressed degree.");
		value = compressedDegrees;
	};
	compressedDegrees(const fullDegrees& fullDegrees)
	{ 
		value = 0;
		degree_storage temp = 1;
		for (int i = 0; i < VARS_COUNT; i++) 
		{ 
			value += temp * fullDegrees.values[i];
			temp *= MONOM_BASE;
		} 
	};
};

class Monom
{
private:
	double coef;
	compressedDegrees degrees;
public:
	Monom(const double& coef, const compressedDegrees& = compressedDegrees(0));
	Monom(const Monom&);

	Monom& operator=(const Monom&);
	Monom operator+(const Monom&) const;
	Monom& operator+=(const Monom&);
	Monom operator-(const Monom&) const;
	Monom& operator-=(const Monom&);
	Monom operator*(const Monom&) const;
	Monom& operator*=(const Monom&);
	bool operator==(const Monom& monom) const { return (this->degrees.value == monom.degrees.value); };
	bool operator!=(const Monom& monom) const { return (this->degrees.value != monom.degrees.value); };
	bool operator>(const Monom& monom) const { return (this->degrees.value > monom.degrees.value); };
	bool operator>=(const Monom& monom) const { return (this->degrees.value >= monom.degrees.value); };
	bool operator<(const Monom& monom) const { return (this->degrees.value < monom.degrees.value); };
	bool operator<=(const Monom& monom) const { return (this->degrees.value <= monom.degrees.value); };

	double getValue(const double, const double, ...);
	double getValue(const double*&);
	double getValue(const double[VARS_COUNT]);

	double getCoef() const { return this->coef; } ;

	bool checkDegrees(const compressedDegrees&) const;
	bool checkDegrees(const Monom&) const;

	friend std::ostream& operator<<(std::ostream&, const Monom&);
};