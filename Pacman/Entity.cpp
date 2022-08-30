#include "Entity.h"
#include "ConsoleApp.h"
#include "Game.h"

// Methods
void Entity::eraseRender(bool colorAllowed, bool isBreadcrumbCoord, const Point& coord) const // Prints the original figure of the current coordinator - which is a breadcrumb or just a vacuum
{
	ConsoleApp::gotoxy(coord.getX(), coord.getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::BROWN));
	if (isBreadcrumbCoord == true)
		std::cout << valOf(boardConstants::BREADCRUMB) << std::endl;
	else
		std::cout << valOf(boardConstants::BLANK) << std::endl;
}
void Entity::Print(bool colorAllowed, int figureColor) const // Prints the entity's render - in it's new coordinator
{
	ConsoleApp::gotoxy(getCoord().getX(), getCoord().getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), figureColor);
	std::cout << *this << std::endl;
}
bool Entity::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed)
{
	setCounter(getCounter() + 1);
	if (getFirstMove() == false)
	{
		setFirstMove(true);
		setDirection(valOf(pointConstants::TRASH));
	}
	int tmpDirection;
	vector<bool> newPossibleDirections;
	newPossibleDirections.resize(valOf(entityConstants::NUM_OF_ARROWKEYS));
	Point pointToUpdate = getCoord();
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

	return true; // Irrelevant
}
bool Entity::getPossibleDirections(const pair<Tunnel, Tunnel>& tunnels, const Board& board, vector<bool>& currPossibleDirections, vector<bool>& newPossibleDirections, int currDirection, const Point& coord) const
{
	bool res = false;
	newPossibleDirections[valOf(pointConstants::UP)] = newPossibleDirections[valOf(pointConstants::LEFT)] = newPossibleDirections[valOf(pointConstants::DOWN)] = newPossibleDirections[valOf(pointConstants::RIGHT)] = true;
	if (currDirection == valOf(pointConstants::DOWN) || coord.getY() == 0)
		newPossibleDirections[valOf(pointConstants::UP)] = false; // Can not go UP
	if (currDirection == valOf(pointConstants::RIGHT) || coord.getX() == 0)
		newPossibleDirections[valOf(pointConstants::LEFT)] = false; // Can not go LEFT
	if (currDirection == valOf(pointConstants::UP) || coord.getY() == board.getHeight() - 1)
		newPossibleDirections[valOf(pointConstants::DOWN)] = false; // Can not go DOWN
	if (currDirection == valOf(pointConstants::LEFT) || coord.getX() == board.getWidth() - 1)
		newPossibleDirections[valOf(pointConstants::RIGHT)] = false; // Can not go RIGHT
	checkForWalls(board, newPossibleDirections, coord);
	for (int i = 0; res == false && i < valOf(entityConstants::NUM_OF_ARROWKEYS); i++)
		if (currPossibleDirections[i] != newPossibleDirections[i])
		{
			res = true;
			for (i = 0; i < valOf(entityConstants::NUM_OF_ARROWKEYS); i++)
				currPossibleDirections[i] = newPossibleDirections[i];
		}
	return res;
}
void Entity::checkForWalls(const Board& board, vector<bool>& possibleDirections, const Point& coord) const
{
	int x = coord.getX(), y = coord.getY();
	if (possibleDirections[valOf(pointConstants::UP)] == true && board.isWall(x, y - 1) == true)
		possibleDirections[valOf(pointConstants::UP)] = false; // Can not go UP
	if (possibleDirections[valOf(pointConstants::LEFT)] == true && board.isWall(x - 1, y) == true)
		possibleDirections[valOf(pointConstants::LEFT)] = false; // Can not go LEFT
	if (possibleDirections[valOf(pointConstants::DOWN)] == true && board.isWall(x, y + 1) == true)
		possibleDirections[valOf(pointConstants::DOWN)] = false; // Can not go DOWN
	if (possibleDirections[valOf(pointConstants::RIGHT)] == true && board.isWall(x + 1, y) == true)
		possibleDirections[valOf(pointConstants::RIGHT)] = false; // Can not go RIGHT
}
void Entity::getNextDirection(const vector<bool>& possibleDirections, int& newDirection) const
{
	if (possibleDirections[valOf(pointConstants::UP)] != false || possibleDirections[valOf(pointConstants::LEFT)] != false || possibleDirections[valOf(pointConstants::DOWN)] != false || possibleDirections[valOf(pointConstants::RIGHT)] != false)
	{
		int oldDirection = newDirection;
		newDirection = rand() % valOf(entityConstants::NUM_OF_ARROWKEYS);
		while (possibleDirections[newDirection] == false)
		{
			newDirection = oldDirection;
			newDirection = rand() % valOf(entityConstants::NUM_OF_ARROWKEYS);
		}
	}
	else
		newDirection = -1;
}
int Entity::pickDirection(const vector<bool>& possibleDirections) const // Chooses the next step of a ghost/fruit randomly, depends of the walls are next to it
{
	int res = 0, direction;
	while (res == 0)
	{
		direction = rand() % valOf(entityConstants::NUM_OF_ARROWKEYS);
		if (possibleDirections[direction] == true)
			res = 1;
	}
	return direction + 1;
}
void Entity::resetMovement()
{
	for (size_t i = 0; i < _possibleDirections.size(); i++)
		_possibleDirections[i] = (false);
	setDirection(valOf(pointConstants::TRASH));
	setFirstMove(false);
}