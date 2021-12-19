#pragma once

#include "Ghost.h"

class NoviceGhost : public Ghost
{
public:
	NoviceGhost(int x, int y, int movementFrequency = valOf(ghostConstants::MOVEMENT_FREQUENCY)) : Ghost(x, y, movementFrequency) {}
	~NoviceGhost() override {}; // No actual memory allocation
	void Reset(const Point& coord) override;
};

