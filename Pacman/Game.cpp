#include "Game.h"
#include "ConsoleApp.h"

const char* CLEAR = "                                              ";

// Constructors
Game::Game(const string& screenName, bool colorAllowed, bool& isValid, int difficultyLevel) : _fruit(), _board(), _difficultyLevel(difficultyLevel)
{
	vector<Point> entities(valOf(gameConstants::MAX_OBJECTS));
	vector<string> board(valOf(boardConstants::MAX_HEIGHT));
	if (isValidScreen(screenName, entities, board) == true)
	{
		_board.initializeBoard(board, entities[0], entities[5]);
		initializeTunnels(board);
		_board.setLegend(entities[5]);
		_entities.reserve(5);
		_fruit.Reset(_board, entities);
		int i;
		for (i = 0; i < entities.size() - 1; i++)
			if (entities[i].getX() != valOf(pointConstants::TRASH) && entities[i].getY() != valOf(pointConstants::TRASH))
				_entities.push_back(entities[i]);
		_entities.resize(_entities.size());
		isValid = true;
	}
	else
		isValid = false;
}
// Getters
bool Game::isValidScreen(const string& name, vector<Point>& entities, vector<string>& currBoard)
{
	ConsoleApp::clearScreen();
	bool res = true, firstChar = false, illegalCharacter = false;
	char firstCharLine = 0;
	int height = 0, legendHeight = 0, width = 0, countPacman = 0, countGhosts = 0, countLegend = 0;
	std::fstream currFile;
	string str;

	currFile.open(name);
	if (currFile.is_open() == false)
	{
		std::cout << "Invalid screen file '" << name << "': The file could not be opened." << std::endl;
		res = false;
	}
	else
	{
		int j;
		for (auto i = 0; std::getline(currFile, str, '\n') && res == true && illegalCharacter == false; i++)
		{
			if (i == 0)
			{
				if (str == "")
					res = false;
				else if (isLegendOnFirstLine(str, width) == true)
				{
					width += 20;
					if (width < str.size())
						width = static_cast<int>(str.size());
				}
				else
					width = static_cast<int>(str.size());
			}
			for (j = 0; illegalCharacter == false && str[j] != '\0' && j < width; j++)
			{
				currBoard[i].push_back(str[j]);
				if (str[j] == valOf(pacmanConstants::FIGURE))
				{
					entities[0].setX(j);
					entities[0].setY(i);
					countPacman++;
				}
				else if (str[j] == valOf(ghostConstants::FIGURE))
				{
					int tmpIndex = 1 + countGhosts;
					entities[tmpIndex].setX(j);
					entities[tmpIndex].setY(i);
					countGhosts++;
				}
				else if (str[j] == valOf(boardConstants::LEGEND))
				{
					legendHeight = i;
					entities[5].setX(j);
					entities[5].setY(i);
					countLegend++;
				}
				else if ((0 < str[j] && str[j] < valOf(boardConstants::BLANK)) || (valOf(boardConstants::BLANK) < str[j] && str[j] < valOf(boardConstants::WALL)) || (valOf(boardConstants::LEGEND) < str[j] && str[j] < valOf(boardConstants::BREADCRUMB)) || (valOf(boardConstants::BREADCRUMB) < str[j] && str[j] < valOf(pacmanConstants::FIGURE)) || valOf(pacmanConstants::FIGURE) < str[j])
					illegalCharacter = true;
			}
			if (str[j] == '\0')
			{
				while (j < width)
				{
					currBoard[i].push_back(' ');
					j++;
				}
			}
			height = i;
		}
		if (height == legendHeight)
			height += 3;
		else if (height == legendHeight + 1)
			height += 2;
		else
			height += 1;
		currBoard.resize(height);
		for (auto i = 0; res == true && illegalCharacter == false && i < entities.size(); i++)
		{
			if (entities[i].getY() != valOf(pointConstants::TRASH) && entities[i].getX() != valOf(pointConstants::TRASH) && currBoard[entities[i].getY()][entities[i].getX()] != valOf(boardConstants::LEGEND))
				currBoard[entities[i].getY()][entities[i].getX()] = valOf(boardConstants::BLANK);
		}
		if (illegalCharacter == true)
		{
			std::cout << "Invalid screen file '" << name << "': contains an illegal character." << std::endl;
			res = false;
		}
		else if (width == 0)
		{
			std::cout << "Invalid screen file '" << name << "': empty screen." << std::endl;
			res = false;
		}
		else if (height > 25)
		{
			std::cout << "Invalid screen file '" << name << "': too large horizontally." << std::endl;
			res = false;
		}
		else if (width > 80)
		{
			std::cout << "Invalid screen file '" << name << "': too large vertically." << std::endl;
			res = false;
		}
		else if (countPacman != 1)
		{
			std::cout << "Invalid screen file '" << name << "': does not contain just one Pac-Man." << std::endl;
			res = false;
		}
		else if (countGhosts > 4)
		{
			std::cout << "Invalid screen file '" << name << "': contains too many ghosts." << std::endl;
			res = false;
		}
		else if (countLegend != 1)
		{
			std::cout << "Invalid screen file '" << name << "': does not contain just one legend area." << std::endl;
			res = false;
		}
		else
			std::cout << "Screen file '" << name << "' is valid." << std::endl;
	}
	currFile.close();
	ConsoleApp::pauseScreen();
	ConsoleApp::clearScreen();
	return res;
}
bool Game::isLegendOnFirstLine(const string& string, int& width) const
{
	int i;
	for (i = 0; i < string.size(); i++)
		if (string[i] == valOf(boardConstants::LEGEND))
		{
			width = i;
			return true;
		}
	return false;
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
			if (str[0] != valOf(boardConstants::WALL) && str[tmpMaxWidth] != valOf(boardConstants::WALL))
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
		if (str[0] != valOf(boardConstants::WALL) && str[tmpMaxHeight] != valOf(boardConstants::WALL))
			_tunnels.second.push_back({ {x, 0}, {x, tmpMaxHeight} });
	}
}
// Methods
bool Game::Play(Pacman& pacman, vector<Ghost*>& ghosts, int& lives, int& score, bool colorAllowed) // Loop continue running until player wins, or loses
{
	int loopNumber = 0;
	bool playerQuits = false; // If player pauses game, then decides to quit by pressing 'q' or 'Q', he would get back to menu.
	while (pacman.getLives() > 0 && _board.getNumberOfBreadcrumbs() > 0 && playerQuits == false) // Unless the Pac-Man dies or it wins and gets all breadcrumbs
	{
		if (pacman.getFirstMove() == false) // Board, Pac-Man, the ghosts and the fruit are initially being printed. Game freezes until the player presses a key
		{
			// Prints board
			getBoard().Print(colorAllowed);
			pacman.Print(colorAllowed, valOf(colorConstants::YELLOW)); // Prints Pac-Man
			for (auto i = 0; i < ghosts.size(); i++)
				ghosts[i]->Print(colorAllowed, valOf(colorConstants::RED)); // Prints the ghosts
			if (getFruit().getVisibility() == true)
				getFruit().Print(colorAllowed, valOf(colorConstants::LIGHTMAGENTA)); // Prints the fruit
			while (!_kbhit())
				Print(pacman.getLives(), pacman.getScore(), colorAllowed); // Prints text
		}
		playerQuits = Move(pacman, ghosts, loopNumber, colorAllowed); // Updates the coordinator of Pac-Man, the ghosts and the fruit
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
				loopNumber = 0; // Resets ghosts' and fruit's movement
				Reset(pacman, ghosts); // Reduces Pac-Man's life and resets the game in case needed
			}
			if (_board.isBreadcrumb(pacman.getCoord().getX(), pacman.getCoord().getY()) == true)
			{
				_board.removeBreadcrumb(pacman.getCoord().getX(), pacman.getCoord().getY()); // Removes the breadcrumb itself
				_board.updateTotalBreadcrumbs(); // Decreases total breadcrumbs number
				pacman.updateScore(); // Increases Pac-Man's score
			}
			// Printing player's lives and score status every loop
			Print(pacman.getLives(), pacman.getScore(), colorAllowed);
		}
	}
	// End of loop -> means that the player has won or lost.
	ConsoleApp::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::WHITE));
	if (pacman.getLives() == 0) // Player loses if the function returns true. It returns true only if Pac-Man's lives are 0
	{
		std::cout << "YOU LOST!" << std::endl;
		ConsoleApp::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY() + 1);
		std::cout << "Better luck next time." << std::endl;
		Sleep(5 * valOf(gameConstants::GAME_SPEED));
		ConsoleApp::clearScreen();
		ConsoleApp::gotoxy(0, 0);
		std::cout << "YOU LOST!" << std::endl
			<< "Better luck next time." << std::endl;
		ConsoleApp::pauseScreen();
	}
	else if (_board.getNumberOfBreadcrumbs() == 0) // Player wins if the function returns true. It returns true only if Pac-Man's score is equal to 496
	{
		std::cout << "YOU WON!" << std::endl;
		ConsoleApp::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY() + 1);
		std::cout << "Congratulations." << std::endl;
		Sleep(5 * valOf(gameConstants::GAME_SPEED));
		ConsoleApp::clearScreen();
		ConsoleApp::gotoxy(0, 0);
		std::cout << "YOU WON!" << std::endl
			<< "Congratulations." << std::endl;
		ConsoleApp::pauseScreen();
	}
	else
	{
		std::cout << "YOU QUIT!" << std::endl;
		ConsoleApp::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY() + 1);
		std::cout << "Never give up." << std::endl;
		Sleep(5 * valOf(gameConstants::GAME_SPEED));
		ConsoleApp::clearScreen();
		ConsoleApp::gotoxy(0, 0);
		std::cout << "YOU QUIT!" << std::endl
			<< "Never give up." << std::endl;
		ConsoleApp::pauseScreen();
	}

	// Aftermath
	lives = pacman.getLives();
	score = pacman.getScore();
	return playerQuits;
}
bool Game::Move(Pacman& pacman, vector<Ghost*>& ghosts, int loopNumber, bool colorAllowed)
{
	// Fruit moves every four loops
	if (getFruit().getVisibility() == true && loopNumber % getFruit().getMovementFrequency() == 0)
	{
		if (loopNumber % valOf(fruitConstants::FRUIT_TIMER) == 0 && loopNumber > 0)
		{
			int x = getFruit().getCoord().getX(), y = getFruit().getCoord().getY();
			ConsoleApp::gotoxy(x, y);
			if (_board.isBreadcrumb(x, y))
			{
				if (colorAllowed == true)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::BROWN));
				std::cout << valOf(boardConstants::BREADCRUMB) << std::endl;
			}
			else
				std::cout << valOf(boardConstants::BLANK) << std::endl;
			_fruit.makeFruitInvisibile();
		}
		else
		{
			_fruit.eraseRender(colorAllowed, _board.isBreadcrumb(_fruit.getCoord().getX(), _fruit.getCoord().getY()), _fruit.getCoord());
			_fruit.Move(getTunnels(), _board, colorAllowed);
			_fruit.Print(colorAllowed, valOf(colorConstants::LIGHTMAGENTA));
		}
	}
	else if (getFruit().getVisibility() == false && loopNumber % (getFruit().getMovementFrequency() * valOf(fruitConstants::FRUIT_TIMER)) == 0)
	{
		_fruit.setStartingCoord(_board, getEntities());
		_fruit.Reset(_board, getEntities());
	}
	// Pac-Man moves every loop
	Point tmpCoord = pacman.getCoord();
	bool isQuit = pacman.Move(getTunnels(), _board, colorAllowed);
	pacman.eraseRender(colorAllowed, _board.isBreadcrumb(tmpCoord.getX(), tmpCoord.getY()), tmpCoord);
	pacman.Print(colorAllowed, valOf(colorConstants::YELLOW));
	// Ghosts move every two loops
	BestGhost* tmpBestGhost = nullptr;
	GoodGhost* tmpGoodGhost = nullptr;
	if (ghosts.size() > 0 && loopNumber % ghosts[0]->getMovementFrequency() == 0)
	{
		for (auto i = 0; i < ghosts.size(); i++)
		{
			tmpBestGhost = dynamic_cast<BestGhost*>(ghosts[i]);
			tmpGoodGhost = dynamic_cast<GoodGhost*>(ghosts[i]);
			ghosts[i]->eraseRender(colorAllowed, _board.isBreadcrumb(ghosts[i]->getCoord().getX(), ghosts[i]->getCoord().getY()), ghosts[i]->getCoord());
			ghosts[i]->Move(getTunnels(), _board, colorAllowed);
			if (tmpBestGhost != nullptr)
			{
				tmpBestGhost->setTargetCoord(pacman.getCoord());
				ghosts[i] = tmpBestGhost;
			}
			else if (tmpGoodGhost != nullptr)
			{
				tmpGoodGhost->setTargetCoord(pacman.getCoord());
				ghosts[i] = tmpGoodGhost;
			}
			ghosts[i]->Print(colorAllowed, valOf(colorConstants::RED));
		}
	}
	if (tmpBestGhost != nullptr || (tmpGoodGhost != nullptr && tmpGoodGhost->getIsBest() == true))
		Sleep(valOf(gameConstants::GAME_SPEED) / 2); // Multiplies game speed
	else
		Sleep(valOf(gameConstants::GAME_SPEED));
	return isQuit;
}
void Game::Print(int lives, int score, bool colorAllowed) // Function to display legend message
{
	ConsoleApp::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::WHITE));
	std::cout << "LIVES: " << lives << std::endl;
	ConsoleApp::gotoxy(getBoard().getLegend().getX(), getBoard().getLegend().getY() + 1);
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
		if (getEntities()[entityIndex].getY() != valOf(pointConstants::TRASH) && getEntities()[entityIndex].getX() != valOf(pointConstants::TRASH))
			ghosts[i]->Reset(getEntities()[entityIndex]);
	}
	// Fruit resetting
	_fruit.Reset(_board, getEntities());
	// Life status print resetting
	ConsoleApp::clearLegendArea(getBoard().getLegend());
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
		ConsoleApp::gotoxy(x, y);
		std::cout << valOf(boardConstants::BLANK) << std::endl;
		// Prints Pac-Man
		pacman.Print(colorAllowed, valOf(colorConstants::YELLOW));
		res = true;
	}
	// In case Pac-Man's coordinator is equal to fruit's coordinator
	x = pacman.getCoord().getX();
	y = pacman.getCoord().getY();
	if (res == false && getFruit().getCoord() == Point(x, y))
	{
		pacman.Print(colorAllowed, valOf(colorConstants::YELLOW));
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
			ConsoleApp::gotoxy(x, y);
			if (_board.isBreadcrumb(x, y))
			{
				if (colorAllowed == true)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::BROWN));
				std::cout << valOf(boardConstants::BREADCRUMB) << std::endl;
			}
			else
				std::cout << valOf(boardConstants::BLANK) << std::endl;
			// Prints ghosts
			ghosts[i]->Print(colorAllowed, valOf(colorConstants::RED));
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
			ghosts[i]->Print(colorAllowed, valOf(colorConstants::RED));
			res = true;
		}
	}
	if (res == true)
		x = y = 0;
	return res;
}