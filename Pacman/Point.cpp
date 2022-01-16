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
void Point::updateCoord(Directions direction) // Updates the coordinator of the object (pacman and ghosts), changing it by one.
{
	if (direction == Directions::UP)
		setY(_y - 1);
	else if (direction == Directions::LEFT)
		setX(_x - 1);
	else if (direction == Directions::DOWN)
		setY(_y + 1);
	else if (direction == Directions::RIGHT)
		setX(_x + 1);
}