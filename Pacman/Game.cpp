#include "Game.h"
#include "GoodGhost.h"
#include "NoviceGhost.h"

// Constructors
Game::Game(const string& screenName, bool colorAllowed, bool& isValid, int difficultyLevel) : _fruit(), _board(), _difficultyLevel(difficultyLevel)
{
	vector<Point> entities(static_cast<int>(gameConstants::MAX_OBJECTS));
	vector<string> board(static_cast<int>(boardConstants::TABLE_MAX_HEIGHT));
	if (isValidScreen(screenName, entities, board) == true)
	{
		_board.initializeBoard(board, entities[0], entities[5]);
		initializeTunnels(board);
		_board.setLegend(entities[5]);
		_entities.reserve(5);
		_fruit.Reset(_board, entities);
		for (auto i = 0; i < entities.size() - 1; i++)
			if (entities[i].getX() != static_cast<int>(Directions::TRASH) && entities[i].getY() != static_cast<int>(Directions::TRASH))
				_entities.push_back(entities[i]);
		_entities.resize(_entities.size());
		isValid = true;
	}
	else
		isValid = false;
}
// Getters
bool Game::isValidScreen(const string& screenName, vector<Point>& entities, vector<string>& currBoard)
{
	Menu::clearScreen();
	bool res = true, illegalCharacter = false;
	int height = 0, width = 0, legendHeight = 0, countPacman = 0, countGhosts = 0, countLegend = 0;

	std::fstream currFile(screenName, std::ios::in);
	if (currFile.is_open() == false)
	{
		std::cout << "Invalid screen file '" << screenName << "': The file could not be opened." << std::endl;
		res = false;
	}
	else
	{
		string str;
		int j;
		for (auto i = 0; std::getline(currFile, str, '\n') && res == true && illegalCharacter == false; i++)
		{
			if (i == 0) // Checking only the first line, mainly for defining the width of the board
			{
				if (str == "")
					res = false;
				else if (isLegendOnFirstLine(std::move(str), width) == true)
				{
					width += 20;
					if (width < str.size())
						width = static_cast<int>(str.size());
				}
				else
					width = static_cast<int>(str.size());
			}
			j = checkLine(entities, currBoard, i, str, width, countPacman, countGhosts, countLegend, legendHeight, illegalCharacter); // Adds blank characters for lines which are shorter than board's width
			if (str[j] == '\0') // Adds blank characters for lines which are shorter than board's width
				while (j++ < width)
					currBoard[i].push_back(' ');
			height = i;
		}
		if (height == legendHeight)
		{
			int tmpHeight = height + 1;
			for (int k = 0; k < width; k++)
			{
				currBoard[height].push_back(' ');
				currBoard[tmpHeight].push_back(' ');
			}
			height += 3;
		}
		else if (height == legendHeight + 1)
		{
			for (size_t k = currBoard[height].size(); k < width; k++)
				currBoard[height].push_back(' ');
			height += 2;
		}
		else
			height += 1;
		currBoard.resize(height);
		if (res == true && illegalCharacter == false)
			seperateEntitiesFromBoard(entities, currBoard);
		isInvalidScreen(screenName, res, illegalCharacter, height, width, countPacman, countGhosts, countLegend);
	}
	currFile.close();
	Menu::clearScreen();
	return res;
}
int Game::checkLine(vector<Point>& entities, vector<string>& currBoard, int i, const string& line, int width, int& countPacman, int& countGhosts, int& countLegend, int& legendHeight, bool& illegalCharacter)
{
	int j;
	for (j = 0; illegalCharacter == false && line[j] != '\0' && j < width; j++)
	{
		currBoard[i].push_back(line[j]);
		if (line[j] == static_cast<char>(pacmanConstants::FIGURE))
		{
			entities[0].setX(j);
			entities[0].setY(i);
			countPacman++;
		}
		else if (line[j] == static_cast<char>(ghostConstants::FIGURE))
		{
			int ghostsIndex = 1 + countGhosts;
			entities[ghostsIndex].setX(j);
			entities[ghostsIndex].setY(i);
			countGhosts++;
		}
		else if (line[j] == static_cast<char>(boardConstants::LEGEND))
		{
			legendHeight = i;
			entities[5].setX(j);
			entities[5].setY(i);
			countLegend++;
		}
		// Illegal character check
		else if ((0 < line[j] && line[j] < static_cast<char>(boardConstants::BLANK)) || (static_cast<char>(boardConstants::BLANK) < line[j] && line[j] < static_cast<char>(boardConstants::WALL)) || (static_cast<char>(boardConstants::LEGEND) < line[j] && line[j] < static_cast<char>(boardConstants::BREADCRUMB)) || (static_cast<char>(boardConstants::BREADCRUMB) < line[j] && line[j] < static_cast<char>(pacmanConstants::FIGURE)) || static_cast<char>(pacmanConstants::FIGURE) < line[j])
			illegalCharacter = true;
	}
	return j;
}
// Every coordinator of an entity is initialized to a blank background, instead of it's game shape -> seperates board from entities (for instance: '@' would become ' ')
void Game::seperateEntitiesFromBoard(const vector<Point>& entities, vector<string>& currBoard) const
{
	for (auto i = 0; i < entities.size(); i++)
	{
		if (entities[i].getY() != static_cast<int>(Directions::TRASH) && entities[i].getX() != static_cast<int>(Directions::TRASH) && currBoard[entities[i].getY()][entities[i].getX()] != static_cast<char>(boardConstants::LEGEND))
			currBoard[entities[i].getY()][entities[i].getX()] = static_cast<char>(boardConstants::BLANK);
	}
}
// Updates 'res' (output parameter of function) if one of the if clauses is true, and prints an appropriate message for any case
void Game::isInvalidScreen(const string& screenName, bool& res, bool illegalCharacter, int height, int width, int countPacman, int countGhosts, int countLegend) const
{
	if (illegalCharacter == true)
	{
		std::cout << "Invalid screen file '" << screenName << "': contains an illegal character." << std::endl;
		res = false;
	}
	else if (width == 0)
	{
		std::cout << "Invalid screen file '" << screenName << "': empty screen." << std::endl;
		res = false;
	}
	else if (height > static_cast<int>(boardConstants::TABLE_MAX_HEIGHT))
	{
		std::cout << "Invalid screen file '" << screenName << "': too large horizontally." << std::endl;
		res = false;
	}
	else if (width > static_cast<int>(boardConstants::TABLE_MAX_WIDTH))
	{
		std::cout << "Invalid screen file '" << screenName << "': too large vertically." << std::endl;
		res = false;
	}
	else if (countPacman != 1)
	{
		std::cout << "Invalid screen file '" << screenName << "': does not contain just one Pac-Man." << std::endl;
		res = false;
	}
	else if (countGhosts > static_cast<int>(ghostConstants::MAX_GHOSTS))
	{
		std::cout << "Invalid screen file '" << screenName << "': contains too many ghosts." << std::endl;
		res = false;
	}
	else if (countLegend != 1)
	{
		std::cout << "Invalid screen file '" << screenName << "': does not contain just one legend area." << std::endl;
		res = false;
	}
}
// Function indicates through a boolean value if the first line of the input file includes a legend '&' 
bool Game::isLegendOnFirstLine(string&& string, int& width) const
{
	int i;
	for (i = 0; i < string.size(); i++)
		if (string[i] == static_cast<char>(boardConstants::LEGEND))
		{
			width = i;
			return true;
		}
	return false;
}
void Game::getStepsAndResultFiles(const string& screenName, string& stepsName, string& resultName)
{
	string testFileName = "";
	for (auto i = 0; screenName[i] != '.'; i++)
		testFileName.push_back(screenName[i]);
	stepsName = testFileName + ".steps";
	resultName = testFileName + ".result";
}
// Setters
void Game::initializeTunnels(const vector<string>& board) // For further information - readme (9). All characters which are not '#' -> a potential tunnel. Only '#' blocks tunnel option
{
	int maxWidth = static_cast<int>(board[0].size()), tmpMaxWidth = maxWidth - 1;
	int maxHeight = static_cast<int>(board.size()), tmpMaxHeight = maxHeight - 1;
	// Vertical search
	string str;
	for (int y = 0; y < maxHeight; y++)
	{
		if (board[y] == "")
			maxHeight--;
		else
		{
			str = board[y];
			if (str[0] != static_cast<char>(boardConstants::WALL) && str[tmpMaxWidth] != static_cast<char>(boardConstants::WALL))
				_tunnels.first.push_back({ {0, y}, {tmpMaxWidth, y} });
		}
	}
	// Horizontal search
	for (int x = 0, i = 0;  x < maxWidth; x++)
	{
		str = "";
		for (size_t y = 0; y < maxHeight; y++)
		{
			str = str + board[y][x];
		}
		if (str[0] != static_cast<char>(boardConstants::WALL) && str[tmpMaxHeight] != static_cast<char>(boardConstants::WALL))
			_tunnels.second.push_back({ {x, 0}, {x, tmpMaxHeight} });
	}
}
Directions Game::convertIntToDirections(int num) const
{
	if (num == 0)
		return Directions::UP;
	if (num == 1)
		return Directions::LEFT;
	if (num == 2)
		return Directions::DOWN;
	else if (num == 3)
		return Directions::RIGHT;
	else
		return Directions::TRASH;
}
// Operators
std::ostream& operator<<(std::ostream& out, Directions direction)
{
	if (direction == Directions::UP)
		return out << 0;
	else if (direction == Directions::LEFT)
		return out << 1;
	else if (direction == Directions::DOWN)
		return out << 2;
	else if (direction == Directions::RIGHT)
		return out << 3;
	return out << -1;
}
// Save Mode Methods
bool Game::PlayEx2Mode(const string& screenName, bool saveMode, Pacman& pacman, vector<Ghost*>& ghosts, int& lives, int& score, bool colorAllowed) // Loop continue running until player wins, or loses
{
	bool isFirstMove = false;
	string stepsName, resultName, stepsNameTmp;
	if (saveMode == true)
		getStepsAndResultFiles(screenName, stepsName, resultName);
	std::fstream stepsFile;

	static int pointOfTimeCounter;
	int loopNumber = 0;
	vector<int> pointsOfTime;
	pointsOfTime.reserve(pacman.getLives());

	bool playerQuits = false; // If player pauses game, then decides to quit by pressing 'q' or 'Q', he would get back to menu
	if (saveMode == true)
	{
		stepsNameTmp = stepsName + ".temp";
		std::ofstream stepsFile(stepsNameTmp, std::fstream::out | std::fstream::trunc);
		if (stepsFile.is_open() == false)
			throw stepsName;
		if (colorAllowed == true)
			stepsFile << "true" << std::endl;
		else
			stepsFile << "false" << std::endl;
		stepsFile.close();
	}
	while (pacman.getLives() > 0 && _board.getNumberOfBreadcrumbs() > 0 && playerQuits == false) // Unless the Pac-Man dies or it wins and gets all breadcrumbs
	{
		if (pacman.getFirstMove() == false) // Board, Pac-Man, the ghosts and the fruit are initially being printed. Game freezes until the player presses a key
		{
			// Prints board
			getBoard().Print(colorAllowed, screenName);
			pacman.Print(colorAllowed, static_cast<int>(colorConstants::YELLOW)); // Prints Pac-Man
			for (auto i = 0; i < ghosts.size(); i++)
				ghosts[i]->Print(colorAllowed, static_cast<int>(colorConstants::RED)); // Prints the ghosts
			if (getFruit().getVisibility() == true)
				getFruit().Print(colorAllowed, static_cast<int>(colorConstants::LIGHTMAGENTA)); // Prints the fruit
			while (!_kbhit())
				Print(pacman.getLives(), pacman.getScore(), colorAllowed); // Prints text
		}
		Point fruitCoord = getFruit().getCoord();
		int tmpX = getFruit().getCoord().getX(), tmpY = getFruit().getCoord().getY();
		playerQuits = Move(stepsNameTmp, pacman, ghosts, loopNumber, colorAllowed, saveMode); // Updates the coordinator of Pac-Man, the ghosts and the fruit
		pointOfTimeCounter++;
		loopNumber++;
		if (playerQuits == false)
		{
			bool isEatByPacman;
			if (getFruit().getVisibility() == true && ((isEatByPacman = pacmanEatsFruit(pacman, colorAllowed)) == true || ghostsFruitCollision(ghosts, colorAllowed) == true))
			{
				if (isEatByPacman == true)
					pacman.setScore(pacman.getScore() + getFruit().getNumber()); // Increases Pac-Man's score by the actual size that was presented by the fruit
				_fruit.makeFruitInvisibile(); // Fruit disappears until its next visibility counter ends
			}
			else if (pacmanGhostsCollision(pacman, ghosts) == true)
			{
				pointsOfTime.push_back(pointOfTimeCounter); // Adds the current Pac-Man's death point of time
				loopNumber = 0; // Resets ghosts' and fruit's movement
				Reset(pacman, ghosts); // Reduces Pac-Man's life and resets the game in case needed
			}
			if (_board.isBreadcrumb(pacman.getCoord().getX(), pacman.getCoord().getY()) == true)
			{
				_board.removeBreadcrumb(pacman.getCoord().getX(), pacman.getCoord().getY()); // Removes the breadcrumb itself
				_board.updateTotalBreadcrumbs(); // Decreases total breadcrumbs number
				pacman.updateScore(); // Increases Pac-Man's score
			}
			if (saveMode == true)
			{
				std::ofstream stepsFile(stepsNameTmp, std::fstream::out | std::fstream::app);
				if (stepsFile.is_open() == false)
					throw stepsName;
				if ((loopNumber - 1) % getFruit().getMovementFrequency() == 0)
				{
					stepsFile << " " << getFruit().getDirection(); // fruit information
					if (getFruit().getVisibility() == true)
						stepsFile << " " << "true";
					else
						stepsFile << " " << "false";
					stepsFile << " " << getFruit().getNumber() << " " << tmpX << " " << tmpY;
				}
				stepsFile << std::endl;
				stepsFile.close();
			}
			// Printing player's lives and score status every loop
			Print(pacman.getLives(), pacman.getScore(), colorAllowed);
		}
	}
	// Writes all points of time to 'pacman_*.result' file
	if (playerQuits == false)
	{
		int dummy = rename(stepsNameTmp.c_str(), stepsName.c_str());
		createResultFile(resultName, pointsOfTime, pointOfTimeCounter);
	}
	else
		remove(stepsNameTmp.c_str());
	// End of loop -> means that the player has won or lost.
	Outcome(pacman.getLives(), _board.getNumberOfBreadcrumbs(), getBoard().getLegend().getX(), getBoard().getLegend().getY(), colorAllowed);
	// Aftermath
	lives = pacman.getLives();
	score = pacman.getScore();
	pointOfTimeCounter = 0;
	return playerQuits;
}
bool Game::Move(const string& stepsName, Pacman& pacman, vector<Ghost*>& ghosts, int loopNumber, bool colorAllowed, bool saveMode)
{
	int tmpX = getFruit().getCoord().getX(), tmpY = getFruit().getCoord().getY();
	// Fruit moves every four loops
	if (getFruit().getVisibility() == true && loopNumber % getFruit().getMovementFrequency() == 0)
	{
		if (loopNumber % static_cast<int>(fruitConstants::FRUIT_TIMER) == 0 && loopNumber > 0)
		{
			int x = getFruit().getCoord().getX(), y = getFruit().getCoord().getY();
			Menu::gotoxy(x, y);
			if (_board.isBreadcrumb(x, y))
			{
				if (colorAllowed == true)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::BROWN));
				std::cout << static_cast<char>(boardConstants::BREADCRUMB) << std::endl;
			}
			else
				std::cout << static_cast<char>(boardConstants::BLANK) << std::endl;
			_fruit.makeFruitInvisibile();
		}
		else
		{
			_fruit.eraseRender(colorAllowed, _board.isBreadcrumb(_fruit.getCoord().getX(), _fruit.getCoord().getY()), _fruit.getCoord());
			_fruit.Move(getTunnels(), _board, colorAllowed);
			_fruit.Print(colorAllowed, static_cast<int>(colorConstants::LIGHTMAGENTA));
		}
	}
	else if (getFruit().getVisibility() == false && loopNumber % (getFruit().getMovementFrequency() * static_cast<int>(fruitConstants::FRUIT_TIMER)) == 0)
	{
		_fruit.setStartingCoord(_board, getEntities());
		_fruit.Reset(_board, getEntities());
	}
	// Pac-Man moves every loop
	Point tmpCoord = pacman.getCoord();
	bool isQuit = pacman.Move(getTunnels(), _board, colorAllowed);
	pacman.eraseRender(colorAllowed, _board.isBreadcrumb(tmpCoord.getX(), tmpCoord.getY()), tmpCoord);
	pacman.Print(colorAllowed, static_cast<int>(colorConstants::YELLOW));
	// Ghosts move every two loops
	bool isSmart = false;
	if (ghosts.size() > 0 && loopNumber % ghosts[0]->getMovementFrequency() == 0)
	{
		for (auto i = 0; i < ghosts.size(); i++)
		{
			ghosts[i]->eraseRender(colorAllowed, _board.isBreadcrumb(ghosts[i]->getCoord().getX(), ghosts[i]->getCoord().getY()), ghosts[i]->getCoord());
			ghosts[i]->Move(getTunnels(), _board, colorAllowed);
			isSmart = ghosts[i]->setTargetCoord(pacman.getCoord());
			ghosts[i]->Print(colorAllowed, static_cast<int>(colorConstants::RED));
		}
	}
	if (isSmart == true)
		Sleep(static_cast<int>(gameConstants::GAME_SPEED) / 2); // Multiplies game speed
	else
		Sleep(static_cast<int>(gameConstants::GAME_SPEED));
	if (saveMode == true)
	{
		// Write to file
		std::ofstream stepsFile(stepsName, std::fstream::out | std::fstream::app);
		if (stepsFile.is_open() == false)
			throw stepsName;
		// PACMAN
		stepsFile << pacman.getDirection();
		// GHOSTS
		if (loopNumber % ghosts[0]->getMovementFrequency() == 0)
			for (auto& n : ghosts)
				stepsFile << " " << n->getDirection();
		// FRUIT
		if (loopNumber % getFruit().getMovementFrequency() == 0)
		{
			stepsFile << " " << getFruit().getDirection(); // fruit information
		}
		stepsFile.close();
	}
	return isQuit;
}
// Function's output is the final screen message that is printed, after each game screen
void Game::Outcome(int lives, int totalBreadcrumbs, int legendX, int legendY, bool colorAllowed) const
{
	string str1, str2;
	if (lives == 0)
	{
		str1 = "YOU LOST!";
		str2 = "Better luck next time.";
	}
	else if (totalBreadcrumbs == 0)
	{
		str1 = "YOU WON!";
		str2 = "Congratulations.";
	}
	else // If player pressed 'q' or 'Q'
	{
		str1 = "YOU QUIT!";
		str2 = "Never give up.";
	}
	// Output
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::WHITE));
	Menu::gotoxy(legendX, legendY);
	std::cout << str1 << std::endl;
	Menu::gotoxy(legendX, legendY + 1);
	std::cout << str2 << std::endl;
	Sleep(5 * static_cast<int>(gameConstants::GAME_SPEED));
	Menu::clearScreen();
	std::cout << str1 << std::endl << str2 << std::endl;
	Menu::pauseScreen();
}
void Game::createResultFile(const string& resultName, const vector<int>& pointsOfTime, int pointOfTimeCounter) const // Writes all points of time to 'pacman_*.result' file
{
	std::fstream resultFile(resultName, std::fstream::out | std::fstream::trunc);
	if (resultFile.is_open() == false)
		throw resultName.c_str();
	for (size_t i = 0; i < pointsOfTime.size(); i++)
	{
		if (i > 0)
			resultFile << " ";
		resultFile << pointsOfTime[i];
	}
	resultFile << std::endl;
	resultFile << pointOfTimeCounter;
	resultFile.close();
}
// Load Mode Methods
bool Game::playLoadMode(const string& screenName, bool silentMode, Pacman& pacman, vector<Ghost*>& ghosts, int& lives, int& score, bool colorAllowed) // Loop continue running until player wins, or loses
{
	string stepsName, resultName;
	getStepsAndResultFiles(screenName, stepsName, resultName);
	std::fstream stepsFile(stepsName, std::ios::in);
	if (stepsFile.is_open() == false)
		throw stepsName;
	static int pointOfTimeCounter; // general
	int loopNumber = 0; // for movement
	vector<int> pointsOfTime;
	pointsOfTime.reserve(pacman.getLives());
	string boolLine;
	std::getline(stepsFile, boolLine, '\n');
	colorAllowed = (boolLine.compare("true") == 0);
	if (silentMode == false)
	{
		getBoard().Print(colorAllowed, screenName);
		Print(pacman.getLives(), pacman.getScore(), colorAllowed);
		pacman.Print(colorAllowed, static_cast<int>(colorConstants::YELLOW));
		for (auto& i: ghosts)
			i->Print(colorAllowed, static_cast<int>(colorConstants::RED));
		_fruit.Print(colorAllowed, static_cast<int>(colorConstants::LIGHTMAGENTA));
	}
	while (pacman.getLives() > 0 && _board.getNumberOfBreadcrumbs() > 0) // Unless the Pac-Man dies or it wins and gets all breadcrumbs
	{
		Move(stepsFile, silentMode, pacman, ghosts, loopNumber, colorAllowed); // Updates the coordinator of Pac-Man, the ghosts and the fruit
		pointOfTimeCounter++;
		loopNumber++;
		bool isEatByPacman;
		if (getFruit().getVisibility() == true && ((isEatByPacman = pacmanEatsFruit(pacman, colorAllowed)) == true || ghostsFruitCollision(ghosts, colorAllowed) == true))
		{
			if (isEatByPacman == true)
				pacman.setScore(pacman.getScore() + getFruit().getNumber()); // Increases Pac-Man's score by the actual size that was presented by the fruit
			_fruit.makeFruitInvisibile(); // Fruit disappears until its next visibility counter ends
		}
		else if (pacmanGhostsCollision(pacman, ghosts) == true)
		{
			pointsOfTime.push_back(pointOfTimeCounter); // Adds the current Pac-Man's death point of time
			loopNumber = 0; // Resets ghosts' and fruit's movement
			if (silentMode == false)
			{
				getFruit().eraseRender(colorAllowed, _board.isBreadcrumb(getFruit().getCoord().getX(), getFruit().getCoord().getY()), getFruit().getCoord());
				for (size_t i = 0; i < ghosts.size(); i++)
					ghosts[i]->eraseRender(colorAllowed, _board.isBreadcrumb(ghosts[i]->getCoord().getX(), ghosts[i]->getCoord().getY()), ghosts[i]->getCoord());
				pacman.eraseRender(colorAllowed, _board.isBreadcrumb(pacman.getCoord().getX(), pacman.getCoord().getY()), pacman.getCoord());
			}
			Reset(pacman, ghosts); // Reduces Pac-Man's life and resets the game in case needed
		}
		if (_board.isBreadcrumb(pacman.getCoord().getX(), pacman.getCoord().getY()) == true)
		{
			_board.removeBreadcrumb(pacman.getCoord().getX(), pacman.getCoord().getY()); // Removes the breadcrumb itself
			_board.updateTotalBreadcrumbs(); // Decreases total breadcrumbs number
			pacman.updateScore(); // Increases Pac-Man's score
		}
		// Printing player's lives and score status every loop
		if (silentMode == false)
			Print(pacman.getLives(), pacman.getScore(), colorAllowed);
	}
	stepsFile.close();
	// Reads all points of time from 'pacman_*.result' file
	vector<int> pointsOfTimeCmp;
	int resultPointOfTime;

	readResultFile(resultName, pointsOfTimeCmp, resultPointOfTime);
	// Aftermath
	lives = pacman.getLives();
	score = pacman.getScore();
	// Compares outputs
	if (silentMode == false)
		Menu::clearScreen();
	bool res = isValidResult(pointsOfTime, pointsOfTimeCmp, pointOfTimeCounter, resultPointOfTime);
	pointOfTimeCounter = 0;
	return res;
}
void Game::Move(std::fstream& stepsFile, bool silentMode, Pacman& pacman, vector<Ghost*>& ghosts, int loopNumber, bool colorAllowed)
{
	string line;
	std::getline(stepsFile, line, '\n');
	size_t size = 1 + ghosts.size() + 1;
	vector<int> entitiesDirections;
	entitiesDirections.reserve(size);
	static bool fruitVisibility = true;
	static int fruitNumber, fruitX, fruitY;
	readLineFromStepsFile(loopNumber, ghosts.size(), line, entitiesDirections, fruitVisibility, fruitNumber, fruitX, fruitY);
	// Pac-Man moves every loop
	Point tmpCoord = pacman.getCoord();
	if (silentMode == false)
		pacman.eraseRender(colorAllowed, _board.isBreadcrumb(tmpCoord.getX(), tmpCoord.getY()), tmpCoord);
	tmpCoord.updateCoord(convertIntToDirections(entitiesDirections[0]));
	pacman.setPacman(tmpCoord, getTunnels());
	if (silentMode == false)
		pacman.Print(colorAllowed, static_cast<int>(colorConstants::YELLOW));
	// Ghosts move every two loops
	Point pointToUpdate(0, 0);
	if (ghosts.size() > 0 && loopNumber % ghosts[0]->getMovementFrequency() == 0)
	{
		for (size_t i = 0; i < ghosts.size(); i++)
		{
			size_t ghostIndex = i + 1;
			if (silentMode == false)
				ghosts[i]->eraseRender(colorAllowed, _board.isBreadcrumb(ghosts[i]->getCoord().getX(), ghosts[i]->getCoord().getY()), ghosts[i]->getCoord());
			pointToUpdate = ghosts[i]->getCoord();
			pointToUpdate.updateCoord(convertIntToDirections(entitiesDirections[ghostIndex]));
			ghosts[i]->setCoord(pointToUpdate);
			if (silentMode == false)
				ghosts[i]->Print(colorAllowed, static_cast<int>(colorConstants::RED));
		}
	}
	// Fruit moves every four loops
	size_t fruitIndex = ghosts.size() + 1;
	if (silentMode == false && _fruit.getVisibility() == true)
		_fruit.eraseRender(colorAllowed, _board.isBreadcrumb(_fruit.getCoord().getX(), _fruit.getCoord().getY()), _fruit.getCoord());
	_fruit.setCoord({ fruitX, fruitY });
	_fruit.setNumber(fruitNumber);
	_fruit.setVisibility(fruitVisibility);
	if (silentMode == false && getFruit().getVisibility() == true)
		_fruit.Print(colorAllowed, static_cast<int>(colorConstants::LIGHTMAGENTA));

	if (silentMode == false)
		Sleep(static_cast<int>(gameConstants::GAME_SPEED));
}
void Game::readLineFromStepsFile(int loopNumber, size_t numOfGhosts, const string& string, vector<int>& entitiesDirections, bool& fruitVisibility, int& fruitNumber, int& fruitX, int& fruitY) const
{
	bool isRead = false;
	int i;
	std::string tmpNumber = "";
	// Copies first line integers into a vector of points of time
	for (i = 0; isRead == false && string[i] != '\0'; i++)
	{
		if (string[i] != ' ')
			tmpNumber.push_back(string[i]);
		else if (tmpNumber.compare("true") != 0 && tmpNumber.compare("false") != 0)
		{
			tmpNumber.push_back('\0');
			entitiesDirections.push_back(std::stoi(tmpNumber));
			tmpNumber = "";
		}
		else
		{
			if (tmpNumber.compare("true") == 0)
				fruitVisibility = true;
			else
				fruitVisibility = false;
			tmpNumber = "";
			i++;
			tmpNumber.push_back(string[i]);
			tmpNumber.push_back('\0');
			fruitNumber = stoi(tmpNumber);
			tmpNumber = "";
			i++;
			i++;
			while (string[i] != ' ')
				tmpNumber.push_back(string[i++]);
			tmpNumber.push_back('\0');
			fruitX = stoi(tmpNumber);
			tmpNumber = "";
			i++;
			while (string[i] != ' ' && string[i] != '\0')
				tmpNumber.push_back(string[i++]);
			tmpNumber.push_back('\0');
			fruitY = stoi(tmpNumber);

			isRead = true;
		}
	}
	if (tmpNumber.compare("") != 0 && isRead == false)
	{
		tmpNumber.push_back('\0');
		entitiesDirections.push_back(std::stoi(tmpNumber));
	}
	entitiesDirections.resize(entitiesDirections.size());
}
// Gets points of time from result file, for comparing it later
void Game::readResultFile(const string& resultName, vector<int>& pointsOfTimeCmp, int& resultPointOfTime) const
{
	string firstLine, secondLine;

	std::fstream resultFile(resultName, std::fstream::in);
	if (resultFile.is_open() == false)
		throw resultName.c_str();
	std::getline(resultFile, firstLine, '\n');
	std::getline(resultFile, secondLine, '\n'); // may be '\0'
	resultFile.close();

	getPointsOfTime(firstLine, secondLine, pointsOfTimeCmp, resultPointOfTime);
}
void Game::getPointsOfTime(const string& firstLine, const string& secondLine, vector<int>& pointsOfTimeCmp, int& resultPointOfTime) const
{
	string tmpNumber = "";
	// Copies first line integers into a vector of points of time
	for (int i = 0; firstLine[i] != '\0'; i++)
	{
		if (firstLine[i] != ' ')
			tmpNumber.push_back(firstLine[i]);
		else
		{
			tmpNumber.push_back('\0');
			pointsOfTimeCmp.push_back(std::stoi(tmpNumber));
			tmpNumber = "";
		}
	}
	if (tmpNumber.compare("") != 0)
		pointsOfTimeCmp.push_back(std::stoi(tmpNumber));
	// Copies second line integer into a variable
	resultPointOfTime = std::stoi(secondLine);
}
bool Game::isValidResult(const vector<int>& pointsOfTime, const vector<int>& pointsOfTimeCmp, int pointOfTimeCounter, int resultPointOfTime) const
{
	// Compares final point of time result, and amount of Pac-Man's deaths
	if (pointOfTimeCounter != resultPointOfTime || pointsOfTime.size() != pointsOfTimeCmp.size())
		return false;
	else
	{ // Compares all Pac-Man's deaths points of time
		for (size_t i = 0; i < pointsOfTime.size(); i++)
			if (pointsOfTime[i] != pointsOfTimeCmp[i])
				return false;
		return true;
	}
}
void Game::Print(int lives, int score, bool colorAllowed) // Function to display legend message
{
	Menu::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::WHITE));
	std::cout << "LIVES: " << lives << std::endl;
	Menu::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY() + 1);
	std::cout << "SCORE: " << score;
}
void Game::Reset(Pacman& pacman, vector<Ghost*>& ghosts) // Used when initializing or resetting the game (when Pac-Man hits a ghost or when playing again)
{
	// Pac-Man resetting
	pacman.Reset(getEntities()[0]);
	// Ghosts resetting
	for (auto i = 0; i < ghosts.size(); i++)
	{
		int entityIndex = i + 1;
		if (getEntities()[entityIndex].getY() != static_cast<int>(Directions::TRASH) && getEntities()[entityIndex].getX() != static_cast<int>(Directions::TRASH))
			ghosts[i]->Reset(getEntities()[entityIndex]);
	}
	// Fruit resetting
	_fruit.Reset(_board, getEntities());
	// Life status print resetting
	Menu::clearLegendArea(getBoard().getLegend());
}
// Collision Methods
bool Game::pacmanGhostsCollision(Pacman& pacman, vector<Ghost*>& ghosts) // Function for every possible collision of Pac-Man and ghosts, returning true if there is.
{
	bool res = false;
	static int x, y;
	// In case Pac-Man's old coordinator is equal to one of ghosts' coordinator
	for (auto i = 0; res == false && i < ghosts.size(); i++)
	{
		if (ghosts[i]->getCoord() == Point(x, y))
			res = true;
	}
	// In case Pac-Man's coordinator is equal to one of ghosts' coordinator
	x = pacman.getCoord().getX();
	y = pacman.getCoord().getY();
	for (auto i = 0; res == false && i < ghosts.size(); i++)
	{
		if (ghosts[i]->getCoord() == Point(x, y))
			res = true;
	}
	if (res == true)
		x = y = 0;
	return res;
}
bool Game::pacmanEatsFruit(Pacman& pacman, bool colorAllowed) // Checks if Pac-Man eats the fruit, returning true in case he does.
{
	bool res = false;
	static int x, y;
	// In case Pac-Man's old coordinator is equal fruit's coordinator
	if (getFruit().getCoord() == Point(x, y))
	{
		// Prevents double figure printing
		Menu::gotoxy(x, y);
		std::cout << static_cast<char>(boardConstants::BLANK) << std::endl;
		// Prints Pac-Man
		pacman.Print(colorAllowed, static_cast<int>(colorConstants::YELLOW));
		res = true;
	}
	// In case Pac-Man's coordinator is equal to fruit's coordinator
	x = pacman.getCoord().getX();
	y = pacman.getCoord().getY();
	if (res == false && getFruit().getCoord() == Point(x, y))
	{
		pacman.Print(colorAllowed, static_cast<int>(colorConstants::YELLOW));
		res = true;
	}
	if (res == true)
		x = y = 0;
	return res;
}
bool Game::ghostsFruitCollision(vector<Ghost*>& ghosts, bool colorAllowed) // Checks if one of the ghosts hits the fruit, returning true in case they do.
{
	bool res = false;
	int i;
	static int x, y;
	// In case fruit's old coordinator is equal to one of ghosts' coordinator
	for (i = 0; res == false && i < ghosts.size(); i++)
	{
		if (ghosts[i]->getCoord() == Point(x, y))
		{
			// Prevents double figure printing
			Menu::gotoxy(x, y);
			if (_board.isBreadcrumb(x, y))
			{
				if (colorAllowed == true)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::BROWN));
				std::cout << static_cast<char>(boardConstants::BREADCRUMB) << std::endl;
			}
			else
				std::cout << static_cast<char>(boardConstants::BLANK) << std::endl;
			// Prints ghosts
			ghosts[i]->Print(colorAllowed, static_cast<int>(colorConstants::RED));
			res = true;
		}
	}
	// In case fruit's coordinator is equal to one of ghosts' coordinator
	x = getFruit().getCoord().getX(), y = getFruit().getCoord().getY();
	for (i = 0; res == false && i < ghosts.size(); i++)
	{
		if (ghosts[i]->getCoord() == Point(x, y))
		{
			// Prints ghosts
			ghosts[i]->Print(colorAllowed, static_cast<int>(colorConstants::RED));
			res = true;
		}
	}
	if (res == true)
		x = y = 0;
	return res;
}