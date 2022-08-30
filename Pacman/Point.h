// The class is used to give every object (Pac-Man and ghosts) a starting coordinator, and to update its coordinator during gameplay
#pragma once

#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

enum class pointConstants : int { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, TRASH = -1 };
template <typename T>
constexpr char valOf(T constant) { return static_cast<char>(constant); } // Writing enum class' variables is within this template function

using std::pair;
using std::string;
using std::vector;

class Point
{
private:
	int _x;
	int _y;
public:
	// Constructors
	Point(int x = valOf(pointConstants::TRASH), int y = valOf(pointConstants::TRASH)) : _x(x), _y(y) {}
	Point(const Point& point) { *this = point; }
	// Getters
	int getX() const { return _x; }
	int getY() const { return _y; }
	// Setters
	void setX(const int x) { _x = x; }
	void setY(const int y) { _y = y; }
	// Operators
	const Point& operator=(const Point& coord);
	const Point& operator+(const Point& coord);
	bool operator==(const Point& coord) const { return (getX() == coord.getX() && getY() == coord.getY()); }
	bool operator!=(const Point& coord) const { return (getX() != coord.getX() || getY() != coord.getY()); };
	// Methods
	void updateCoord(int direction);
};