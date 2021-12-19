#include "Fruit.h"
#include "Ghost.h"
#include "Pacman.h"

// Methods
void Fruit::setStartingCoord(const Board& board, const vector<Point>& entities) // Fruit gets a starting random coordinator as requested
{
	int i;
	bool valid = true;
	_coord.setY(rand() % board.getHeight());
	_coord.setX(rand() % board.getWidth());
	for (i = 0; i < entities.size(); i++)
	{
		if (_coord == entities[i])
			valid = false;
	}
	while ((board.isWall(_coord.getX(), _coord.getY()) == true) || valid == false)
	{
		valid = true;
		_coord.setY(rand() % board.getHeight());
		_coord.setX(rand() % board.getWidth());
		for (i = 0; i < entities.size(); i++)
		{
			if (_coord == entities[i])
				valid = false;
		}
	}
}
void Fruit::makeFruitInvisibile()
{
	setVisibility(false);
	_number = 0;
	setCoord({ 0, 0 });
}
void Fruit::Reset(const Board& board, const vector<Point>& entities) // Values are irrelevant
{
	resetMovement();
	setStartingCoord(board, entities);
	setNumber();
	setVisibility(true);
}