#include <iostream>
#ifndef INCLUDE_ROMAN_H_
#define INCLUDE_ROMAN_H_

struct romanSymbol
{
	char symbol;
	int base;
	int tens;
	romanSymbol() : symbol('-'), base(0), tens(-1) {};
};

struct roman
{
	std::string value;
	roman() : value("") {};
	roman(const char* number) : value(number) {};
	roman(const std::string& number) : value(number) {};
};

struct arabic
{
	int value;
	arabic() : value(0) {};
	arabic(const int& number) : value(number) {};
};

class Number
{
private:
	roman romanNumber;
	arabic arabicNumber;

	void romanToArabic();
	void arabicToRoman();
	void fixRoman();

	romanSymbol takeRomanSymbol(const char&);
	romanSymbol takeRomanSymbol(const int&);
public:
	
	Number();
	Number(const roman&);
	Number(const arabic&);

	roman getRoman();
	arabic getArabic();
};
#endif  // INCLUDE_ROMAN_H_