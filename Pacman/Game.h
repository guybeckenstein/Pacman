// This class is the actual infrastructure of Pac-Man game, using all the other classes
#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "BestGhost.h"
#include "Board.h"
#include "Fruit.h"
#include "GoodGhost.h"
#include "Menu.h"
#include "NoviceGhost.h"
#include "Pacman.h"

enum class gameConstants : char { MAX_OBJECTS = 6, GAME_SPEED = 100, ESC = 27, STAY = 5, QUIT = 6 };

using std::pair;

class Game
{
private:
	Fruit _fruit;
	Board _board;
	vector<Point> _entities; // All starting coordinators of Pac-Man and ghosts
	pair<Tunnel, Tunnel> _tunnels; // First - vertical tunnels, Second - horizontal tunnels
	int _difficultyLevel;
public:
	// Constructors
	Game(const string& screenName, bool colorAllowed, bool& isValid, int difficultyLevel = 1);
	// Getters
	bool isValidScreen(const string& name, vector<Point>& entities, vector<string>& currBoard);
	bool isLegendOnFirstLine(const string& string, int& width) const;
	const Fruit& getFruit() const { return _fruit; }
	const Board& getBoard() const { return _board; }
	const vector<Point>& getEntities() const { return _entities; }
	const pair<Tunnel, Tunnel>& getTunnels() const { return _tunnels; }
	// Setters
	void initializeTunnels(const vector<string>& board);
	// Methods
	bool Play(Pacman& pacman, vector<Ghost*>& ghosts, int& lives, int& score, bool colorAllowed);
	bool Move(Pacman& pacman, vector<Ghost*>& ghosts, int loopNumber, bool colorAllowed);
	void Print(int lives, int score, bool colorAllowed);
	void Reset(Pacman& pacman, vector<Ghost*>& ghosts);
	// Collision Methods
	bool pacmanGhostsCollision(Pacman& pacman, vector<Ghost*>& ghosts);
	bool pacmanEatsFruit(Pacman& pacman, bool colorAllowed);
	bool ghostsFruitCollision(vector<Ghost*>& ghosts, bool colorAllowed);
};