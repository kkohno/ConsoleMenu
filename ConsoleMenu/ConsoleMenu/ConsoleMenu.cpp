#include "ConsoleMenu.h"

unsigned Line::_stdSymbolsInLine = 80;

std::string GetString(std::string str = "")
{
	std::string res;
	if (str.length()) std::cout << str << " ";
	std::getline(std::cin, res);
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "Input error! Try again." << std::endl;
		if (str.length()) std::cout << str << " ";
		std::getline(std::cin, res);
	}
	return res;
}