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
		if (getCounter() % valOf(GoodGhostConstants::SMART_COUNTER) == 0)
		{
			setIsBest(false);
			setCounter(0);
		}
		BFS(board, pointToUpdate, isNewCoord);
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
	}
	if (getIsBest() == false || isNewCoord == false) // Using isNewCoord boolean value for "better" gameplay (when running pacman_c.screen, there is at least one ghost who can not reach pacman)
	{
		if (getCounter() % valOf(GoodGhostConstants::NOVICE_COUNTER) == 0)
		{
			setIsBest(true);
			setCounter(0);
		}
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

void GoodGhost::BFS(const Board& board, Point& newCoord, bool& isNewCoord) const // Only in case there is a direct shorter route to pacman, Function returns a new coordinator
{
	vector<vector<bool>> visitArr(board.getHeight() + 1, vector<bool>(board.getWidth() + 1, false));
	// Creating vector and stores values
	vector<int> possibleDirectionsColumnAdder, possibleDirectionsRowAdder;
	possibleDirectionsColumnAdder.reserve(valOf(entityConstants::NUM_OF_ARROWKEYS)); // Each index resembles an adder for the adjacent coordinator, which means the next direction
	possibleDirectionsColumnAdder.push_back(0); // Can go UP
	possibleDirectionsColumnAdder.push_back(-1); // Can go LEFT
	possibleDirectionsColumnAdder.push_back(0); // Can go DOWN
	possibleDirectionsColumnAdder.push_back(1); // Can go RIGHT
	possibleDirectionsColumnAdder.resize(possibleDirectionsColumnAdder.capacity());
	possibleDirectionsRowAdder.reserve(valOf(entityConstants::NUM_OF_ARROWKEYS)); // Each index resembles an adder for the adjacent coordinator, which means the next direction
	possibleDirectionsRowAdder.push_back(-1); // Can go UP
	possibleDirectionsRowAdder.push_back(0); // Can go LEFT
	possibleDirectionsRowAdder.push_back(1); // Can go DOWN
	possibleDirectionsRowAdder.push_back(0); // Can go RIGHT
	possibleDirectionsRowAdder.resize(possibleDirectionsRowAdder.capacity());

	visitArr[getTargetCoord().getY()][getTargetCoord().getX()] = true; // Marks current target's (Pac-Man) coordinator as visited
	queue<Point> currCoord; // Includes all coordinators from ghost's current location until it reaches its target - Pac-Man
	currCoord.push({ getTargetCoord().getX(), getTargetCoord().getY() });

	while (currCoord.empty() == false && isNewCoord == false)
	{
		int currX = currCoord.front().getX(), currY = currCoord.front().getY();
		currCoord.pop();
		for (int i = 0; i < valOf(entityConstants::NUM_OF_ARROWKEYS) && isNewCoord == false; i++)
		{
			int adjacentX = currX + possibleDirectionsColumnAdder[i], adjacentY = currY + possibleDirectionsRowAdder[i];
			if (getCoord() == Point(adjacentX, adjacentY))
			{
				newCoord.setX(currX);
				newCoord.setY(currY);
				isNewCoord = true;
			}
			else if (isNextCellPossible(visitArr, board, adjacentX, adjacentY) == true)
			{
				currCoord.push({ adjacentX, adjacentY }); // New current coorddinator
				visitArr[adjacentY][adjacentX] = true; // Marks current target's (Pac-Man) coordinator as visited
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