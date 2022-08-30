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
	Fruit(int movementFrequency = static_cast<int>(fruitConstants::MOVEMENT_FREQUENCY)) : Entity(movementFrequency), _number(static_cast<int>(Directions::TRASH)), _isVisible(false) {}
	~Fruit() override = default;
	// Getters
	int getNumber() const { return _number; }
	bool getVisibility() const { return _isVisible; }
<<<<<<< HEAD
=======
	// Setters
	void setNumber() { _number = (rand() % static_cast<int>(fruitConstants::TOTAL_DIVISION_OPTIONS)) + static_cast<int>(fruitConstants::TOTAL_DIVISION_OPTIONS); }
	void setNumber(int number) { _number = number; }
	void setVisibility(bool value) { _isVisible = value; }
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	// Methods
	void setStartingCoord(const Board& board, const vector<Point>& entities);
	void makeFruitInvisibile();
<<<<<<< HEAD
	void Reset(const Board& board, const vector<Point>& entities);
private:
	// Setters
	void setNumber() { _number = (rand() % valOf(fruitConstants::TOTAL_DIVISION_OPTIONS)) + valOf(fruitConstants::TOTAL_DIVISION_OPTIONS); }
	// Methods
	void Render(std::ostream& os) const override { os << getNumber(); }
	void setVisibility(bool value) { _isVisible = value; }
};

=======
	void Reset(const Board& board, const vector<Point>& entities); // Not the same same as Entity::Reset
	void Reset(const Point& coord) override {} // Entity::Reset - this line is unused but enables compilation
};
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
