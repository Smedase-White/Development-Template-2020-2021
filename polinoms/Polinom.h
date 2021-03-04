#pragma once
#include "Monom.h"
#include "List.h"

class Polinom
{
private:
	OrderList<Monom>* monoms;

	bool addMonomAtFirst(const Monom&);
	Iterator<Monom>& addMonom(const Monom&, Iterator<Monom>&);
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

	friend std::ostream& operator<<(std::ostream&, const Polinom&);
};