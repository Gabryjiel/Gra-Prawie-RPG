#include "classes.h"
#include "map.h"
#include "menu.h"

int main()
{
	if (!prepareConsole()) // Prepares a console
		return -1;

	Window window1(1, 1, WindowX - 2, WindowY - 2);
	//	Window window2(WindowX / 2 - 1, 1, WindowX / 2, WindowY - 2);

	Menu mainMenu(1);

	while (true) {
		window1.drawWindow();
		//		window2.drawWindow();
		mainMenu.show();
		while (true) {
			char keyPressed = keyCheck(); // Check if key pressed

			if (keyPressed) { // If key was pressed then interpret it
				if (keyPressed == 'W' && mainMenu.active > 0) { // Menu Up
					mainMenu.active--;
					mainMenu.show();
				}
				else if (keyPressed == 'S' && (unsigned int)mainMenu.active < mainMenu.options.size() - 1) { // Menu Down
					mainMenu.active++;
					mainMenu.show();
				}
				else if (keyPressed == 13) { // Confirm (Enter)
					if (mainMenu.active == 0) { // Start Game
						game(0);
						break;
					}
					else if (mainMenu.active == 1) { // Load Game

					}
					else if (mainMenu.active == 2) { // Scoreboard
/*						Window scoreboardWindow(5, 5, 10, 11);
						static bool scoreboardActive;
						if (scoreboardActive == 1) {
							window1.drawWindow();
							scoreboardActive = 0;
							continue;
						}
						scoreboard(scoreboardWindow);
						scoreboardActive = 1;
*/
					}
					else if (mainMenu.active == 3) { // Exit
						return 1;
					}
				}
			}
		}
	}
}

