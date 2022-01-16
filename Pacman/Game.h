// This class is the actual infrastructure of Pac-Man game, using all the other classes
#pragma once

#include <fstream>
#include "BestGhost.h"
#include "Board.h"
#include "Fruit.h"
#include "Menu.h"
#include "Pacman.h"

enum class gameConstants : char { MAX_OBJECTS = 6, GAME_SPEED = 100, ESC = 27, QUIT = 6 };

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
	bool isValidScreen(const string& screenName, vector<Point>& entities, vector<string>& currBoard);
	int checkLine(vector<Point>& entities, vector<string>& currBoard, int i, const string& line, int width, int& countPacman, int& countGhosts, int& countLegend, int& legendHeight, bool& illegalCharacter);
	void seperateEntitiesFromBoard(const vector<Point>& entities, vector<string>& currBoard) const;
	void isInvalidScreen(const string& screenName, bool& res, bool illegalCharacter, int height, int width, int countPacman, int countGhosts, int countLegend) const;
	bool isLegendOnFirstLine(string&& string, int& width) const;
	// Getters
	const Fruit& getFruit() const { return _fruit; }
	const Board& getBoard() const { return _board; }
	const vector<Point>& getEntities() const { return _entities; }
	const pair<Tunnel, Tunnel>& getTunnels() const { return _tunnels; }
	// Operators
	friend std::ostream& operator<<(std::ostream& out, Directions direction);
	// Setters
	void initializeTunnels(const vector<string>& board);
	Directions convertIntToDirections(int num) const;
	// Save Mode Methods
	static void getStepsAndResultFiles(const string& screenName, string& stepsName, string& resultName);
	bool PlayEx2Mode(const string& screenName, bool saveMode, Pacman& pacman, vector<Ghost*>& ghosts, int& lives, int& score, bool colorAllowed); // Play function is overloaded
	bool Move(const string& stepsName, Pacman& pacman, vector<Ghost*>& ghosts, int loopNumber, bool colorAllowed, bool saveMode); // Move function is overloadde
	void Outcome(int lives, int totalBreadcrumbs, int legendX, int legendY, bool colorAllowed) const;
	void createResultFile(const string& resultName, const vector<int>& pointsOfTime, int pointOfTimeCounter) const;
	// Load Mode Methods
	bool playLoadMode(const string& screenName, bool silentMode, Pacman& pacman, vector<Ghost*>& ghosts, int& lives, int& score, bool colorAllowed); // Play function is overloaded
	void Move(std::fstream& stepsFile, bool silentMode, Pacman& pacman, vector<Ghost*>& ghosts, int loopNumber, bool colorAllowed);
	void readLineFromStepsFile(int loopNumber, size_t numOfGhosts, const string& string, vector<int>& entitiesDirections, bool& fruitVisibility, int& fruitNumber, int& fruitX, int& fruitY) const;
	void readResultFile(const string& resultName, vector<int>& pointsOfTimeCmp, int& resultPointOfTime) const;
	void getPointsOfTime(const string& firstLine, const string& secondLine, vector<int>& pointsOfTimeCmp, int& resultPointOfTime) const;
	bool isValidResult(const vector<int>& pointsOfTime, const vector<int>& pointsOfTimeCmp, int pointOfTimeCounter, int resultPointOfTime) const;
	// General Game Methods
	void Print(int lives, int score, bool colorAllowed);
	void Reset(Pacman& pacman, vector<Ghost*>& ghosts);
	// Game Collision Methods
	bool pacmanGhostsCollision(Pacman& pacman, vector<Ghost*>& ghosts);
	bool pacmanEatsFruit(Pacman& pacman, bool colorAllowed);
	bool ghostsFruitCollision(vector<Ghost*>& ghosts, bool colorAllowed);
};