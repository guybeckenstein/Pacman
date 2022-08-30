// The class is used to define the Pac-Man object in the game
#pragma once

#include "Entity.h"

enum class pacmanConstants : int { FIGURE = '@', MOVEMENT_FREQUENCY = 1, INIT_LIVES = 3, INIT_SCORE = 0 };

class Pacman : public Entity
{
private:
	int _lives;
	int _score;
public:
	// Constructors
	Pacman(int startingX, int startingY, int movementFrequency = static_cast<int>(pacmanConstants::MOVEMENT_FREQUENCY), int lives = static_cast<int>(pacmanConstants::INIT_LIVES), int score = 0) : Entity(startingX, startingY, movementFrequency), _lives(lives), _score(score) { }
	~Pacman() override = default;
	// Getters
	int getLives() const { return _lives; }
	int getScore() const { return _score; }
	// Setters
	void setPacman(const Point& coord, const pair<Tunnel, Tunnel>& tunnels); // If Pac-Man goes under one of the tunnels, the function updates its values
	void setLives(int lives) { _lives = lives; }
	void setScore(int score) { _score = score; }
	void updateLife() { (_lives)--; } // Decreases Pac-Man's life by one
	void updateScore() { (_score)++; } // Increases Pac-Man's score by one
	// Movement Methods
	bool Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) override;
	char getArrowKeys(const Board& board, bool colorAllowed);
	bool getNextDirection(const pair<Tunnel, Tunnel>& tunnels, const Board& board, char key, Directions& nextDirection, bool& nextToTunnel);
	bool checkForTunnels(const pair<Tunnel, Tunnel>& tunnels, const Board& board, char key);
	// Reset / Reinitialize Methods
	void Render(std::ostream& os) const override { os << static_cast<char>(pacmanConstants::FIGURE); }
	void Reset(const Point& coord) override;
};

