#include "Menu.h"
#include "BestGhost.h"
#include "ConsoleApp.h"
#include "Game.h"
#include "GoodGhost.h"
#include "NoviceGhost.h"
#include "Pacman.h"

const char* CLEARSCREEN = "                    ";

void Menu::Run() // Initializes and runs the game completely
{
	char choice = mainMenu(); // Prints menu
	bool exitGame = false;
	while (exitGame == false)
	{
		if (choice == 1)
			Load();
		else if (choice == 2)
			setColorSettings(colorScreen(getColorSettings())); // Sets the new color settings of Game class by calling Menu class' colorSettings function. This function gets a boolean value from the current Game class colorSettings getter
		else if (choice == 8)
			Instructions();
		else if (choice == 9)
			exitGame = true;
		if (exitGame == false)
		{
			ConsoleApp::clearScreen();
			choice = mainMenu();
		}
	}
}
// Prints the first main menu of the game. This menu appears after first initialization, after exiting Pac-Man's game and after picking the color settings or the instructions
int Menu::mainMenu()
{
	std::cout << "(1) Start a new game" << std::endl
		<< "(2) Add or remove color" << std::endl
		<< "(8) Present instructions and keys"
		<< std::endl <<
		"(9) EXIT"
		<< std::endl;
	char choice = _getch();
	while (choice != '1' && choice != '2' && choice != '8' && choice != '9')
	{
		ConsoleApp::gotoxy(0, 3);
		std::cout << std::endl << std::endl << "Wrong number, choose one of the numbers above.";
		ConsoleApp::gotoxy(0, 2);
		choice = _getch();
	}
	return choice - '0';
}
// Displays file loading menu. It is possible able to pick game difficulty level (default difficulty level is begginer = 1)
void Menu::Load()
{
	ConsoleApp::clearScreen();
	std::cout << "You can choose whether you will select a screen to load, or all three screens will load automatically" << std::endl
		<< "(1) Load screens automatically" << std::endl
		<< "(2) Select a screen to load" << std::endl
		<< "(8) Choose a difficulty level for the game" << std::endl
		<< "(9) EXIT" << std::endl;

	char choice = _getch();
	int difficultyLevel = 1;
	while (choice != '1' && choice != '2' && choice != '9')
	{
		if (choice == '8')
		{
			difficultyLevel = getDifficultyLevel();
			ConsoleApp::clearScreen();
			std::cout << "You can choose whether you will select a screen to load, or all three screens will load automatically" << std::endl
				<< "(1) Load screens automatically" << std::endl
				<< "(2) Select a screen to load" << std::endl
				<< "(8) Choose a difficulty level for the game" << std::endl
				<< "(9) EXIT" << std::endl;
		}
		else
		{
			ConsoleApp::gotoxy(0, 6);
			std::cout << "Wrong number, choose the numbers above.";
			ConsoleApp::gotoxy(0, 5);
		}
		choice = _getch();
	}
	if (choice == '1')
		loadScreensAutomatically(valOf(pointConstants::TRASH), difficultyLevel);
	else if (choice == '2')
		loadScreenByName(difficultyLevel);
	else
		ConsoleApp::pauseScreen();
}
// Returns the difficulty level that the user has picked
int Menu::getDifficultyLevel()
{
	ConsoleApp::clearScreen();
	std::cout << "You can choose the difficulty level of the game. Default is begginer level" << std::endl
		<< "If you finish game, you will need to change game difficulty level again to play in better levels" << std::endl
		<< "(1) Begginer - Novice Ghosts" << std::endl
		<< "(2) Semi-Pro - Good Ghosts" << std::endl
		<< "(3) Legendary - Best Ghosts" << std::endl;

	char choice = _getch();
	while (choice != '1' && choice != '2' && choice != '3')
	{
		ConsoleApp::gotoxy(0, 6);
		std::cout << "Wrong number, choose the numbers above.";
		ConsoleApp::gotoxy(0, 5);
		choice = _getch();
	}
	ConsoleApp::gotoxy(0, 8);
	std::cout << "Initializing game difficulty level..." << std::endl;
	ConsoleApp::pauseScreen();
	return choice - '0';
}
// First, a Pac-Man's screen is loaded by user's choice, then the other screens are loaded (only screens which are lexicographically bigger than the first one)
void Menu::loadScreenByName(int difficultyLevel)
{
	ConsoleApp::clearScreen();
	int screenIndex;
	string name;
	std::cout << "Enter screen name" << std::endl;
	getline(std::cin, name);
	if (isNameExist(name, screenIndex) == true)
		loadScreensAutomatically(screenIndex, difficultyLevel);
	else
	{
		std::cout << "Screen name does not exist." << std::endl;
		ConsoleApp::pauseScreen();
	}
}
void Menu::loadScreensAutomatically(int screenIndex, int difficultyLevel)
{
	bool isWin = true, isValidScreen = false, isQuit = false;
	int properScreens = 0;
	int numOfGhosts = 0, lives = valOf(pacmanConstants::INIT_LIVES), score = valOf(pacmanConstants::INIT_SCORE);
	size_t size = getScreenNames().size();
	if (screenIndex != valOf(pointConstants::TRASH))
	{
		Game screen(getScreenNames()[screenIndex], getColorSettings(), isValidScreen);
		if (isValidScreen == true)
		{
			Pacman pacman = Pacman(valOf(pacmanConstants::MOVEMENT_FREQUENCY), screen.getEntities()[0].getX(), screen.getEntities()[0].getY(), lives, score);
			vector<Ghost*> ghosts(0);
			if (screen.getEntities().size() > 1)
			{
				ghosts.reserve(valOf(ghostConstants::MAX_GHOSTS));
				for (int j = 1; j < screen.getEntities().size(); j++)
					if (screen.getEntities()[j].getX() != valOf(pointConstants::TRASH) && screen.getEntities()[j].getY() != valOf(pointConstants::TRASH))
					{
						if (difficultyLevel == 1)
							ghosts.push_back(new NoviceGhost{ screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), valOf(ghostConstants::MOVEMENT_FREQUENCY) });
						else if (difficultyLevel == 2)
							ghosts.push_back(new GoodGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), valOf(ghostConstants::MOVEMENT_FREQUENCY) });
						else
							ghosts.push_back(new BestGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), valOf(ghostConstants::MOVEMENT_FREQUENCY) });
					}
				ghosts.resize(ghosts.size());
			}
			isQuit = screen.Play(pacman, ghosts, lives, score, getColorSettings());
			if (lives == 0)
				isWin = false;
			properScreens++;
			for (auto i = 0; i < ghosts.size(); i++)
				delete[] ghosts[i];
		}
	}
	else
	{
		for (int i = 0; isQuit == false && isWin == true && i < size; i++)
		{
			Game screen(getScreenNames()[i], getColorSettings(), isValidScreen);
			if (isValidScreen == true)
			{
				Pacman pacman = Pacman(valOf(pacmanConstants::MOVEMENT_FREQUENCY), screen.getEntities()[0].getX(), screen.getEntities()[0].getY(), lives, score);
				vector<Ghost*> ghosts(0);
				if (screen.getEntities().size() > 1)
				{
					ghosts.reserve(valOf(ghostConstants::MAX_GHOSTS));
					for (int j = 1; j < screen.getEntities().size(); j++)
						if (screen.getEntities()[j].getX() != valOf(pointConstants::TRASH) && screen.getEntities()[j].getY() != valOf(pointConstants::TRASH))
						{
							if (difficultyLevel == 1)
								ghosts.push_back(new NoviceGhost{ screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), valOf(ghostConstants::MOVEMENT_FREQUENCY) });
							else if (difficultyLevel == 2)
								ghosts.push_back(new GoodGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), valOf(ghostConstants::MOVEMENT_FREQUENCY) });
							else
								ghosts.push_back(new BestGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), valOf(ghostConstants::MOVEMENT_FREQUENCY) });
						}
					ghosts.resize(ghosts.size());
				}
				isQuit = screen.Play(pacman, ghosts, lives, score, getColorSettings());
				if (lives == 0)
					isWin = false;
				properScreens++;
				for (auto k = 0; k < ghosts.size(); k++)
					delete[] ghosts[k];
			}
		}
	}
	Results(properScreens, screenIndex, isWin, isQuit, score);
}
void Menu::Results(int properScreens, int screenIndex, bool isWin, bool isQuit, int score)
{
	ConsoleApp::clearScreen();
	if (properScreens > 0)
	{
		if (screenIndex != valOf(pointConstants::TRASH))
		{
			if (isWin == true)
				if (isQuit == false)
					std::cout << "You won a single screen!" << std::endl
					<< "Now it is time for you to complete all screens in a row." << std::endl;
				else
					std::cout << "An excuse is the most expensive brand of self defeat you will ever purchase." << std::endl
					<< "You just started your Pac-Man process, you are giving up on a tremendous experience." << std::endl;
			else
				std::cout << "You lost at the first screen... But remember:" << std::endl
				<< "Sometimes you must lose everything to gain it again," << std::endl
				<< "and the regaining is the sweeter for the pain of loss." << std::endl;
		}
		else
		{
			if (isWin == true)
				if (isQuit == false)
					std::cout << "Congratulations for winning the challenging Pac-Man game!" << std::endl
					<< "Your triumph will ring through the history of MTA College." << std::endl;
				else
					std::cout << "An excuse is the most expensive brand of self defeat you will ever purchase." << std::endl
					<< "If you quit on the process, you are quitting on the result." << std::endl
					<< "And remember for life - quitting is never an option." << std::endl;
			else
				std::cout << "You lost... But remember:" << std::endl
				<< "Sometimes you must lose everything to gain it again," << std::endl
				<< "and the regaining is the sweeter for the pain of loss." << std::endl;
		}
	}
	else
	{
		if (screenIndex == 0)
			std::cout << "All screens are invalid." << std::endl;
		else
			std::cout << "Selected screen is invalid." << std::endl;
		std::cout << "Could not play." << std::endl;
	}
	std::cout << std::endl << "FINAL SCORE: " << score << " POINTS." << std::endl << std::endl;
	ConsoleApp::pauseScreen();
}
bool Menu::isNameExist(const string& name, int& index)
{
	int i; 
	size_t size = getScreenNames().size();
	for (i = 0; i < size; i++)
	{
		string nameWithDirectory = "Screens\\" + name;
		if (name == getScreenNames()[i] || (name + ".screen") == getScreenNames()[i])
		{
			index = i;
			return true;
		}
		else if (nameWithDirectory == getScreenNames()[i] || (nameWithDirectory + ".screen") == getScreenNames()[i])
		{
			index = i;
			return true;
		}
	}
	return false;
}
void Menu::Instructions() // Informs the player what the rules are
{
	ConsoleApp::clearScreen();
	std::cout << "The player controls Pac-Man ('@'), who must eat all the breadcrumbs dots ('.') inside an enclosed maze." << std::endl <<
		"The player must avoid all ghosts ('$')." << std::endl << std::endl
		<< "Game controls in the game are below:" << std::endl
		<< "W - go UP." << std::endl << "A - go LEFT." << std::endl << "D - go RIGHT." << std::endl << "X - go DOWN." << std::endl
		<< "S - STAY in current position." << std::endl
		<< "If you want to PAUSE game during playing, press ESC for PAUSE." << std::endl
		<< "If you have changed your desired color, you can pick a new color again, through pressing (2) in menu." << std::endl << std::endl;
	ConsoleApp::pauseScreen();
}
// Operators
const Menu& Menu::operator=(const Menu& menu)
{
	if (this != &menu)
	{
		setColorSettings(menu._colorAllowed);
		_screenNames.clear();
		_screenNames = menu._screenNames;
	}
	return *this;
}
// Bonus Methods
bool Menu::colorScreen(bool isColorAllowed) // This function changes color settings of the game, if player decides to change it.
{
	ConsoleApp::clearScreen();
	bool newColorSettings;
	if (isColorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::WHITE));
	std::cout << "You can choose whether you will play in a colorful mode or not" << std::endl
		<< "(0) Non-color mode" << std::endl
		<< "(1) Color mode" << std::endl;

	char choice = _getch();
	while (choice != '0' && choice != '1')
	{
		ConsoleApp::gotoxy(0, 4);
		std::cout << "Wrong number, choose the numbers above.";
		ConsoleApp::gotoxy(0, 3);
		choice = _getch();
	}
	ConsoleApp::gotoxy(0, 6);
	if (choice == '0')
	{
		newColorSettings = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::LIGHTGREY));
		std::cout << "Initializing non-color mode..." << std::endl;
	}
	else
	{
		newColorSettings = true;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), valOf(colorConstants::WHITE));
		std::cout << "Initializing color mode..." << std::endl;
	}
	ConsoleApp::pauseScreen();
	return newColorSettings;
}