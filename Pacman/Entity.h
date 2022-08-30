// The class inherits the common coordinator feature to "Pacman", "Ghost" and "Fruit" classes
#pragma once

#include <map>
#include "Board.h"

enum class entityConstants : int { NUM_OF_ARROWKEYS = 4 , CHANGE_DIRECTION = 20 };

using Tunnel = vector<pair<Point, Point>>;
using std::map;

class Entity
{
protected:
	// Movement and position
	Point _coord;
	int _movementFrequency;
	int _counter;
	bool _firstMove;
	// Directions and next directions
	Directions _direction;
	mutable map<Directions, bool> _nextDirectionsPossible;
	mutable map<Directions, bool>::iterator _directionsIterator; // Iterator for _currDirections
public:
	Entity(int movementFrequency = 1, int x = static_cast<int>(Directions::TRASH), int y = static_cast<int>(Directions::TRASH)) : _coord({ x, y }), _movementFrequency(movementFrequency), _direction(Directions::TRASH), _counter(0), _firstMove(false)
	{
		srand(static_cast<unsigned int>(std::time(NULL)));

		_nextDirectionsPossible.insert(pair<Directions, bool>(Directions::UP, false)); // Way 1 for inserting pairs
		_nextDirectionsPossible.insert(pair<Directions, bool>(Directions::LEFT, false)); // Way 1 for inserting pairs
		_nextDirectionsPossible.emplace(Directions::DOWN, false); // Way 2 for inserting pairs
		_nextDirectionsPossible.emplace(Directions::RIGHT, false); // Way 2 for inserting pairs
	}
	virtual ~Entity() = default;
	// Getters
	const Point& getCoord() const { return _coord; }
<<<<<<< HEAD
	virtual int getMovementFrequency() const { return _movementFrequency; }
	virtual bool getFirstMove() const { return _firstMove; }
	// Setters
	virtual void setDirection(int direction) { _direction = direction; }
=======
	int getMovementFrequency() const { return _movementFrequency; }
	int getCounter() const { return _counter; }
	Directions getDirection() const { return _direction; }
	bool getFirstMove() const { return _firstMove; }
	// Setters
	void setCoord(const Point& coord) { _coord = coord; }
	void setMovementFrequency(int movementFrequency) { _movementFrequency = movementFrequency; }
	void setCounter(int counter) { _counter = counter; }
	void setDirection(Directions direction) { _direction = direction; }
	void setFirstMove(bool value) { _firstMove = value; }
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	// Operators
	friend std::ostream& operator<<(std::ostream& os, const Entity& creature);
	// Print Methods
<<<<<<< HEAD
	virtual void eraseRender(bool colorAllowed, bool isBreadcrumbCoord, const Point& coord) const;
	virtual void Print(bool colorAllowed, int figureColor) const;
	// Movement Methods
	virtual bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed); // Function must return bool to deal with cases of a player that quits game
=======
	void eraseRender(bool colorAllowed, bool isBreadcrumbCoord, const Point& coord) const;
	void Print(bool colorAllowed, int figureColor) const;
	virtual void Render(std::ostream& os) const = 0;
	// Movement Methods
	virtual bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed); // Function must return bool to deal with cases of a player that quits game
	bool getPossibleDirections(const pair<Tunnel, Tunnel>& tunnels, const Board& board, map<Directions, bool>& newPossibleDirections, Directions currDirection, const Point& coord) const;
	void checkForWalls(const Board& board, map<Directions, bool>& newPossibleDirections, const Point& coord) const;
	void getNextDirection(Directions& newDirection) const;
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	// Reset / Reinitialize Methods
	virtual void Reset(const Point& coord) {}
protected:
	// Getters
	virtual int getCounter() const { return _counter; }
	virtual int getDirection() const { return _direction; }
	// Setters
	virtual void setCoord(const Point& coord) { _coord = coord; }
	virtual void setCounter(int counter) { _counter = counter; }
	virtual void setFirstMove(bool value) { _firstMove = value; }
	// Print Methods
	virtual void Render(std::ostream& os) const = 0;
	// Movement Methods
	virtual bool getPossibleDirections(const pair<Tunnel, Tunnel>& tunnels, const Board& board, vector<bool>& currPossibleDirections, vector<bool>& newPossibleDirections, int currDirection, const Point& coord) const;
	virtual void getNextDirection(const vector<bool>& possibleDirections, int& newDirection) const;
	// Reset / Reinitialize Methods
	virtual void resetMovement();
<<<<<<< HEAD
private:
	// Movement Methods
	void checkForWalls(const Board& board, vector<bool>& possibleDirections, const Point& coord) const;
	int pickDirection(const vector<bool>& possibleDirections) const;
};

=======
};
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
