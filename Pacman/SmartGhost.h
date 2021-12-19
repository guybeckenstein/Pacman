#pragma once

#include <Queue>
#include "Board.h"
#include "Ghost.h"

const int SQUARED = 2;
const double SQRT = 0.5;
const int TOTAL_DIRECTIONS = 4;

class SmartGhost : public Ghost
{
private:
	Point _target;
public:
	SmartGhost(const Point& pacmanCoord ) : _target(pacmanCoord) {}
	~SmartGhost() override {}; // No actual memory allocation
	// Getters
	const Point& getTargetCoord() const { return _target; }
	// Setters
	void setTargetCoord(const Point& coord) { _target = coord; }
	// Methods
	double getDistanceFromTarget(int x, int y) { return (pow(pow(x - _target.getX(), SQUARED) + pow(y - _target.getY(), SQUARED), SQRT)); }
	std::queue<int> createRouteGhost(int x, int y, const Board& board, int direction);
};

