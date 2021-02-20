#include "roman.h"

romanSymbol Number::takeRomanSymbol(const char& symb)
{
	romanSymbol symbol;
	symbol.symbol = symb;
	switch (symb)
	{
	case 'I':
		symbol.base = 1;
		symbol.tens = 1;
		break;
	case 'V':
		symbol.base = 5;
		symbol.tens = 1;
		break;
	case 'X':
		symbol.base = 1;
		symbol.tens = 10;
		break;
	case 'L':
		symbol.base = 5;
		symbol.tens = 10;
		break;
	case 'C':
		symbol.base = 1;
		symbol.tens = 100;
		break;
	case 'D':
		symbol.base = 5;
		symbol.tens = 100;
		break;
	case 'M':
		symbol.base = 1;
		symbol.tens = 1000;
		break;
	default:
		throw std::logic_error("Invalid symbol.");
		break;
	}
	return symbol;
}

romanSymbol Number::takeRomanSymbol(const int& num)
{
	romanSymbol symbol;
	switch (num)
	{
	case 1:
		symbol.symbol = 'I';
		symbol.base = 1;
		symbol.tens = 1;
		break;
	case 5:
		symbol.symbol = 'V';
		symbol.base = 5;
		symbol.tens = 1;
		break;
	case 10:
		symbol.symbol = 'X';
		symbol.base = 1;
		symbol.tens = 10;
		break;
	case 50:
		symbol.symbol = 'L';
		symbol.base = 5;
		symbol.tens = 10;
		break;
	case 100:
		symbol.symbol = 'C';
		symbol.base = 1;
		symbol.tens = 100;
		break;
	case 500:
		symbol.symbol = 'D';
		symbol.base = 5;
		symbol.tens = 100;
		break;
	case 1000:
		symbol.symbol = 'M';
		symbol.base = 1;
		symbol.tens = 1000;
		break;
	default:
		throw std::logic_error("Invalid number");
		break;
	}
	return symbol;
}

void Number::romanToArabic()
{
	std::string input = romanNumber.value;
	int output = 0;
	int currentTens = INT16_MAX;
	for (char symb : input)
	{
		romanSymbol symbol = takeRomanSymbol(symb);
		if (currentTens < symbol.tens || (currentTens == symbol.tens && symbol.base == 5))
		{
			output += symbol.base * symbol.tens;
			output -= 2 * currentTens;
			currentTens = INT16_MAX;
		}
		else
		{
			output += symbol.base * symbol.tens;
			currentTens = symbol.tens;
		}
	}
	arabicNumber.value = output;
}

void Number::arabicToRoman()
{
	int input = arabicNumber.value;
	std::string output = "";
	int currentTens = 1;
	while (input != 0)
	{
		char temp = input % 10;
		input = input / 10;
		switch (temp)
		{
		case 4:
			output.insert(output.begin(), takeRomanSymbol(5 * currentTens).symbol);
			output.insert(output.begin(), takeRomanSymbol(currentTens).symbol);
			break;
		case 9:
		{
			int tempRank = currentTens;
			/*while (input % 10 == 9)
			{
				input = input / 10;
				currentTens *= 10;
			}
			if (input % 10 == 4)
			{
				input = input / 10;
				currentTens *= 10;
				output.insert(output.begin(), takeRomanSymbol(5 * currentTens).symbol);
			}
			else*/
				output.insert(output.begin(), takeRomanSymbol(10 * currentTens).symbol);
			output.insert(output.begin(), takeRomanSymbol(tempRank).symbol);
			break;
		}
		default:
			bool big = false;
			if (temp >= 5)
			{
				big = true;
				temp -= 5;
			}
			while (temp != 0)
			{
				output.insert(output.begin(), takeRomanSymbol(currentTens).symbol);
				temp--;
			}
			if (big)
				output.insert(output.begin(), takeRomanSymbol(5 * currentTens).symbol);
			break;
		}
		currentTens *= 10;
	}
	romanNumber.value = output;
}

void Number::fixRoman()
{
	std::string input = romanNumber.value;
	std::string output = "";
	romanSymbol prev;
	int row = 0;
	for (char symb : input)
	{
		romanSymbol symbol = takeRomanSymbol(symb);
		if (symbol.symbol == prev.symbol)
		{
			row++;
		}
		else
		{
			output.append(Number(row * (prev.base * prev.tens)).getRoman().value);
			prev = symbol;
			row = 1;
		}
	}
	output.append(Number(row * (prev.base * prev.tens)).getRoman().value);
	romanNumber.value = output;
}

Number::Number()
{
	romanNumber.value = "";
	arabicNumber.value = 0;
}

Number::Number(const roman& number)
{
	romanNumber.value = number.value;
	this->fixRoman();
	this->romanToArabic();
}

Number::Number(const arabic& number)
{
	arabicNumber.value = number.value;
	this->arabicToRoman();
}

roman Number::getRoman()
{
	return romanNumber;
}

arabic Number::getArabic()
{
	return arabicNumber;
}