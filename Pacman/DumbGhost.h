#pragma once

#include "Ghost.h"

class DumbGhost : public Ghost
{
private:

public:
	DumbGhost() {}
	~DumbGhost() override {}; // No actual memory allocation
};

