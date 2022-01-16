#include <queue>
#include "GoodGhost.h"

using std::queue;

// Movement Methods
// Move function for smart ghosts, using BFS algorithm
bool GoodGhost::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed)
{
	bool isNewCoord = false;
	Point pointToUpdate = getCoord();
	setCounter(getCounter() + 1);
	if (getIsBest() == true)
	{
		if (getCounter() % static_cast<int>(GoodGhostConstants::SMART_COUNTER) == 0)
		{
			setIsBest(false);
			setCounter(0);
		}
		BFS(board, pointToUpdate, isNewCoord);
		if (isNewCoord == true)
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
	}
	if (getIsBest() == false || isNewCoord == false) // Using isNewCoord boolean value for "better" gameplay (when running pacman_c.screen, there is at least one ghost who can not reach pacman)
	{
		if (getCounter() % static_cast<int>(GoodGhostConstants::NOVICE_COUNTER) == 0)
		{
			setIsBest(true);
			setCounter(0);
		}
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

void GoodGhost::BFS(const Board& board, Point& newCoord, bool& isNewCoord) const // Only in case there is a direct shorter route to pacman, Function returns a new coordinator
{
	vector<vector<bool>> visitArr(board.getHeight(), vector<bool>(board.getWidth(), false));
	visitArr[getTargetCoord().getY()][getTargetCoord().getX()] = true; // Marks current target's (Pac-Man) coordinator as visited
	queue<Point> coordQueue; // Includes all coordinators from ghost's current location until it reaches its target - Pac-Man
	coordQueue.push(getTargetCoord());
	while (coordQueue.empty() == false && isNewCoord == false)
	{
		int currX = coordQueue.front().getX(), currY = coordQueue.front().getY();
		coordQueue.pop();
		vector<Point> adjacentArr;
		adjacentArr.push_back({ currX , currY - 1 }); // UP adjacent
		adjacentArr.push_back({ currX - 1 , currY }); // LEFT adjacent
		adjacentArr.push_back({ currX , currY + 1 }); // DOWN adjacent
		adjacentArr.push_back({ currX + 1 , currY }); // RIGHT adjacent
		for (int i = 0; i < adjacentArr.size() && isNewCoord == false; i++)
		{
			if (getCoord() == adjacentArr[i])
			{
				newCoord.setX(currX);
				newCoord.setY(currY);
				isNewCoord = true;
			}
			else if (isNextCellPossible(visitArr, board, adjacentArr[i].getX(), adjacentArr[i].getY()) == true)
			{
				coordQueue.push({ adjacentArr[i].getX(), adjacentArr[i].getY() }); // New current coorddinator
				visitArr[adjacentArr[i].getY()][adjacentArr[i].getX()] = true; // Marks current target's (Pac-Man) coordinator as visited
			}
		}
	}
}
// Validates the current cell
bool GoodGhost::isNextCellPossible(const vector<vector<bool>> visitArr, const Board& board, int adjacentX, int adjacentY) const
{
	if (adjacentX >= board.getWidth() || adjacentY >= board.getHeight() || adjacentX == 0 || adjacentY == 0 || board.isWall(adjacentX, adjacentY) == true || visitArr[adjacentY][adjacentX] == true)
		return false;
	return true;
}

void GoodGhost::Reset(const Point& coord)
{
	resetMovement();
	setIsBest(true);
	_coord = coord;
}