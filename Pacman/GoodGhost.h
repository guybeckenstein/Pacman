#pragma once

#include "Board.h"
#include "Ghost.h"

enum class GoodGhostConstants : int { SMART_COUNTER = 20, NOVICE_COUNTER = 5};

class GoodGhost : public Ghost
{
private:
	Point _target;
	bool _isBest;
public:
	GoodGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY)) : _target(pacmanCoord), _isBest(true), Ghost(x,y, movementFrequency) { }
	// Destructor
	~GoodGhost() override = default;
	// Getters
	const Point& getTargetCoord() const { return _target; }
	bool getIsBest() const { return _isBest; }
	// Setters
	bool setTargetCoord(const Point& coord) override { _target = coord; return getIsBest(); }
	void setIsBest(bool isBest) { _isBest = isBest; }
	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	void BFS(const Board& board, Point& newCoord, bool& isNewCoord) const;
	bool isNextCellPossible(const vector<vector<bool>> value, const Board& board, int adjacentX, int adjacentY) const;
	void Reset(const Point& coord) override;
};

