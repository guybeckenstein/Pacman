#include "PacmanTarget.h"
#include "Entity.h"
#include <queue>

using namespace std;

// Discovers shortest path to Pac-Man
void PacmanTarget::BFS(const Board& board, const Point& oldCoord, Point& newCoord, bool& isNewCoord) const
{
	vector<vector<bool>> visitArr(board.getHeight() + 1, vector<bool>(board.getWidth() + 1, false));
	// Creating vectors and stores integer values for the directions
	const vector<int> possibleDirectionsColumnAdder = getNewIntegerOfDirectionsVector(), possibleDirectionsRowAdder = getNewIntegerOfDirectionsVector();

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
			if (oldCoord == Point(adjacentX, adjacentY))
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
const vector<int> PacmanTarget::getNewIntegerOfDirectionsVector() const
{
	vector<int> newVector;
	newVector.reserve(valOf(entityConstants::NUM_OF_ARROWKEYS)); // Each index resembles an adder for the adjacent coordinator, which means the next direction
	newVector.push_back(0); // Can go UP
	newVector.push_back(-1); // Can go LEFT
	newVector.push_back(0); // Can go DOWN
	newVector.push_back(1); // Can go RIGHT
	newVector.resize(newVector.capacity());

	return newVector;
}

// Validates the current cell
bool PacmanTarget::isNextCellPossible(const vector<vector<bool>> visitArr, const Board& board, int adjacentX, int adjacentY) const
{
	if (adjacentX >= board.getWidth() || adjacentY >= board.getHeight() || adjacentX == 0 || adjacentY == 0 || board.isWall(adjacentX, adjacentY) == true || visitArr[adjacentY][adjacentX] == true)
		return false;
	return true;
}
