#include "Ghost.h"

const Point& Ghost::makeRegularMovement(const pair<Tunnel, Tunnel>& tunnels, const Board& board, Point& pointToUpdate)
{
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
	return pointToUpdate;
}