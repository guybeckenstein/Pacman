#include "GoodGhost.h"

// Movement Methods
// Move function for smart ghosts, using BFS algorithm
bool GoodGhost::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed)
{
	Point pointToUpdate = getCoord();
	setCounter(getCounter() + 1);
	if (getIsBest() == false || BFS(board, getCoord(), pointToUpdate) == false)
		makeRegularMovement(tunnels, board, pointToUpdate);
	setCoord(pointToUpdate);
	if (getCounter() % valOf(GoodGhostConstants::NOVICE_COUNTER) == 0)
	{
		setIsBest(true);
		setCounter(0);
	}

	return true; // Irrelevant
}

void GoodGhost::Reset(const Point& coord)
{
	resetMovement();
	setIsBest(true);
	_coord = coord;
}