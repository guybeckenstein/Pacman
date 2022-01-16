#pragma once

#include "Ghost.h"

class NoviceGhost : public Ghost
{
public:
	NoviceGhost(int x, int y, int movementFrequency = static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY)) : Ghost(x, y, movementFrequency) { }
	// Destructor
	~NoviceGhost() override = default;
	// Setters
	bool setTargetCoord(const Point& coord) override { return false; }
	void Reset(const Point& coord) override;
};

