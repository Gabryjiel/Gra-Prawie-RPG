#pragma once
#include "map.h"

Map::Map() {
	fileInterpreter();
	placeChests();
}

void Map::placeChests() {
	Chest allChest[] = {
		{7 ,6 ,1,{"Boots     ", ".         ", ".         "}},
		{20,20,2,{"GPS       ", ".         ", ".         ", ".         "}}
	};

	for (int i = 0; i < sizeof(allChest) / sizeof(Chest); i++) {
		Map::chests.push_back(allChest[i]);
		Map::map[allChest[i].x][allChest[i].y].color = 96;
		Map::map[allChest[i].x][allChest[i].y].name = "Chest";
		Map::map[allChest[i].x][allChest[i].y].sign = '+';
		Map::map[allChest[i].x][allChest[i].y].stable = false;
	}
}

void Map::fileInterpreter() {
	std::fstream file;
	file.open("mapBETA.txt");

	for (int y = 0; y < MAPA_Y; y++) {
		for (int x = 0; x < MAPA_X; x++) {
			std::string field;

			file >> field;

			if (field == "TN") {
				Map::map[x][y].color = 42;
				Map::map[x][y].name = "Normal Tree";
				Map::map[x][y].sign = '^';
				Map::map[x][y].stable = false;
			}
			else if (field == "TS") {
				Map::map[x][y].color = 250;
				Map::map[x][y].name = "Snowy Tree";
				Map::map[x][y].sign = '^';
				Map::map[x][y].stable = false;
			}
			else if (field == "PA") {
				Map::map[x][y].color = 123;
				Map::map[x][y].name = "Path";
				Map::map[x][y].sign = ' ';
				Map::map[x][y].stable = true;
			}
			else if (field == "1") {
				Map::map[x][y].color = 43;
				Map::map[x][y].name = "Grass";
				Map::map[x][y].sign = ' ';
				Map::map[x][y].stable = true;
			}
			else if (field == "2") {
				Map::map[x][y].color = 251;
				Map::map[x][y].name = "Snow";
				Map::map[x][y].sign = ' ';
				Map::map[x][y].stable = true;
			}

			Map::map[x][y].x = x;
			Map::map[x][y].y = y;

			if (file.eof()) file.close();
		}
	}
}

void Map::draw() {
	for (int y = 0; y < MAPA_Y; y++) {
		for (int x = 0; x < MAPA_X; x++) {
			setColor(Map::map[x][y].color);
			setCursor(x + punktx1, y + punkty1);
			std::cout << Map::map[x][y].sign;
		}
	}
}

Square Map::checkSquare(char character, int xpos, int ypos) {
	int x = xpos;
	int y = ypos;

	if (character == 30) //Do gory
		y--;
	else if (character == 31) //Do dolu
		y++;
	else if (character == 17) //W lewo
		x--;
	else if (character == 16) //W prawo
		x++;

	return Map::map[x][y];
}

bool Map::createMap() {

	for (int y = 0; y < MAPA_Y; y++) {
		for (int x = 0; x < MAPA_X; x++) {
			Map::map[x][y].x = x;
			Map::map[x][y].y = y;
			Map::map[x][y].color = 43;
			Map::map[x][y].stable = true;
			Map::map[x][y].sign = ' ';
			Map::map[x][y].name = "Grass";
		}
	}

	return true;
}