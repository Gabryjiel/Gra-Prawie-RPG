#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iostream>
#include "classes.h"

#define MAPA_X 113
#define MAPA_Y 62
#define punktx1 2
#define punkty1 2

struct Square {
	int x;
	int y;
	std::string name;
	int color;
	char sign;
	bool stable;
};

struct Chest {
	int x;
	int y;
	int id;
	std::vector<std::string> item;
};

class Map {
public:
	Square map[MAPA_X][MAPA_Y];

	std::vector<Chest> chests;

	Map();
	void fileInterpreter();
	void placeChests();
	void draw();
	Square checkSquare(char, int, int);
	bool createMap();
};