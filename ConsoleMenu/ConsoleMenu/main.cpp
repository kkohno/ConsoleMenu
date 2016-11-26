#include "ConsoleMenu.h"

void TopWriter1()
{
	std::cout << "This is a top" << std::endl;
	std::cout << Line();
}

void Function1()
{
	std::cout << "Function 1" << std::endl;
	system("pause");
}
void Function2()
{
	system("cls");
	std::cout << "Function 2" << std::endl;
	system("pause");
}

void SubMenu1()
{
	ConsoleMenu menu("Sub Menu1");
	menu.Add("Function 2", Function2);
	menu.Add("Function 1", Function1);
}

void MenuMain()
{
	ConsoleMenu menu(TopWriter1, "Main Menu");
	menu.Add("Function 1", Function1);
	menu.Add("Function 2", Function2);
	menu.Add("SubMenu 1", SubMenu1);
}

void main()
{
	MenuMain();
}