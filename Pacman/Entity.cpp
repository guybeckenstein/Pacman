#include "Entity.h"
#include "ConsoleApp.h"
#include "Game.h"

// Operators
std::ostream& operator<<(std::ostream& os, const Entity& creature)
{
	creature.Render(os);
	return os;
}
// Print Methods
void Entity::eraseRender(bool colorAllowed, bool isBreadcrumbCoord, const Point& coord) const // Prints the original figure of the current coordinator - which is a breadcrumb or just a vacuum
{
	ConsoleApp::gotoxy(coord.getX(), coord.getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::BROWN));
	if (isBreadcrumbCoord == true)
		std::cout << static_cast<char>(boardConstants::BREADCRUMB) << std::endl;
	else
		std::cout << static_cast<char>(boardConstants::BLANK) << std::endl;
}
void Entity::Print(bool colorAllowed, int figureColor) const // Prints the entity's render - in it's new coordinator
{
	ConsoleApp::gotoxy(getCoord().getX(), getCoord().getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), figureColor);
	std::cout << *this << std::endl;
}
// Movement Methods
bool Entity::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed)
{
	setCounter(getCounter() + 1);
	if (getFirstMove() == false)
	{
		setFirstMove(true);
		setDirection(Directions::TRASH);
	}
	Directions tmpDirection;
	map<Directions, bool> newPossibleDirections;
	Point pointToUpdate = getCoord();
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

	return true; // Irrelevant
}
bool Entity::getPossibleDirections(const pair<Tunnel, Tunnel>& tunnels, const Board& board, map<Directions, bool>& newPossibleDirections, Directions currDirection, const Point& coord) const
{
	bool res = false;

	newPossibleDirections.insert(pair<Directions, bool>(Directions::UP, true)); // Way 1 for inserting pairs
	newPossibleDirections.insert(pair<Directions, bool>(Directions::LEFT, true)); // Way 1 for inserting pairs
	newPossibleDirections.emplace(Directions::DOWN, true); // Way 2 for inserting pairs
	newPossibleDirections.emplace(Directions::RIGHT, true); // Way 2 for inserting pairs

	if (currDirection == Directions::DOWN || coord.getY() == 0)
	{
		_directionsIterator = newPossibleDirections.find(Directions::UP);
		_directionsIterator->second = false; // Can not go UP
	}
	if (currDirection == Directions::RIGHT || coord.getX() == 0)
	{
		_directionsIterator = newPossibleDirections.find(Directions::LEFT);
		_directionsIterator->second = false; // Can not go LEFT
	}
	if (currDirection == Directions::UP || coord.getY() == board.getHeight() - 1)
	{
		_directionsIterator = newPossibleDirections.find(Directions::DOWN);
		_directionsIterator->second = false; // Can not go DOWN
	}
	if (currDirection == Directions::LEFT || coord.getX() == board.getWidth() - 1)
	{
		_directionsIterator = newPossibleDirections.find(Directions::RIGHT);
		_directionsIterator->second = false; // Can not go RIGHT
	}
	checkForWalls(board, newPossibleDirections, coord);
	int i = 0;
	for (auto currNextItr = _nextDirectionsPossible.find(Directions::UP), nextNextItr = newPossibleDirections.find(Directions::UP); res == false && i < static_cast<int>(entityConstants::NUM_OF_ARROWKEYS); i++)
	{
		if (currNextItr->second != nextNextItr->second)
		{
			res = true;
			i = 0;
			for (currNextItr = _nextDirectionsPossible.find(Directions::UP), nextNextItr = newPossibleDirections.find(Directions::UP); i < static_cast<int>(entityConstants::NUM_OF_ARROWKEYS); i++)
			{
				currNextItr->second = nextNextItr->second;
				++currNextItr;
				++nextNextItr;
			}
		}
		else
		{
			++currNextItr;
			++nextNextItr;
		}
	}
	return res;
}
void Entity::checkForWalls(const Board& board, map<Directions, bool>& newPossibleDirections, const Point& coord) const
{
	int x = coord.getX(), y = coord.getY();
	auto itr = newPossibleDirections.find(Directions::UP);
	if (itr->second == true && board.isWall(x, y - 1) == true)
		itr->second = false; // Can not go UP
	if ((++itr)->second == true && board.isWall(x - 1, y) == true)
		itr->second = false; // Can not go LEFT
	if ((++itr)->second == true && board.isWall(x, y + 1) == true)
		itr->second = false; // Can not go DOWN
	if ((++itr)->second == true && board.isWall(x + 1, y) == true)
		itr->second = false; // Can not go RIGHT
}
void Entity::getNextDirection(Directions& newDirection) const
{
	auto itr = _nextDirectionsPossible.find(Directions::UP);
	if (itr->second != false || (++itr)->second != false || (++itr)->second != false || (++itr)->second != false)
	{
		Directions oldDirection = newDirection;
		int randomValue = rand() % static_cast<int>(entityConstants::NUM_OF_ARROWKEYS);
		if (randomValue == 0)
			newDirection = Directions::UP;
		else if (randomValue == 1)
			newDirection = Directions::LEFT;
		else if (randomValue == 2)
			newDirection = Directions::DOWN;
		else
			newDirection = Directions::RIGHT;
		while ((itr = _nextDirectionsPossible.find(newDirection))->second == false)
		{
			newDirection = oldDirection;
			randomValue = rand() % static_cast<int>(entityConstants::NUM_OF_ARROWKEYS);
			if (randomValue == 0)
				newDirection = Directions::UP;
			else if (randomValue == 1)
				newDirection = Directions::LEFT;
			else if (randomValue == 2)
				newDirection = Directions::DOWN;
			else
				newDirection = Directions::RIGHT;
		}
	}
	else
		newDirection = Directions::TRASH;
}
// Reset / Reinitialize Methods
void Entity::resetMovement()
{
	for (auto begin = _nextDirectionsPossible.begin(), end = _nextDirectionsPossible.end(); begin != end; ++begin)
		begin->second = false;
	setDirection(Directions::TRASH);
	setFirstMove(false);
}