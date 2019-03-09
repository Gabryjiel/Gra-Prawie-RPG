#include "classes.h"

int prepareConsole()
{
	SetConsoleTitle("Gra Prawie RPG");
	HANDLE outHnl = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInf;
	GetCurrentConsoleFontEx(outHnl, TRUE, &fontInf);
	fontInf.cbSize = sizeof(fontInf);
	fontInf.nFont = 0;
	fontInf.FontFamily = FF_DONTCARE;
	fontInf.FontWeight = FW_NORMAL;
	fontInf.dwFontSize.X = 8;
	fontInf.dwFontSize.Y = 8;
	wcscpy_s(fontInf.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(outHnl, TRUE, &fontInf);

	COORD sizeB = { WindowX,WindowY };
	SetConsoleScreenBufferSize(outHnl, sizeB);

	SMALL_RECT sizeW = { 0, 0, WindowX - 1, WindowY - 1 };
	SetConsoleWindowInfo(outHnl, true, &sizeW);

	CONSOLE_CURSOR_INFO cursorInfo = { 100,false };
	SetConsoleCursorInfo(outHnl, &cursorInfo);

	return 1;
}

int setColor(int color)
{
	SetConsoleTextAttribute(OutH, color);
	return 1;
}

int setCursor(short x, short y)
{
	COORD point = { x,y };
	SetConsoleCursorPosition(OutH, point);
	return 1;
}

char keyCheck(int mili, string mode)
{
	using namespace std::chrono;
	char controls[] = { 'W','S','A','D','E','Q','R',13 };
	char keyToCheck = 0;
	static char lockedKey;
	static steady_clock::time_point start;
	steady_clock::time_point end;
	int tick = mili;
	bool iWantToMove = false;

	for (short i = 0; i < sizeof(controls) / sizeof(char); i++) {
		if (GetAsyncKeyState(controls[i])) {
			if (keyToCheck != 0) return 0;
			keyToCheck = controls[i];
		}
	}

	end = steady_clock::now();

	if (keyToCheck == 'W' || keyToCheck == 'S' || keyToCheck == 'A' || keyToCheck == 'D')
		iWantToMove = true;

	if (duration_cast<milliseconds>(end - start).count() > tick && iWantToMove) lockedKey = 0;

	if (keyToCheck != lockedKey) {
		start = steady_clock::now();
		lockedKey = keyToCheck;
		return keyToCheck;
	}
	else return 0;
}
/*
int scoreboard(Window wind)
{
	vector <int> score;
	vector <int> day;
	vector <int> month;
	vector <int> year;
	vector <string> nickname;

	fstream file;
	file.open("Scoreboard.txt");

	int i, maxchar = 0;
	for (i = 0; file.is_open(); i++)
	{
		int t_score = 0, t_day = 0, t_month = 0, t_year = 0;
		string t_nick;

		if (file.eof())
		{
			file.close();
			break;
		}
		file >> t_nick >> t_score >> t_day >> t_month >> t_year;

		nickname.push_back(t_nick);
		score.push_back(t_score);
		day.push_back(t_day);
		month.push_back(t_month);
		year.push_back(t_year);

		if (maxchar < t_nick.length())
			maxchar = (int)t_nick.length();
	}

	for (int l = 0; l < i - 1; l++)
	{
		for (int n = 0; n < i - 1; n++)
		{
			if (score[n] < score[n + 1])
			{
				iter_swap(score.begin() + n, score.begin() + (n + 1));
				iter_swap(nickname.begin() + n, nickname.begin() + (n + 1));
				iter_swap(day.begin() + n, day.begin() + (n + 1));
				iter_swap(month.begin() + n, month.begin() + (n + 1));
				iter_swap(year.begin() + n, year.begin() + (n + 1));
			}
		}
	}

#define LICZBAPOZYCJI 25
	if (i > LICZBAPOZYCJI)
		i = LICZBAPOZYCJI;
#undef LICZBAPOZYCJI

	setCursor(wind.x + 2, wind.y + 3);
	cout << "SCOREBOARD";

	for (int t = 0; t < i - 1; t++)
	{
		setCursor(wind.x + 2, wind.y + 6 + t);
		cout << t + 1 << ". " << nickname[t];

		for (int c = 0; c < maxchar - nickname[t].length(); c++)
		{
			cout << " ";
		}

		cout << " - " << score[t] << " on ";

		if (day[t] < 10)
			cout << "0";
		cout << day[t] << ".";

		if (month[t] < 10)
			cout << "0";
		cout << month[t] << "." << year[t];
	}

	return 1;
}
*/
// Funkcje klasy Window



//Funkcje klasy Player

Player::Player()
{
	Player::position = { 2,4 };
	Player::inGame = 1;
	Player::character = 17;
	Player::action = ' ';
	Player::inMenu = 0;
	for (int i = 0; i < 7; i++) Player::equipment.push_back(".         ");
}