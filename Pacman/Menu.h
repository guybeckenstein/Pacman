// This class is for printing main menu and other outputs
#pragma once

#include <iostream>
#include <string>
#include <vector>

enum class colorConstants : int { BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, BROWN = 6, LIGHTGREY = 7, DARKGREY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11, LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15 };

using std::string;
using std::vector;

class Menu
{
private:
	vector<string> _screenNames;
	bool _colorAllowed;
public:
	Menu(const vector<string>& screenNames) : _screenNames(screenNames), _colorAllowed(false) {}
	Menu(const Menu& menu) { *this = menu; }
	~Menu() { _screenNames.clear(); }
	// Used Functions
	void Run();
	int mainMenu();
	void Load();
	int getDifficultyLevel();
	void loadScreenByName(int difficultyLevel);
	void loadScreensAutomatically(int screenIndex, int difficultyLevel); // starts from screenIndex
	void Results(int properScreens, int screenIndex, bool isWin, bool isQuit, int score = 0);
	bool isNameExist(const string& name, int& index);
	void Instructions();
	static void pauseGame(const Point& legend, bool colorAllowed);
	static void clearLegendArea(const Point& legend);
	// Getters
	const vector<string>& getScreenNames() const { return _screenNames; }
	// Operators
	const Menu& operator=(const Menu& menu);
	// We are expected to use these Methods
	static void clearScreen() { system("cls"); }
	static void pauseScreen() { system("pause"); }
	static void gotoxy(int x, int y);
	// Bonus Methods
	bool getColorSettings() { return _colorAllowed; }
	void setColorSettings(bool value) { _colorAllowed = value; }
	bool colorScreen(bool isColorAllowed);
};

