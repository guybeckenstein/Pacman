#pragma once

#include "Board.h"
#include "Point.h"

class PacmanTarget
{
private:
	Point _pacmanTarget;
public:
	PacmanTarget(const Point& pacmanCoord) : _pacmanTarget(pacmanCoord) { }
	// Setters
	void setTargetCoord(const Point& coord) { _pacmanTarget = coord; }
	// Movement Methods
	void BFS(const Board& board, const Point& oldCoord, Point& newCoord, bool& isNewCoord) const;
private:
	// Getters
	const Point& getTargetCoord() const { return _pacmanTarget; }
	// Movement Methods
	const vector<int> getNewIntegerOfDirectionsVector() const;
	bool isNextCellPossible(const vector<vector<bool>> visitArr, const Board& board, int adjacentX, int adjacentY) const;
};
