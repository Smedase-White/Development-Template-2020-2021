#include "Polinom.h"

Polinom::Polinom()
{
	this->monoms = new OrderList<Monom>();
}

Polinom::Polinom(const Monom& monom)
{
	this->monoms = new OrderList<Monom>();
	this->monoms->addFirst(monom);
}

Polinom::Polinom(const Polinom& polinom)
{
	this->monoms = new OrderList<Monom>(*polinom.monoms);
}

Polinom::~Polinom()
{
	this->monoms->~OrderList();
	delete this->monoms;
}

Polinom& Polinom::operator=(const Polinom& polinom)
{
	this->monoms->~OrderList();
	this->monoms = new OrderList<Monom>(*polinom.monoms);
	return *this;
}

bool Polinom::addMonomAtFirst(const Monom& monom)
{
	if (monom.getCoef() == 0)
		return false;
	Monom temp(this->monoms->getFirst());
	if (monom > temp)
	{
		this->monoms->addFirst(monom);
		return true;
	}
	else
		if (monom == temp)
		{
			if (monom.getCoef() + temp.getCoef() == 0)
				this->monoms->removeFirst();
			else
				this->monoms->replaceFirst(temp + monom);
			return true;
		}
	return false;
}

Iterator<Monom>& Polinom::addMonom(const Monom& monom, Iterator<Monom>& iter)
{
	if (monom.getCoef() == 0)
		return iter;
	while (iter.hasNext())
	{
		Monom temp = iter.current();
		if (monom > temp)
		{
			iter.add(monom);
			return iter;
		}
		else
			if (monom == temp)
			{
				/*if (monom.getCoef() + temp.getCoef() == 0)
				{
					iter.remove();
					return iter;
				}*/
				iter.replace(temp + monom);
				return iter;
			}
		iter.next();
	}
	iter.add(monom);
	return iter;
}

Polinom Polinom::operator+(const Polinom& polinom) const
{
	if (this->monoms->empty())
		return polinom;
	if (polinom.monoms->empty())
		return *this;
	Polinom result(*this);
	Iterator<Monom> main = result.monoms->getIterator();
	Iterator<Monom> second = polinom.monoms->getIterator();
	Monom a(main.next());
	Monom b(second.next());
	if (result.addMonomAtFirst(b))
	{
		main = result.monoms->getIterator();
		if (second.hasNext())
			b = second.next();
		else
			return result;
	}
	while (second.hasNext())
	{
		main = result.addMonom(b, main);
		b = second.next();
	}
	result.addMonom(b, main);
	return result;
}

Polinom& Polinom::operator+=(const Polinom& polinom)
{
	*this = *this + polinom;
	return *this;
}

Polinom Polinom::operator-(const Polinom& polinom) const
{
	return *this + polinom * Monom(-1);
}

Polinom& Polinom::operator-=(const Polinom& polinom)
{
	*this = *this - polinom;
	return*this;
}

Polinom Polinom::operator*(const Polinom& polinom) const
{
	if (!this->monoms->getFirst().checkDegrees(polinom.monoms->getFirst()))
		throw std::logic_error("Degrees is big.");
	Polinom result;
	Iterator<Monom> main = this->monoms->getIterator();
	while (main.hasNext())
	{
		Polinom temp;
		Monom a(main.next());
		if (a.getCoef() == 0)
			continue;
		Iterator<Monom> second = polinom.monoms->getIterator();
		while (second.hasNext())
		{
			Monom b(second.next());
			if (b.getCoef() != 0)
				temp.monoms->addLast(a * b);
		}
		result += temp;
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
	Iterator<Monom> main = this->monoms->getIterator();
	while (main.hasNext())
		result += main.next().getValue(values);
	return result;
}

std::ostream& operator<<(std::ostream& ostr, const Polinom& polinom)
{
	Iterator<Monom> iter = polinom.monoms->getIterator();
	while (iter.hasNext())
		ostr << iter.next() << '\n';
	return ostr;
}