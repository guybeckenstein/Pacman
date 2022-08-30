#include "BestGhost.h"

// Movement Methods
// Move function for smart ghosts, using BFS algorithm
bool BestGhost::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed)
{
	bool isNewCoord = false;
	Point pointToUpdate = getCoord();
	BFS(board, getCoord(), pointToUpdate, isNewCoord);
	if (isNewCoord == true)
	{
		if (pointToUpdate.getY() == getCoord().getY() - 1)
			setDirection(valOf(pointConstants::UP)); // Can go UP
		else if (pointToUpdate.getX() == getCoord().getX() - 1)
			setDirection(valOf(pointConstants::LEFT)); // Can go LEFT
		else if (pointToUpdate.getY() == getCoord().getY() + 1)
			setDirection(valOf(pointConstants::DOWN)); // Can go DOWN
		else
			setDirection(valOf(pointConstants::RIGHT)); // Can go RIGHT
		setCoord(pointToUpdate);
	}
	else // Using isNewCoord boolean value for "better" gameplay (when running pacman_c.screen, there is at least one ghost who can not reach pacman)
	{
		setCounter(getCounter() + 1);
		int tmpDirection;
		vector<bool> newPossibleDirections;
		newPossibleDirections.resize(valOf(entityConstants::NUM_OF_ARROWKEYS));
		bool isNewDirections = getPossibleDirections(tunnels, board, _possibleDirections, newPossibleDirections, getDirection(), pointToUpdate);
		if (isNewDirections == true || getCounter() % valOf(entityConstants::CHANGE_DIRECTION) == 0)
		{
			if (getCounter() % valOf(entityConstants::CHANGE_DIRECTION) == 0)
				_possibleDirections[getDirection()] = false;
			tmpDirection = getDirection();
			getNextDirection(_possibleDirections, tmpDirection);
			if (tmpDirection != getDirection())
				setCounter(0);
			setDirection(tmpDirection);
		}
		pointToUpdate.updateCoord(getDirection());
		setCoord(pointToUpdate);
	}

	return true; // Irrelevant
}

void BestGhost::Reset(const Point& coord)
{
	resetMovement();
	_coord = coord;
}