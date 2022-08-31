#include "BestGhost.h"

// Movement Methods
// Move function for smart ghosts, using BFS algorithm
bool BestGhost::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed)
{
	Point pointToUpdate = getCoord();
	setCounter(getCounter() + 1);
	if (BFS(board, getCoord(), pointToUpdate) == false)
		makeRegularMovement(tunnels, board, pointToUpdate);
	setCoord(pointToUpdate);

	return true; // Irrelevant
}

void BestGhost::Reset(const Point& coord)
{
	resetMovement();
	_coord = coord;
}