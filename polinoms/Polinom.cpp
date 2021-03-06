#include "Polinom.h"

Polinom::Polinom()
{
	this->monoms = new LinkList<Monom>();
}

Polinom::Polinom(const Monom& monom)
{
	this->monoms = new LinkList<Monom>();
	this->monoms->addFirst(monom);
}

Polinom::Polinom(const Polinom& polinom)
{
	this->monoms = new LinkList<Monom>(*polinom.monoms);
}

Polinom::~Polinom()
{
	this->monoms->~LinkList();
	delete this->monoms;
}

Polinom& Polinom::operator=(const Polinom& polinom)
{
	this->monoms->~LinkList();
	this->monoms = new LinkList<Monom>(*polinom.monoms);
	return *this;
}

Polinom Polinom::operator+(const Polinom& polinom) const
{
	if (this->monoms->empty())
		return polinom;
	if (polinom.monoms->empty())
		return *this;
	Polinom result;
	Iterator<Monom> main = this->monoms->begin();
	Iterator<Monom> second = polinom.monoms->begin();
	while (main.hasNext() && second.hasNext())
	{
		if (main.current() < second.current())
			result.monoms->addLast(second.next());
		else
			if (main.current() > second.current())
				result.monoms->addLast(main.next());
			else
				result.monoms->addLast(main.next() + second.next());
	}
	while (main.hasNext())
		result.monoms->addLast(main.next());
	while (second.hasNext())
		result.monoms->addLast(second.next());

	return result;
}

Polinom& Polinom::operator+=(const Polinom& polinom)
{
	* this = *this + polinom;
	return *this;
}

Polinom Polinom::operator-(const Polinom& polinom) const
{
	return *this + polinom * Polinom(Monom(-1));
}

Polinom& Polinom::operator-=(const Polinom& polinom)
{
	*this += polinom * Polinom(Monom(-1));
	return*this;
}

Polinom Polinom::operator*(const Polinom& polinom) const
{
	if (!this->monoms->getFirst().checkDegrees(polinom.monoms->getFirst()))
		throw std::logic_error("Degrees is big.");
	Polinom result;
	Iterator<Monom> main = this->monoms->begin();
	while (main.hasNext())
	{
		Polinom temp;
		if (main.current().getCoef() == 0)
			continue;
		Iterator<Monom> second = polinom.monoms->begin();
		while (second.hasNext())
		{
			if (second.current().getCoef() != 0)
				temp.monoms->addLast(main.current() * second.current());
			second.next();
		}
		result += temp;
		main.next();
	}
	return result;
}

Polinom& Polinom::operator*=(const Polinom& polinom)
{
	*this = *this * polinom;
	return*this;
}

double Polinom::getValue(const double x1, const double x2, ...)
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

double Polinom::getValue(const double*& _values)
{
	double values[VARS_COUNT];
	for (int i = 0; i < VARS_COUNT; i++)
		values[i] = _values[i];
	return (this->getValue(values));
}

double Polinom::getValue(const double _values[VARS_COUNT])
{
	double values[VARS_COUNT];
	for (int i = 0; i < VARS_COUNT; i++)
		values[i] = _values[i];
	double result = 0;
	Iterator<Monom> main = this->monoms->begin();
	while (main.hasNext())
		result += main.next().getValue(values);
	return result;
}

std::ostream& operator<<(std::ostream& ostr, const Polinom& polinom)
{
	Iterator<Monom> iter = polinom.monoms->begin();
	while (iter.hasNext())
		ostr << iter.next() << '\n';
	return ostr;
}