#pragma once
#include <map>
#include <iostream>
#include <conio.h>
#include <string>

typedef void (*MenuItemFunc)();

template<class T>
T Input(std::string str = "")
{
	T res;
	if (str.size()) std::cout << str << " ";
	std::cin >> res;
	std::cin.ignore(1);
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "ошибка ввода, повторите попытку." << std::endl;
		if (str.size()) std::cout << str << " ";
		std::cin >> res;
	}
	return res;
}

const char* GetString(const char *str = 0);

// описывает пункт меню
class MenuItem
{
	char *name;				// название пункта меню
	MenuItemFunc itemFunc;	// ссылка на обработчик пункта меню
public:
	MenuItem(const MenuItem &mi)
	{
		this->name=_strdup(mi.name);
		this->itemFunc=mi.itemFunc;
	}
	MenuItem(const char *name="UNNAMED",MenuItemFunc func=0)
	{
		this->name=_strdup(name);
		this->itemFunc=func;
	}
	friend std::ostream& operator<<(std::ostream &o, MenuItem& menuitem)
	{
		return o<<menuitem.name;
	}
	~MenuItem()
	{
		delete[] name;
	}
	void Execute()
	{
		if(itemFunc) itemFunc();
	}
};

// для вывода линий символов в поток
class Line
{
	static const int _lineLength = 80;
	char _symbol;
public:

	Line(char symbol = '_')
	{
		this->_symbol = symbol;
	}

	friend std::ostream& operator<<(std::ostream &os, Line &l)
	{
		for (int i = 0;i < _lineLength;++i)
			os << l._symbol;
		return os << std::endl;
	}
};

// класс меню
class ConsoleMenu
{
	std::map<int, MenuItem> items;
	std::string _menuName;
	bool Execute()
	{
		unsigned int code = Input<int>("Command code");
		if (code == 0) {
			items[code].Execute();
			return false;
		}
		if (code >= items.size() || code < 0) {
			std::cout << "Invalid command code" << std::endl;
			_getch();
			return true;
		}
		//system("cls");
		//topWriter();
		//cout<<"Команда "<<items[code]<<":"<<endl;
		items[code].Execute();
		return true;
	}
	static void ReturnFunc()	// функция - заглушка для выхода из меню
	{
		return;
	}
public:
	MenuItemFunc topWriter;		// функция вывода верхушки меню
	ConsoleMenu(MenuItemFunc topWriter = 0, std::string menuname = "")
	{
		this->topWriter = topWriter;
		this->_menuName = _menuName;
		Add("Exit", ReturnFunc);
	}
	void Add(const char *name, const MenuItemFunc menuItem)
	{
		MenuItem newitem(name, menuItem);
		items.insert(std::make_pair((int)items.size(), newitem));
	}
	void Show()	// показать меню
	{
		if (_menuName.size() > 0) {
			std::cout << '\t' << _menuName << std::endl;
			std::cout << Line();
		}
		if (topWriter) topWriter();
		for each(auto i in items)
			std::cout << i.first << '\t' << i.second << std::endl;
	}
	~ConsoleMenu()	// обработчик меню
	{
		do
		{
			system("cls");
			Show();
		} while (Execute());
	}
};