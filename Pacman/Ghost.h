// The class is used to define the ghost object in the game
#pragma once

#include "Entity.h"

enum class ghostConstants : int { FIGURE = '$', MOVEMENT_FREQUENCY = 2, MAX_GHOSTS = 4 };

class Ghost : public Entity
{
public:
	Ghost(int x, int y, int movementFrequency = static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY)) : Entity(movementFrequency, x, y) { }
	// Destructor
	virtual ~Ghost() { } // No actual memory allocation
	// Setters
	virtual bool setTargetCoord(const Point& coord) = 0;
	// Methods
	void Render(std::ostream& os) const override { os << static_cast<char>(ghostConstants::FIGURE); }
	virtual void Reset(const Point& coord) = 0;
};