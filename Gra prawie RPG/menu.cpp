#pragma once

#include "menu.h"

Window::Window(int x, int y, int l, int h)
{
	Window::x = x;
	Window::y = y;
	Window::length = l;
	Window::height = h;

}

int Window::drawWindow()
{
	for (int i = 0; i < Window::height; i++)
	{
		setCursor(Window::x, Window::y + i);
		for (int n = 0; n < Window::length; n++)
		{
			if (i == 0 || i == Window::height - 1 || n == 0 || n == Window::length - 1)
			{
				setColor(255);
				cout << "#";
			}
			else
			{
				setColor(7);
				cout << " ";
			}
		}
	}
	SetConsoleTextAttribute(OutH, 7);
	setCursor(2, 2);
	return 1;
}

Menu::Menu(int mode)
{
	if (mode == 1)
	{
		title = "";
		options.push_back("Start Game");
		options.push_back("Load  Game");
		options.push_back("Scoreboard");
		options.push_back("   Exit   ");
		x = 52;
		y = _WINDOW_Y / 2 - 3;
		length = 12;
		height = 7;
	}
	else if (mode == 2)
	{
		title = "Inventory";
		options.push_back("Tools");
		options.push_back("Consumables");
		options.push_back("Items");
		x = _WINDOW_X / 2 + 3;
		y = 5;
		length = 20;
		height = 10;
	}
	else if (mode == 11)
	{
		title = "Your Inventory";
		x = 81;
		y = 4;
		for (int i = 0; i < 10; i++) options.push_back(_FREE_OPT);
		length = 20;
		height = 10;
	}
	else if (mode == 12)
	{
		title = "Chest Inventory";
		x = _WINDOW_X / 2 + 23;
		y = 5;
		length = 20;
		height = 10;
	}
	else if (mode == 13)
	{
		title = "Curretly holding";
		options.push_back(_FREE_OPT);
		x = _WINDOW_X / 2 + 44;
		y = 5;
		length = 20;
		height = 2;
	}
	active = 0;
}

Menu::Menu() {

}

void Menu::createMenu(std::string menuTitle, std::vector<std::string> variants, int xpos, int ypos) {
	Menu::title = menuTitle;
	Menu::x = xpos;
	Menu::y = ypos;

	for (unsigned int i = 0; i < variants.size(); i++) {
		options.push_back(variants[i]);
	}

}

int Menu::move()
{
	int key = keyCheck(300, "menu");

	if (key == 'W' && Menu::active > 0)
	{
		Menu::active--;
	}
	else if (key == 'S' && Menu::active < Menu::options.size() - 1)
	{
		Menu::active++;
	}
	else if (key == 13)
	{
		return 13;
	}
	return 1;
}

int Menu::show(int color, int selection)
{
	setCursor(x, y - 2);
	setColor(impColor);
	cout << title;

	for (int i = 0; i < Menu::options.size(); i++)
	{
		setCursor(x, y + i);

		if (i == selection)
			setColor(dftSelectionColor);
		else if (i == Menu::active)
			setColor(color);
		else
			setColor(dftColor);

		cout << options[i];
	}

	setColor(dftColor);
	return 1;
}

int Menu::clear()
{
	for (int i = -2; i < height; i++)
	{
		for (int n = 0; n < length; n++)
		{
			setCursor(x + n, y + i);
			cout << " ";
		}
	}

	return 1;
}
