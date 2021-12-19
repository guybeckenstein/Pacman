// The class is used to define the fruit object in the game
#pragma once

#include "Entity.h"

enum class fruitConstants : int {MOVEMENT_FREQUENCY = 4, FRUIT_TIMER = 100, TOTAL_DIVISION_OPTIONS = 5};

class Fruit : public Entity
{
private:
	int _number;
	bool _isVisible;
public:
	// Constructors
	Fruit(int movementFrequency = valOf(fruitConstants::MOVEMENT_FREQUENCY)) : Entity(movementFrequency), _number(valOf(pointConstants::TRASH)), _isVisible(false) {}
	// Getters
	int getNumber() const { return _number; }
	bool getVisibility() const { return _isVisible; }
	// Setters
	void setNumber() { _number = (rand() % valOf(fruitConstants::TOTAL_DIVISION_OPTIONS)) + valOf(fruitConstants::TOTAL_DIVISION_OPTIONS); }
	void setVisibility(bool value) { _isVisible = value; }
	// Methods
	void Render(std::ostream& os) const override { os << getNumber(); }
	void setStartingCoord(const Board& board, const vector<Point>& entities);
	void makeFruitInvisibile();
	void Reset(const Point& coord) override {} // Unused in Fruit class
	void Reset(const Board& board, const vector<Point>& entities); // Not the same same as Entity::Reset
};

