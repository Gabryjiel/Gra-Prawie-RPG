#pragma once
#pragma once

#include <string>
#include <vector>
#include "classes.h"

#define _WINDOW_X 232
#define _WINDOW_Y 66
#define _FREE_OPT ".           "
#define dftColor 8
#define dftSemiActiveColor 7
#define dftActiveColor 14
#define impColor 2
#define dftSelectionColor 12

class Window
{
public:
	short x;
	short y;
	int length;
	int height;
	char ** previousLayer;

	Window(int, int, int, int);
	int drawWindow();
};


class Menu
{
public:
	std::string title;
	std::vector <std::string> options;
	short active;

	short x;
	short y;
	int length;
	int height;

	Menu(int);
	Menu();
	void createMenu(std::string, std::vector<std::string>, int, int);
	int move();
	int show(int color = dftActiveColor, int selection = -1);
	//	int show(int);
	int clear();
};