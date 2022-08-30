#pragma once

#include "Board.h"
#include "Ghost.h"
#include "PacmanTarget.h"

enum class GoodGhostConstants : int { SMART_COUNTER = 20, NOVICE_COUNTER = 5};

class GoodGhost : virtual public Ghost, virtual public PacmanTarget
{
private:
	bool _isBest;
public:
	GoodGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = valOf(ghostConstants::MOVEMENT_FREQUENCY)) : PacmanTarget(pacmanCoord), _isBest(true), Ghost(x,y, movementFrequency) { }
	~GoodGhost() override {}; // No actual memory allocation
	// Getters
	bool getIsBest() const { return _isBest; }
	// Setters

	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	void Reset(const Point& coord) override;
private:
	// Setters
	void setIsBest(bool isBest) { _isBest = isBest; }
};

