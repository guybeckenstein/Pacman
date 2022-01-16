// The class is used to print the table and breadcrumbs of Pac-Man, when initializing and updating the game
// Also being used to avoid game-objects from touching game walls (Pac-Man and ghosts)
#pragma once

#include "Point.h"

enum class boardConstants : char { TABLE_MAX_HEIGHT = 25, TABLE_MAX_WIDTH = 80, BREADCRUMB = '.', BLANK = ' ', WALL = '#', EMPTY = '%', LEGEND = '&', LEGEND_MAX_HEIGHT = 3, LEGEND_MAX_WIDTH = 20 };

class Board
{
private:
	vector<string> _table;
	size_t _height, _width;
	Point _legend;
	int _totalBreadcrumbs;
public:
	// Constructors
	Board(): _height(0), _width(0), _legend(static_cast<int>(Directions::TRASH), static_cast<int>(Directions::TRASH)), _totalBreadcrumbs(0) {}
	void initializeBoard(const vector<string>& table, const Point& pacmanCoord, const Point& legendCoord);
	void addBreadcrumbs(const Point& pacmanCoord);
	bool isInLegendArea(int x, int y, const vector<vector<Point>>& legendArea) const;
	// Getters
	size_t getHeight() const { return _height; }
	size_t getWidth() const { return _width; }
	const Point& getLegend() const { return _legend; }
	int getNumberOfBreadcrumbs() const { return _totalBreadcrumbs; }
	// Setters
	void setTable(const vector<string>& table) { _table = table; }
	void setHeight(size_t height) { _height = height; }
	void setWidth(size_t width) { _width = width; }
	void setLegend(const Point& legend) { _legend = legend; }
	void addBreadcrumb(int x, int y) { _table[y][x] = static_cast<char>(boardConstants::BREADCRUMB); }
	void removeBreadcrumb(int x, int y) { _table[y][x] = static_cast<char>(boardConstants::BLANK); }
	void updateTotalBreadcrumbs() { _totalBreadcrumbs--; }
	// Methods
	void Print(bool colorAllowed, const string& screenName) const;
	bool isWall(int x, int y) const { return (_table[y][x] == static_cast<char>(boardConstants::WALL)); }
	bool isEmpty(int x, int y) const { return (_table[y][x] == static_cast<char>(boardConstants::EMPTY)); }
	bool isBreadcrumb(int x, int y) const { return (_table[y][x] == static_cast<char>(boardConstants::BREADCRUMB)); }
};