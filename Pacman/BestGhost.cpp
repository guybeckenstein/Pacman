#include <queue>
#include "BestGhost.h"

using std::queue;

// Movement Methods
// Move function for smart ghosts, using BFS algorithm
bool BestGhost::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed)
{
	Point pointToUpdate = getCoord();
	if (BFS(board, pointToUpdate) == true)
	{
		if (pointToUpdate.getY() == getCoord().getY() - 1)
			setDirection(Directions::UP); // Can go UP
		else if (pointToUpdate.getX() == getCoord().getX() - 1)
			setDirection(Directions::LEFT); // Can go LEFT
		else if (pointToUpdate.getY() == getCoord().getY() + 1)
			setDirection(Directions::DOWN); // Can go DOWN
		else
			setDirection(Directions::RIGHT); // Can go RIGHT
		setCoord(pointToUpdate);
	}
	else // Using isNewCoord boolean value for "better" gameplay (when running pacman_c.screen, there is at least one ghost who can not reach pacman)
	{
		setCounter(getCounter() + 1);
		Directions tmpDirection;
		map<Directions, bool> newPossibleDirections;
		bool isNewDirections = getPossibleDirections(tunnels, board, newPossibleDirections, getDirection(), pointToUpdate);
		if (isNewDirections == true || getCounter() % static_cast<int>(entityConstants::CHANGE_DIRECTION) == 0)
		{
			if (getCounter() % static_cast<int>(entityConstants::CHANGE_DIRECTION) == 0)
				_nextDirectionsPossible.find(getDirection())->second = false;
			tmpDirection = getDirection();
			getNextDirection(tmpDirection);
			if (tmpDirection != getDirection())
				setCounter(0);
			setDirection(tmpDirection);
		}
		pointToUpdate.updateCoord(getDirection());
		setCoord(pointToUpdate);
	}
	return true; // Irrelevant
}
// Discovers shortest path to Pac-Man
bool BestGhost::BFS(const Board& board, Point& newCoord) const // Only in case there is a direct shorter route to pacman, Function returns a new coordinator
{
	vector<vector<bool>> visitArr(board.getHeight(), vector<bool>(board.getWidth(), false));
	visitArr[getTargetCoord().getY()][getTargetCoord().getX()] = true; // Marks current target's (Pac-Man) coordinator as visited
	queue<Point> coordQueue; // Includes all coordinators from ghost's current location until it reaches its target - Pac-Man
	coordQueue.push(getTargetCoord());
	while (coordQueue.empty() == false)
	{
		int currX = coordQueue.front().getX(), currY = coordQueue.front().getY();
		coordQueue.pop();
		vector<Point> adjacentArr;
		adjacentArr.push_back({ currX , currY - 1 }); // UP adjacent
		adjacentArr.push_back({ currX - 1 , currY }); // LEFT adjacent
		adjacentArr.push_back({ currX , currY + 1 }); // DOWN adjacent
		adjacentArr.push_back({ currX + 1 , currY }); // RIGHT adjacent
		for (int i = 0; i < adjacentArr.size(); i++)
		{
			if (getCoord() == adjacentArr[i])
			{
				newCoord.setX(currX);
				newCoord.setY(currY);
				return true;
			}
			else if (isNextCellPossible(visitArr, board, adjacentArr[i].getX(), adjacentArr[i].getY()) == true)
			{
				coordQueue.push({ adjacentArr[i].getX(), adjacentArr[i].getY() }); // New current coorddinator
				visitArr[adjacentArr[i].getY()][adjacentArr[i].getX()] = true; // Marks current target's (Pac-Man) coordinator as visited
			}
		}
	}
	return false;
}
// Checks the current cell - if it was not visited before, if it is not on the edges of the board, and does not contain walls
bool BestGhost::isNextCellPossible(const vector<vector<bool>> visitArr, const Board& board, int adjacentX, int adjacentY) const
{
	return (0 < adjacentX && adjacentX < board.getWidth() && 0 < adjacentY && adjacentY < board.getHeight() && board.isWall(adjacentX, adjacentY) == false && visitArr[adjacentY][adjacentX] == false);
}
void BestGhost::Reset(const Point& coord)
{
	resetMovement();
	_coord = coord;
}