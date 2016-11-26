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
	if (str.length()) std::cout << str << " ";
	std::cin >> res;
	std::cin.ignore(1);
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "Input error! Try again." << std::endl;
		if (str.length()) std::cout << str << " ";
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
	char _symbol;
	static unsigned _stdSymbolsInLine;	// количество символов в строке по умолчанию
public:

	Line(char symbol = '_')
	{
		this->_symbol = symbol;
	}

	friend std::ostream& operator<<(std::ostream &os, Line &l)
	{
		for (unsigned i = 0;i < _stdSymbolsInLine;++i)
			os << l._symbol;
		return os << std::endl;
	}

	static void SetStdSymbolsInLine(unsigned stdSymbolsInLine)	// задает число символов в одной строке по умолчанию
	{
		Line::_stdSymbolsInLine = stdSymbolsInLine;
	}
};

// класс меню
class ConsoleMenu
{
	std::map<int, MenuItem> _items;
	std::string _menuName;

	static void ReturnFunc()	// функция - заглушка для выхода из меню
	{
		return;
	}

	bool Execute()
	{
		unsigned int code = Input<int>("Command code");
		if (code == 0) {
			_items[code].Execute();
			return false;
		}
		if (code >= _items.size() || code < 0) {
			std::cout << "Invalid command code" << std::endl;
			_getch();
			return true;
		}
		//system("cls");
		//topWriter();
		//cout<<"Команда "<<items[code]<<":"<<endl;
		_items[code].Execute();
		return true;
	}
	void Show()	// показать меню
	{
		if (_menuName.length() > 0) {
			std::cout << '\t' << _menuName << std::endl;
			std::cout << Line();
		}
		if (_topWriter) _topWriter();
		for each(auto i in _items)
			std::cout << i.first << '\t' << i.second << std::endl;
	}
public:
	MenuItemFunc _topWriter;		// функция вывода верхушки меню
	
	~ConsoleMenu()	// обработчик меню
	{
		do
		{
			system("cls");
			Show();
		} while (Execute());
	}

	ConsoleMenu(MenuItemFunc topWriter, std::string menuname)
	{
		this->_topWriter = topWriter;
		this->_menuName = menuname;
		Add("Exit", ReturnFunc);
	}
	ConsoleMenu(MenuItemFunc topWriter)
	{
		this->_topWriter = topWriter;
		Add("Exit", ReturnFunc);
	}
	ConsoleMenu(std::string menuname)
	{
		this->_menuName = menuname;
		Add("Exit", ReturnFunc);
	}
	void Add(const char *name, const MenuItemFunc menuItem)
	{
		MenuItem newitem(name, menuItem);
		_items.insert(std::make_pair((int)_items.size(), newitem));
	}
};