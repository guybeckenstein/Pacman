#pragma once

#include "Board.h"
#include "Ghost.h"
#include "PacmanTarget.h"

<<<<<<< HEAD
class BestGhost : virtual public Ghost, virtual public PacmanTarget
=======
class BestGhost : public Ghost
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
{
private:
public:
<<<<<<< HEAD
	BestGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = valOf(ghostConstants::MOVEMENT_FREQUENCY)) : PacmanTarget(pacmanCoord), Ghost(x,y, movementFrequency) {}
	~BestGhost() override {}; // No actual memory allocation
=======
	BestGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY)) : _target(pacmanCoord), Ghost(x, y, movementFrequency) { }
	// Destructor
	~BestGhost() override = default;
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	// Getters

	// Setters
<<<<<<< HEAD

	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
=======
	bool setTargetCoord(const Point& coord) override { _target = coord; return true; }
	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	bool BFS(const Board& board, Point& newCoord) const;
	bool isNextCellPossible(const vector<vector<bool>> value, const Board& board, int adjacentX, int adjacentY) const;
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	void Reset(const Point& coord) override;
};