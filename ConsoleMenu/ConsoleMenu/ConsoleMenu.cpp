#include "ConsoleMenu.h"

std::string GetString(std::string str = "")
{
	std::string res;
	if (str.size()) std::cout << str << " ";
	std::getline(std::cin, res);
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "ошибка ввода, повторите попытку." << std::endl;
		if (str.size()) std::cout << str << " ";
		std::getline(std::cin, res);
	}
	return res;
}