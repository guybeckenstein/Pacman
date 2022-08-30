#pragma once

#include "Board.h"
#include "Ghost.h"
#include "PacmanTarget.h"

class BestGhost : virtual public Ghost, virtual public PacmanTarget
{
private:
public:
	BestGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = valOf(ghostConstants::MOVEMENT_FREQUENCY)) : PacmanTarget(pacmanCoord), Ghost(x,y, movementFrequency) {}
	~BestGhost() override {}; // No actual memory allocation
	// Getters

	// Setters

	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	void Reset(const Point& coord) override;
};