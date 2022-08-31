// The class is used to define the ghost object in the game
#pragma once

#include "Entity.h"

enum class ghostConstants : int { FIGURE = '$', MOVEMENT_FREQUENCY = 2, MAX_GHOSTS = 4 };

class Ghost : public Entity
{
private:
public:
	Ghost(int x, int y, int movementFrequency = valOf(ghostConstants::MOVEMENT_FREQUENCY)) : Entity(movementFrequency, x, y) { }
	// Destructor
	virtual ~Ghost() {} // No actual memory allocation
	// Methods
	void Render(std::ostream& os) const override { os << valOf(ghostConstants::FIGURE); }
	void Reset(const Point& coord) = 0;
protected:
	// Movement Methods
	const Point& makeRegularMovement(const pair<Tunnel, Tunnel>& tunnels, const Board& board, Point& pointToUpdate);
};