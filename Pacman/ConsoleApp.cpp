#include "ConsoleApp.h"
#include <iostream>
#include <windows.h>
#include "Board.h"
#include "Game.h"

void ConsoleApp::clearLegendArea(const Point& legend)
{
	ConsoleApp::gotoxy(legend.getX(), legend.getY());
	for (auto i = 0; i < valOf(boardConstants::LEGEND_MAX_HEIGHT); i++)
	{
		for (auto j = 0; j < valOf(boardConstants::LEGEND_MAX_WIDTH); j++)
			std::cout << " ";
		std::cout << std::endl;
	}
}
void ConsoleApp::gotoxy(int x, int y)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// Hides cursor
	CONSOLE_CURSOR_INFO info = { 100, false };
	SetConsoleCursorInfo(hConsoleOutput, &info);
	COORD dwCursorPosition = { static_cast<short>(x), static_cast<short>(y) };
	// Sets cursor position
	std::cout << std::flush;
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
void ConsoleApp::pauseGame(const Point& legend, bool colorAllowed) // Player pressed "ESC" button -> game paused. If player will press "ESC" again, game will continue
{
	gotoxy(legend.getX(), legend.getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::WHITE));
	std::cout << "Game paused, press" << std::endl
		<< "ESC again to continue" << std::endl;
	char key = 0;
	while (key != valOf(gameConstants::ESC))
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == valOf(gameConstants::ESC))
			{
				clearLegendArea(legend);
				continue;
			}
		}
	}
}