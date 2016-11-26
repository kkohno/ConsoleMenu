#include "ConsoleMenu.h"

void TopWriter1()
{
	std::cout << "ololo" << std::endl;
	std::cout << Line();
}

void Function1()
{
	std::cout << "ololo" << std::endl;
	system("pause");
}

void MenuMain()
{
	ConsoleMenu menu(TopWriter1);
	menu.Add("Function 1", Function1);
}

void main()
{
	MenuMain();
}