#include<iomanip>
#include "Board.h"
#include "Menu.h"
#include "Pacman.h"

// Setters

// Creating a board from the screen loaded
void Board::initializeBoard(const vector<string>& table, const Point& pacmanCoord, const Point& legendCoord)
{
	setTable(table);
	setHeight(table.size());
	setWidth(table[0].size());
	setLegend(legendCoord);
	for (int y = 0; y < getHeight(); y++)
	{
		if (_table[y] == "")
			for (int x = 0; x < getWidth(); x++)
				_table[y].push_back(' ');
		else if (y == legendCoord.getY() || y == legendCoord.getY() + 1 || y == legendCoord.getY() + 2)
			for (int x = legendCoord.getX(); x < legendCoord.getX() + static_cast<int>(boardConstants::LEGEND_MAX_WIDTH); x++)
				if (isWall(x, y) == true)
					_table[y][x] = static_cast<char>(boardConstants::BLANK);
	}
	_totalBreadcrumbs = 0;
	addBreadcrumbs(pacmanCoord);
}
// Used when starting a screen. Adds breadcrumbs to all coordinators which are not '#', '%', or in the legend area
void Board::addBreadcrumbs(const Point& pacmanCoord)
{
	vector<vector<Point>> legendArea(static_cast<int>(boardConstants::LEGEND_MAX_HEIGHT));
	int x, y;
	for (y = 0; y < legendArea.size(); y++)
	{
		legendArea[y].reserve(static_cast<int>(boardConstants::LEGEND_MAX_WIDTH));
		for (x = 0; x < _width && x < legendArea[y].capacity(); x++)
			legendArea[y].push_back({ getLegend().getX() + x, getLegend().getY() + y });
		legendArea[y].resize(legendArea[y].size());
	}
	for (y = 0; y < getHeight(); y++)
	{
		for (x = 0; x < getWidth(); x++)
			if (isWall(x, y) == false)
				if (Point(x, y) == pacmanCoord || isInLegendArea(x, y, legendArea) == true)
					continue;
				else if (_table[y][x] == static_cast<char>(boardConstants::BLANK))
				{
					addBreadcrumb(x, y);
					_totalBreadcrumbs++;
				}
	}
}
// Breadcrumbs can not be created in the legend area
bool Board::isInLegendArea(int pointX, int pointY, const vector<vector<Point>>& legendArea) const
{
	size_t x, y, size = legendArea[0].size();
	for (y = 0; y < legendArea.size(); y++)
		for (x = 0; x < size; x++)
			if (Point(pointX, pointY) == legendArea[y][x])
				return true;
	return false;
}
// Methods
// Printing current board table, including breadcrumbs
void Board::Print(bool colorAllowed, const string& screenName) const
{
	Menu::gotoxy(0, 0);
	for (auto y = 0; y < getHeight(); y++)
	{
		for (auto x = 0; x < getWidth(); x++)
		{
			if (colorAllowed == true) // Bonus
			{
				if (isBreadcrumb(x, y) == true)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::BROWN));
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::LIGHTBLUE));
				if (isEmpty(x, y) || _table[y][x] == static_cast<char>(boardConstants::LEGEND))
					std::cout << static_cast<char>(boardConstants::BLANK);
				else
					std::cout << _table[y][x];
			}
			else
				if (isEmpty(x, y) || _table[y][x] == static_cast<char>(boardConstants::LEGEND))
					std::cout << static_cast<char>(boardConstants::BLANK);
				else
					std::cout << _table[y][x];
		}
		std::cout << std::endl;
	}
	if (colorAllowed == true) // Bonus
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::WHITE));
	std::cout << std::endl << std::setw(getWidth()) << screenName;
}