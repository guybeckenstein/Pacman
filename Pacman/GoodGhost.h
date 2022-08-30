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
<<<<<<< HEAD
	GoodGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = valOf(ghostConstants::MOVEMENT_FREQUENCY)) : PacmanTarget(pacmanCoord), _isBest(true), Ghost(x,y, movementFrequency) { }
	~GoodGhost() override {}; // No actual memory allocation
=======
	GoodGhost(const Point& pacmanCoord, int x, int y, int movementFrequency = static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY)) : _target(pacmanCoord), _isBest(true), Ghost(x,y, movementFrequency) { }
	// Destructor
	~GoodGhost() override = default;
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	// Getters
	bool getIsBest() const { return _isBest; }
	// Setters
<<<<<<< HEAD

=======
	bool setTargetCoord(const Point& coord) override { _target = coord; return getIsBest(); }
	void setIsBest(bool isBest) { _isBest = isBest; }
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	void Reset(const Point& coord) override;
private:
	// Setters
	void setIsBest(bool isBest) { _isBest = isBest; }
};

