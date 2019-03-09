#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>

using namespace std;

// Stale globalne

#define WLK_MAPY_X 113 // rozmiar okna / 2 - 3
#define WLK_MAPY_Y 62 // rozmiar okna - 4
#define OutH GetStdHandle(STD_OUTPUT_HANDLE)

const int WindowX = 117;
const int WindowY = 66;

// Deklaracje klas

class Player;

// Deklaracje funkcji

int setCursor(short, short);
int setColor(int);
char keyCheck(int mili = 300, string mode = "menu");
//int scoreboard(Window);
int prepareConsole();
int game(int);

// Definicje struktur 

struct Pos
{
	int X;
	int Y;
};

// Definicje klas


class Player
{
public:
	char character;
	string nickname;
	Pos position;
	bool inGame;
	bool inMenu;
	int action;
	vector <string> equipment;
	int money;

	Player();
	//	Player interpretAction(Player);
};