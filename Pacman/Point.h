// The class is used to give every object (Pac-Man and ghosts) a starting coordinator, and to update its coordinator during gameplay
#pragma once

#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

enum class Directions : int { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, STAY = 4, QUIT = 6, TRASH = -1 };
//template <class T>
//constexpr char valOf(T constant) { return static_cast<char>(constant); } // Writing enum class' variables is within this template function

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
	Point() = default;
	Point(int x, int y) : _x(x), _y(y) {}
	Point(const Point& point) { *this = point; }
	Point(Point&& point) noexcept : _x(point.getX()), _y(point.getY()) {}
	~Point() = default;
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
	void updateCoord(Directions direction);
};