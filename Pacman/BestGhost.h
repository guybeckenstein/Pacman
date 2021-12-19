#pragma once

#include <queue>
#include "Board.h"
#include "Ghost.h"

class BestGhost : public Ghost // TO DO - implement BestGhost
{
private:
	Point _target;
public:
	BestGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = valOf(ghostConstants::MOVEMENT_FREQUENCY)) : _target(pacmanCoord), Ghost(x,y, movementFrequency) {}
	~BestGhost() override {}; // No actual memory allocation
	// Getters
	const Point& getTargetCoord() const { return _target; }
	// Setters
	void setTargetCoord(const Point& coord) { _target = coord; }
	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	void BFS(const Board& board, Point& newCoord, bool& isNewCoord) const;
	bool isNextCellPossible(const vector<vector<bool>> value, const Board& board, int adjacentX, int adjacentY) const;
	void Reset(const Point& coord) override;
};