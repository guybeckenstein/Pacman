#pragma once

#include "Ghost.h"
#include <Queue>

enum class averageGhostConstants : int { SMART_MOVES_COUNTER = 20, RANDOM_DIRECTION_COUNTER = 5};

class AverageGhost : public Ghost
{
private:

public:
	AverageGhost() {}
	~AverageGhost() override {}; // No actual memory allocation
};

