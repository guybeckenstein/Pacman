// The class inherits the common coordinator feature to "Pacman", "Ghost" and "Fruit" classes
#pragma once

#include "Board.h"
#include "Point.h"

enum class entityConstants : int { NUM_OF_ARROWKEYS = 4 , CHANGE_DIRECTION = 20 };
typedef vector <pair<Point, Point>> Tunnel;

using std::time;

class Entity
{
protected:
	Point _coord;
	int _movementFrequency;
	int _counter;
	int _direction;
	vector<bool> _possibleDirections;
	bool _firstMove;
public:
	Entity(int movementFrequency = 1, int x = valOf(pointConstants::TRASH), int y = valOf(pointConstants::TRASH)) : _coord({ x, y }), _movementFrequency(movementFrequency), _direction(valOf(pointConstants::TRASH)), _counter(0), _firstMove(false)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		_possibleDirections.resize(static_cast<int>(valOf(entityConstants::NUM_OF_ARROWKEYS)));
	}
	virtual ~Entity() {} // No actual memory allocation
	// Getters
	const Point& getCoord() const { return _coord; }
	virtual int getMovementFrequency() const { return _movementFrequency; }
	int getCounter() const { return _counter; }
	virtual int getDirection() const { return _direction; }
	virtual bool getFirstMove() const { return _firstMove; }
	// Setters
	virtual void setCoord(const Point& coord) { _coord = coord; }
	virtual void setMovementFrequency(int movementFrequency) { _movementFrequency = movementFrequency; }
	void setCounter(int counter) { _counter = counter; }
	virtual void setDirection(int direction) { _direction = direction; }
	virtual void setFirstMove(bool value) { _firstMove = value; }
	// Operators
	friend std::ostream& operator<<(std::ostream& os, const Entity& creature)
	{
		creature.Render(os);
		return os;
	}
	// Print Methods
	virtual void eraseRender(bool colorAllowed, bool isBreadcrumbCoord, const Point& coord) const;
	virtual void Print(bool colorAllowed, int figureColor) const;
	virtual void Render(std::ostream& os) const = 0;
	// Movement Methods
	virtual bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed); // Function must return bool to deal with cases of a player that quits game
	bool getPossibleDirections(const pair<Tunnel, Tunnel>& tunnels, const Board& board, vector<bool>& currPossibleDirections, vector<bool>& newPossibleDirections, int currDirection, const Point& coord) const;
	void checkForWalls(const Board& board, vector<bool>& possibleDirections, const Point& coord) const;
	void getNextDirection(const vector<bool>& possibleDirections, int& newDirection) const;
	virtual int pickDirection(const vector<bool>& possibleDirections) const;
	// Reset / Reinitialize Methods
	virtual void Reset(const Point& coord) = 0;
	virtual void resetMovement();
};