int game(int mode)
{
	Window gameWindow(1, 1, WindowX - 2, WindowY - 2);
	//	Window sideWindow(WindowX / 2 - 1, 1, WindowX / 2, WindowY - 2);
	Window inventoryWindow(99, 1, 17, 13);
	Window chestWindow(83, 1, 17, 13);

	Player player;
	Map disboard;

	Menu myInv(11);
	Menu chestInv(12);
	Menu inHand(13);
	string activeInv = "";
	Menu *activeMenu = 0;

	Menu playerInventory;
	Menu chestInventory;

	vector<Menu> menus;
	vector<string> *activeChestItems = 0;
	vector<string> *playerItems = 0;

	Square checkedObject;

	bool checkInventory = true;
	bool updateInventory = true;

	int tick = 250; // Speed of the player

	if (mode == 0) {
		gameWindow.drawWindow();
		//		sideWindow.drawWindow();
		Sleep(500);
		disboard.draw();
	}


	while (true) {

		// If inventory is updated, this reassignes stats (for example: movement speed)
		if (updateInventory) {
			for (unsigned short i = 0; i < sizeof(player.equipment) / sizeof(string); i++) {
				if (player.equipment[i] == "Boots") {
					tick = 100;
				}
				else tick = 250;
			}

			updateInventory = false;
		}

		// Checks everytime after a move
		for (unsigned short i = 0; i < sizeof(player.equipment) / sizeof(string); i++) {
			if (player.equipment[i] == "GPS") {
				setCursor(50, 2);
				setColor(7);
				cout << "X: " << player.position.X;
				setCursor(50, 3);
				cout << "Y: " << player.position.Y;
			}
		}

		// Writes Player's character
		setCursor(player.position.X + gameWindow.x + 1, player.position.Y + gameWindow.y + 1);
		setColor(disboard.map[player.position.X][player.position.Y].color);
		cout << (char)player.character;

		while (true) { // Loop that looks for "key action"
			if (player.inGame) // Speed in game
				player.action = keyCheck(tick, "game");
			if (player.inMenu) // Speed in menus
				player.action = keyCheck(300, "menu");

			if (player.inGame) { // What happens during game
				if (player.action) {
					setCursor(player.position.X + gameWindow.x + 1, player.position.Y + gameWindow.y + 1);
					setColor(disboard.map[player.position.X][player.position.Y].color);
					cout << " ";

					if (player.action == 'W') {
						if (player.character == 30 && disboard.map[player.position.X][player.position.Y - 1].stable == true)
							player.position.Y--;
						else
							player.character = 30;
					}
					else if (player.action == 'S') {
						if (player.character == 31 && disboard.map[player.position.X][player.position.Y + 1].stable == true)
							player.position.Y++;
						else
							player.character = 31;
					}
					else if (player.action == 'A') {
						if (player.character == 17 && disboard.map[player.position.X - 1][player.position.Y].stable == true)
							player.position.X--;
						else
							player.character = 17;
					}
					else if (player.action == 'D') {
						if (player.character == 16 && disboard.map[player.position.X + 1][player.position.Y].stable == true)
							player.position.X++;
						else
							player.character = 16;
					}
					else if (player.action == 'E') {
						player.inGame = 0;
						player.inMenu = 1;
						activeInv = "inventory";
					}
					else if (player.action == 13) {
						checkedObject = disboard.checkSquare(player.character, player.position.X, player.position.Y);

						if (checkedObject.name == "Normal Tree") {

						}
						else if (checkedObject.name == "Snowy Tree") {
							return 0;
						}
						else if (checkedObject.name == "Path") {

						}
						else if (checkedObject.name == "Grass") {

						}
						else if (checkedObject.name == "Snow") {

						}
						else if (checkedObject.name == "Chest") {
							player.inGame = 0;
							player.inMenu = 1;
							activeInv = "inventory";
						}
					}
					break;
				}
			}
			else if (player.inMenu) {
				static int menu;
				static bool firstLoopEntry;
				static string chosenItem;
				static string chosenTitle;
				static int chosenMenu;
				static int item = -1;

				if (!firstLoopEntry) {
					inventoryWindow.drawWindow();

					playerItems = &player.equipment;
					playerInventory.createMenu("  Inventory", player.equipment, inventoryWindow.x + 2, inventoryWindow.y + 4);
					playerInventory.show();
					menus.push_back(playerInventory);

					if (checkedObject.name == "Chest") {
						for (unsigned int i = 0; i < disboard.chests.size() - 1; i++) {
							if (checkedObject.x == disboard.chests[i].x && checkedObject.y == disboard.chests[i].y) {
								activeChestItems = &disboard.chests[i].item;
								chestInventory.createMenu(" Chest", disboard.chests[i].item, chestWindow.x + 2, chestWindow.y + 4);
								break;
							}
						}
						menus.push_back(chestInventory);
						chestWindow.drawWindow();
						chestInventory.show(dftSemiActiveColor);
					}
					menu = 0;
					chosenItem = "";
					chosenMenu = 0;
					activeMenu = &menus[menu];
					activeMenu->active = 0;
					firstLoopEntry = true;
				}


				if (player.action) {

					if (player.action == 'E' || player.action == 'Q') {
						player.inMenu = 0;
						player.inGame = 1;
						disboard.draw();
						activeMenu = 0;
						firstLoopEntry = false;
						checkedObject.name = "";
						playerInventory.options.clear();
						chestInventory.options.clear();
						menus.clear();
						break;
					}
					else if (player.action == 'W' && activeMenu->active > 0) {
						activeMenu->active--;
					}
					else if (player.action == 'S' && (unsigned int)activeMenu->active + 1 < activeMenu->options.size()) {
						activeMenu->active++;
					}
					else if (player.action == 'A' && (unsigned int)menu < (menus.size() - 1)) {
						activeMenu->show(7, item);
						activeMenu = &menus[++menu];
					}
					else if (player.action == 'D' && menu > 0) {
						activeMenu->show(7, item);
						activeMenu = &menus[--menu];
					}
					else if (player.action == 13) {
						if (chosenItem == "") {
							chosenTitle = activeMenu->title;
							chosenItem = activeMenu->options[activeMenu->active];
							chosenMenu = menu;
							item = activeMenu->active;
							activeMenu->show(4, activeMenu->active);
						}
						else if (chosenItem != "") {
							string temp = activeMenu->options[activeMenu->active];
							activeMenu->options[activeMenu->active] = menus[chosenMenu].options[item];
							menus[chosenMenu].options[item] = temp;

							if (chosenTitle == "Inventory") {

							}
							else if (chosenTitle == "Chest") {

							}

							menus[chosenMenu].show(7);

							chosenItem = "";
							chosenTitle = "";
							temp = "";
							chosenMenu = 0;
							activeMenu->show(4);
							item = -1;
							updateInventory = true;
						}
					}
					if (activeMenu->title == chosenTitle)
						activeMenu->show(dftActiveColor, item);
					else
						activeMenu->show(dftActiveColor);
				}

			}

			/*			else if (player.inMenu) { // Podczas podgladu inventory i np. skrzyn
							if (checkedObject.name == "Chest") { // Dolaczenie danych z ewentualnej skrzyni
								if (temp == 0) {
									for (int i = 0; i < disboard.chests.size(); i++) {
										if (disboard.chests[i].x == checkedObject.x && disboard.chests[i].y == checkedObject.y)
											temp = &disboard.chests[i];
									}

									for (int i = 0; i < 5; i++) {
										if (temp->item[i] == "")
											chestInv.options.push_back(_FREE_OPT);
										else
											chestInv.options.push_back(temp->item[i]);
									}
								}
							}

							if (activeInv == "inventory") {
								activeMenu = &myInv;
								myInv.show();
								if (checkedObject.name == "Chest")
									chestInv.show(dftColor);
							}
							else if (activeInv == "chest") {
								activeMenu = &chestInv;
								myInv.show(dftColor);
								chestInv.show();
							}

							if (checkedObject.name != "Chest") { // Przesuniecie menu "Currently holding"
								inHand.x = WindowX / 2 + 23;
							}
							else {
								inHand.x = WindowX / 2 + 44;
							}

							inHand.show(dftSelectionColor);

							if (player.action != ' ') {
								if ((player.action == 'Q' || (player.action == 'E' && checkedObject.name != "Chest")) && inHand.options[0] == _FREE_OPT)
								{
									player.inMenu = 0;
									player.inGame = 1;
									temp = 0;
									checkedObject.name = "";
									activeInv = "";
									activeMenu = 0;
									checkInventory = true;
									chestInv.options.clear();
									sideWindow.drawWindow();
									break;
								}
								else if (player.action == 'W' && activeMenu->active > 0) {
									activeMenu->active--;
								}
								else if (player.action == 'S' && activeMenu->active < activeMenu->options.size() - 1) {
									activeMenu->active++;
								}
								else if (player.action == 'R') {
									disboard.draw();
									break;
								}
								else if (player.action == 'D' && activeInv == "inventory" && checkedObject.name == "Chest") {
									if (myInv.active > 4) {
										chestInv.active = 4;
									}
									else {
										chestInv.active = myInv.active;
									}
									activeInv = "chest";
								}
								else if (player.action == 'A' && activeInv == "chest") {
									myInv.active = chestInv.active;
									activeInv = "inventory";
								}
								else if (player.action == 13 && inHand.options[0] == _FREE_OPT) {
									inHand.options[0] = activeMenu->options[activeMenu->active];
									activeMenu->options[activeMenu->active] = _FREE_OPT;
									if (activeMenu->title == "Chest Inventory") {
										temp->item[activeMenu->active] = _FREE_OPT;
									}
								}
								else if (player.action == 13 && inHand.options[0] != _FREE_OPT) {
									if (activeMenu->options[activeMenu->active] == _FREE_OPT) {
										activeMenu->options[activeMenu->active] = inHand.options[0];
										if (activeMenu->title == "Chest Inventory") {
											temp->item[activeMenu->active] = inHand.options[0];
										}
										inHand.options[0] = _FREE_OPT;
									}
									else {
										string temps = "";
										temps = inHand.options[0];
										inHand.options[0] = activeMenu->options[activeMenu->active];
										activeMenu->options[activeMenu->active] = temps;
										if (activeMenu->title == "Chest Inventory") {
											temp->item[activeMenu->active] = temps;
										}
									}
								}
							}
						} */
		}
	}
	return 1;
}