#include <string>
#include "roman.h"

int main() 
{
	char romanSymbols[] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
	std::string text;
	std::getline(std::cin, text);
	std::string output = "";
	std::string temp = "";
	bool space = true;
	for (char c : text)
	{
		if (space)
		{
			bool isRoman = false;
			if (c == ' ')
			{
				output.append(std::to_string(Number(temp).getArabic().value));
				output.insert(output.end(), c);
				temp = "";
			}
			else
			{
				for (char rs : romanSymbols)
					if (rs == c)
					{
						isRoman = true;
						break;
					}
				if (isRoman)
				{
					temp.insert(temp.end(), c);
				}
				else
				{
					space = false;
					output.append(temp);
					output.insert(output.end(), c);
					temp = "";
				}
			}
		}
		else
		{
			if (c == ' ')
				space = true;
			else
				space = false;
			output.insert(output.end(), c);
		}
	}
	if (temp.length() > 0)
		output.append(std::to_string(Number(temp).getArabic().value));
	std::cout << output;
	return 0;
}