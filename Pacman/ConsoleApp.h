#pragma once

#include <stdlib.h>
#include "Point.h"

class ConsoleApp
{
private:
	ConsoleApp() = delete;
	ConsoleApp(ConsoleApp&) = delete;
	const ConsoleApp& operator=(const ConsoleApp& consoleApp) = delete;
public:
	// system Methods
	static void clearScreen() { system("cls"); }
	static void pauseScreen() { system("pause"); }
	// Console Application Screen Methods
	static void clearLegendArea(const Point& legend);
	static void gotoxy(int x, int y);
	static void pauseGame(const Point& legend, bool colorAllowed);
};

