#include "Monom.h"

bool Monom::checkDegrees(const compressedDegrees& compressedDegrees) const
{
	if (this->degrees.value == 0 || compressedDegrees.value == 0)
		return true;
	int temp1 = this->degrees.value;
	int temp2 = compressedDegrees.value;
	for (int i = 0; i < VARS_COUNT; i++)
	{
		if (temp1 % MONOM_BASE + temp2 % MONOM_BASE >= MONOM_BASE)
			return false;
		temp1 /= MONOM_BASE;
		temp2 /= MONOM_BASE;
	}
	return true;
}

bool Monom::checkDegrees(const Monom& monom) const
{
	return this->checkDegrees(monom.degrees);
}

Monom::Monom(const double& coef, const compressedDegrees& compressedDegrees)
{
	this->degrees.value = compressedDegrees.value;
	this->coef = coef;
}

Monom::Monom(const Monom& monom)
{
	this->degrees = monom.degrees;
	this->coef = monom.coef;
}

Monom& Monom::operator=(const Monom& monom)
{
	this->coef = monom.coef;
	this->degrees = monom.degrees;
	return *this;
}

Monom Monom::operator+(const Monom& monom) const
{
	if (this->degrees.value != monom.degrees.value)
		throw std::logic_error("—тепени при мономах не равны, их нельз€ сложить.");
	Monom result(*this);
	result.coef = result.coef + monom.coef;
	return result;
}

Monom& Monom::operator+=(const Monom& monom)
{
	if (this->degrees.value != monom.degrees.value)
		throw std::logic_error("—тепени при мономах не равны, их нельз€ сложить.");
	this->coef = this->coef + monom.coef;
	return *this;
}

Monom Monom::operator-(const Monom& monom) const
{
	if (this->degrees.value != monom.degrees.value)
		throw std::logic_error("—тепени при мономах не равны, их нельз€ вычесть.");
	Monom result(*this);
	result.coef = result.coef - monom.coef;
	return result;
}

Monom& Monom::operator-=(const Monom& monom)
{
	if (this->degrees.value != monom.degrees.value)
		throw std::logic_error("—тепени при мономах не равны, их нельз€ вычесть.");
	this->coef = this->coef - monom.coef;
	return *this;
}

Monom Monom::operator*(const Monom& monom) const
{
	/*if (!this->checkDegrees(monom.effectiveDegree))
		throw std::logic_error("—тепени при мономах слишком большие, их нельз€ перемножить.");*/
	Monom result(*this);
	result.coef = result.coef * monom.coef;
	result.degrees.value = result.degrees.value + monom.degrees.value;
	return result;
}

Monom& Monom::operator*=(const Monom& monom)
{
	/*if (!this->checkDegrees(monom.effectiveDegree))
		throw std::logic_error("—тепени при мономах слишком большие, их нельз€ перемножить.");*/
	this->coef = this->coef * monom.coef;
	this->degrees.value = this->degrees.value + monom.degrees.value;
	return *this;
}

double Monom::getValue(const double x1, const double x2, ...)
{
	double values[VARS_COUNT];
	va_list vars;
	va_start(vars, x1);
	values[0] = x1;
	for (int i = 1; i < VARS_COUNT; i++)
		values[i] = va_arg(vars, double);
	va_end(vars);
	return (this->getValue(values));
}

double Monom::getValue(const double*& _values)
{
	double values[VARS_COUNT];
	for (int i = 0; i < VARS_COUNT; i++)
		values[i] = _values[i];
	return (this->getValue(values));
}

double Monom::getValue(const double _values[VARS_COUNT])
{
	if (this->degrees.value == 0)
		return this->coef;
	double result = this->coef;
	fullDegrees degrees(this->degrees.value);
	for (int i = 0; i < VARS_COUNT; i++)
		result *= pow(_values[i], degrees.values[i]);
	return result;
}

std::ostream& operator<<(std::ostream& ostr, const Monom& monom)
{
	fullDegrees degrees(monom.degrees.value);
	ostr << monom.coef;
	for (int i = 0; i < VARS_COUNT; i++)
		ostr << " * x" << i << "^" << degrees.values[i];
	return ostr;
}