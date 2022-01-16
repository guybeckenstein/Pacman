#pragma once

#include "Board.h"
#include "Ghost.h"

class BestGhost : public Ghost
{
private:
	Point _target;
public:
	BestGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY)) : _target(pacmanCoord), Ghost(x, y, movementFrequency) { }
	// Destructor
	~BestGhost() override = default;
	// Getters
	const Point& getTargetCoord() const { return _target; }
	// Setters
	bool setTargetCoord(const Point& coord) override { _target = coord; return true; }
	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	bool BFS(const Board& board, Point& newCoord) const;
	bool isNextCellPossible(const vector<vector<bool>> value, const Board& board, int adjacentX, int adjacentY) const;
	void Reset(const Point& coord) override;
};