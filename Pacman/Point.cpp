#include "Point.h"

// Operators
const Point& Point::operator=(const Point& coord)
{
	if (this != &coord)
	{
		setX(coord.getX());
		setY(coord.getY());
	}
	return *this;
}
const Point& Point::operator+(const Point& coord)
{
	setX(getX() + coord.getX());
	setY(getY() + coord.getY());
	return *this;
}
// Methods
void Point::updateCoord(int direction) // Updates the coordinator of the object (pacman and ghosts), changing it by one.
{
	if (direction == (unsigned int)pointConstants::UP) // UP
		setY(_y - 1);
	else if (direction == (unsigned int)pointConstants::LEFT)
		setX(_x - 1);
	else if (direction == (unsigned int)pointConstants::DOWN)
		setY(_y + 1);
	else if (direction == (unsigned int)pointConstants::RIGHT)
		setX(_x + 1);
}