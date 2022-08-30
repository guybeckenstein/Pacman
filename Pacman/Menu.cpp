<<<<<<< HEAD
#include "Menu.h"
=======
#include <filesystem>
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
#include "BestGhost.h"
#include "ConsoleApp.h"
#include "Game.h"
#include "GoodGhost.h"
#include "NoviceGhost.h"

// Constants
constexpr int START_CHOICE = 1, SET_COLOR_CHOICE = 2, INSTRUCTIONS_CHOICE = 8, EXIT_GAME_CHOICE = 9; // Initial menu constants
constexpr char ONE = '1', TWO = '2', THREE = '3', EIGHT = '8', NINE = '9'; // Numbers constants
constexpr int NOVICE_GHOST = 1, GOOD_GHOST = 2; // Ghosts constants

// Initializes and runs the game completely
void Menu::Run(bool saveMode, bool loadMode, bool silentMode)
{
	if (loadMode == false && silentMode == false)
	{
		char choice = mainMenu(); // Prints menu
		bool exitGame = false;
		while (exitGame == false)
		{
<<<<<<< HEAD
			ConsoleApp::clearScreen();
			choice = mainMenu();
=======
			if (choice == START_CHOICE)
				Start(saveMode);
			else if (choice == SET_COLOR_CHOICE)
				setColorSettings(colorScreen(getColorSettings())); // Sets the new color settings of Game class by calling Menu class' colorSettings function. This function gets a boolean value from the current Game class colorSettings getter
			else if (choice == INSTRUCTIONS_CHOICE)
				Instructions();
			else if (choice == EXIT_GAME_CHOICE)
				exitGame = true;
			if (exitGame == false)
			{
				clearScreen();
				choice = mainMenu();
			}
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
		}
	}
	else
		loadScreensLoadMode(silentMode);
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
	while (choice != ONE && choice != TWO && choice != EIGHT && choice != NINE)
	{
		ConsoleApp::gotoxy(0, 3);
		std::cout << std::endl << std::endl << "Wrong number, choose one of the numbers above.";
		ConsoleApp::gotoxy(0, 2);
		choice = _getch();
	}
	return choice - '0';
}
// Displays file loading menu. It is possible able to pick game difficulty level (default difficulty level is begginer = 1)
void Menu::Start(bool saveMode)
{
	ConsoleApp::clearScreen();
	std::cout << "You can choose whether you will select a screen to load, or all three screens will load automatically" << std::endl
		<< "(1) Load screens automatically" << std::endl;
	if (saveMode == false)
		std::cout << "(2) Select a screen to load" << std::endl;
	std:: cout << "(8) Choose a difficulty level for the game" << std::endl
		<< "(9) EXIT" << std::endl;

	char choice = _getch();
	int difficultyLevel = 1;
	if (saveMode == true)
	{
		while (choice != ONE && choice != NINE)
		{
<<<<<<< HEAD
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
=======
			if (choice == EIGHT)
			{
				difficultyLevel = getDifficultyLevel();
				clearScreen();
				std::cout << "You can choose whether you will select a screen to load, or all three screens will load automatically" << std::endl
					<< "(1) Load screens automatically" << std::endl
					<< "(8) Choose a difficulty level for the game" << std::endl
					<< "(9) EXIT" << std::endl;
			}
			else
			{
				gotoxy(0, 5);
				std::cout << "Wrong number, choose the numbers above.";
				gotoxy(0, 4);
			}
			choice = _getch();
		}
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
	}
	else
	{
		while (choice != ONE && choice != TWO && choice != NINE)
		{
			if (choice == EIGHT)
			{
				difficultyLevel = getDifficultyLevel();
				clearScreen();
				std::cout << "You can choose whether you will select a screen to load, or all three screens will load automatically" << std::endl
					<< "(1) Load screens automatically" << std::endl
					<< "(2) Select a screen to load" << std::endl
					<< "(8) Choose a difficulty level for the game" << std::endl
					<< "(9) EXIT" << std::endl;
			}
			else
			{
				gotoxy(0, 6);
				std::cout << "Wrong number, choose the numbers above.";
				gotoxy(0, 5);
			}
			choice = _getch();
		}
	}
	if (choice == ONE)
		loadScreensAutomatically(saveMode, static_cast<int>(Directions::TRASH), difficultyLevel);
	else if (choice == TWO)
		loadScreenByName(saveMode, difficultyLevel);
	else
<<<<<<< HEAD
		ConsoleApp::pauseScreen();
=======
		pauseScreen();

>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
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
	while (choice != ONE && choice != TWO && choice != THREE)
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
// Ex2
// First, a Pac-Man's screen is loaded by user's choice, then the other screens are loaded (only screens which are lexicographically bigger than the first one)
void Menu::loadScreenByName(bool saveMode, int difficultyLevel)
{
	ConsoleApp::clearScreen();
	int screenIndex;
	string name;
	std::cout << "Enter screen name" << std::endl;
	getline(std::cin, name);
	if (isNameExist(name, screenIndex) == true)
		loadScreensAutomatically(saveMode, screenIndex, difficultyLevel);
	else
	{
		std::cout << "Screen name does not exist." << std::endl;
		ConsoleApp::pauseScreen();
	}
}
void Menu::loadScreensAutomatically(bool saveMode, int screenIndex, int difficultyLevel)
{
	bool isWin = true, isValidScreen = false, isQuit = false;
	int properScreens = 0;
	int lives = static_cast<int>(pacmanConstants::INIT_LIVES), score = static_cast<int>(pacmanConstants::INIT_SCORE);
	// Ex2
	if (screenIndex != static_cast<int>(Directions::TRASH))
	{
		Game screen(getScreenNames()[screenIndex], getColorSettings(), isValidScreen);
		if (isValidScreen == true)
		{
			Pacman pacman = Pacman(static_cast<int>(pacmanConstants::MOVEMENT_FREQUENCY), screen.getEntities()[0].getX(), screen.getEntities()[0].getY(), lives, score);
			vector<Ghost*> ghosts(0);
			if (screen.getEntities().size() > 1)
			{
				ghosts.reserve(static_cast<int>(ghostConstants::MAX_GHOSTS));
				for (int j = 1; j < screen.getEntities().size(); j++)
					if (screen.getEntities()[j].getX() != static_cast<int>(Directions::TRASH) && screen.getEntities()[j].getY() != static_cast<int>(Directions::TRASH))
					{
						if (difficultyLevel == NOVICE_GHOST)
							ghosts.push_back(new NoviceGhost{ screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY) });
						else if (difficultyLevel == GOOD_GHOST)
							ghosts.push_back(new GoodGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY) });
						else
							ghosts.push_back(new BestGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY) });
					}
				ghosts.resize(ghosts.size());
			}
			try
			{
				isQuit = screen.PlayEx2Mode(getScreenNames()[screenIndex], false, pacman, ghosts, lives, score, getColorSettings());
			}
			catch (const string& stepsFile)
			{
				for (auto k = 0; k < ghosts.size(); k++)
					delete[] ghosts[k];
				std::cout << "Creating file '" << stepsFile << "' exception: steps file could not be created by the game." << std::endl;
			}
			catch (const char* resultFile)
			{
				for (auto k = 0; k < ghosts.size(); k++)
					delete[] ghosts[k];
				std::cout << "Creating file '" << resultFile << "' exception: result file could not be created by the game." << std::endl;
			}
			if (lives == 0)
				isWin = false;
			properScreens++;
			for (auto k = 0; k < ghosts.size(); k++)
				delete[] ghosts[k];
		}
	}
	else
	{
		// When picking -save, all pacman_*.steps and pacman_*.result files are being deleted
		if (saveMode == true)
		{
			for (auto const& cwd_entry : std::filesystem::directory_iterator{ "Screens" }) // The game would look for files in working directory->Screens
			{
				if (validName(cwd_entry.path().string(), "result") == true)
					remove(cwd_entry.path().string().c_str());
				if (validName(cwd_entry.path().string(), "steps") == true)
					remove(cwd_entry.path().string().c_str());
			}
		}
		size_t numOfScreenNames = getScreenNames().size();
		for (int i = 0; isQuit == false && isWin == true && i < numOfScreenNames; i++)
		{
			Game screen(getScreenNames()[i], getColorSettings(), isValidScreen);
			if (isValidScreen == true)
			{
				// Initializing entities
				Pacman pacman = Pacman(static_cast<int>(pacmanConstants::MOVEMENT_FREQUENCY), screen.getEntities()[0].getX(), screen.getEntities()[0].getY(), lives, score);
				vector<Ghost*> ghosts(0);
				if (screen.getEntities().size() > 1)
				{
					ghosts.reserve(static_cast<int>(ghostConstants::MAX_GHOSTS));
					for (int j = 1; j < screen.getEntities().size(); j++)
						if (screen.getEntities()[j].getX() != static_cast<int>(Directions::TRASH) && screen.getEntities()[j].getY() != static_cast<int>(Directions::TRASH))
						{
							if (difficultyLevel == NOVICE_GHOST)
								ghosts.push_back(new NoviceGhost{ screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY) });
							else if (difficultyLevel == GOOD_GHOST)
								ghosts.push_back(new GoodGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY) });
							else
								ghosts.push_back(new BestGhost{ screen.getEntities()[0], screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY) });
						}
					ghosts.resize(ghosts.size());
				}
				// Initializing game
				isQuit = screen.PlayEx2Mode(getScreenNames()[i], saveMode, pacman, ghosts, lives, score, getColorSettings());
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
void Menu::loadScreensLoadMode(bool silentMode)
{
	bool isValidScreen = false, isValidResults = true;
	int lives = static_cast<int>(pacmanConstants::INIT_LIVES), score = static_cast<int>(pacmanConstants::INIT_SCORE);
	size_t numOfScreenNames = getScreenNames().size();
	for (int i = 0; isValidResults == true && i < numOfScreenNames && lives > 0; i++)
	{
		Game screen(getScreenNames()[i], getColorSettings(), isValidScreen);
		if (isValidScreen == true)
		{
			// Initializing entities
			Pacman pacman = Pacman(static_cast<int>(pacmanConstants::MOVEMENT_FREQUENCY), screen.getEntities()[0].getX(), screen.getEntities()[0].getY(), lives, score);
			vector<Ghost*> ghosts(0);
			if (screen.getEntities().size() > 1)
			{
				ghosts.reserve(static_cast<int>(ghostConstants::MAX_GHOSTS));
				for (int j = 1; j < screen.getEntities().size(); j++)
					if (screen.getEntities()[j].getX() != static_cast<int>(Directions::TRASH) && screen.getEntities()[j].getY() != static_cast<int>(Directions::TRASH))
						ghosts.push_back(new NoviceGhost{ screen.getEntities()[j].getX(), screen.getEntities()[j].getY(), static_cast<int>(ghostConstants::MOVEMENT_FREQUENCY) });
				ghosts.resize(ghosts.size());
			}
			// Initializing game
			try
			{
				isValidResults = screen.playLoadMode(getScreenNames()[i], silentMode, pacman, ghosts, lives, score, getColorSettings());
			}
			catch (const string& stepsFile)
			{
				for (auto k = 0; k < ghosts.size(); k++) // Deleting allocated new ghosts
					delete[] ghosts[k];
				std::cout << "Invalid steps file '" << stepsFile << "': could not be opened by the game." << std::endl;
			}
			catch (const char* resultFile)
			{
				for (auto k = 0; k < ghosts.size(); k++) // Deleting allocated new ghosts
					delete[] ghosts[k];
				std::cout << "Invalid result file '" << resultFile << "': could not be opened by the game." << std::endl;
			}
			for (auto k = 0; k < ghosts.size(); k++) // Deleting allocated new ghosts
				delete[] ghosts[k];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::LIGHTGREY));
		}
	}
	clearScreen();
	if (isValidResults == true)
		std::cout << "The result files and steps created by the game (during save mode) work properly." << std::endl;
	else
		std::cout << "The result files and steps created by the game (during save mode) do not work properly." << std::endl;
}
void Menu::Results(int properScreens, int screenIndex, bool isWin, bool isQuit, int score)
{
	ConsoleApp::clearScreen();
	if (properScreens > 0)
	{
		if (screenIndex != static_cast<int>(Directions::TRASH))
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
<<<<<<< HEAD
	ConsoleApp::pauseScreen();
=======
	pauseScreen();
}
void Menu::pauseGame(const Point& legend, bool colorAllowed) // Player pressed "ESC" button -> game paused. If player will press "ESC" again, game will continue
{
	gotoxy(legend.getX(), legend.getY());
	if (colorAllowed == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::WHITE));
	std::cout << "Game paused, pressin" << std::endl;
	gotoxy(legend.getX(), legend.getY() + 1);
	std::cout << "ESC again = continue" << std::endl;
	char key = 0;
	while (key != static_cast<int>(gameConstants::ESC))
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == static_cast<int>(gameConstants::ESC))
			{
				clearLegendArea(legend);
				continue;
			}
		}
	}
}
void Menu::clearLegendArea(const Point& legend)
{
	gotoxy(legend.getX(), legend.getY());
	for (auto i = 0; i < static_cast<int>(boardConstants::LEGEND_MAX_HEIGHT); i++)
	{
		for (auto j = 0; j < static_cast<int>(boardConstants::LEGEND_MAX_WIDTH); j++)
			std::cout << " ";
		std::cout << std::endl;
		gotoxy(legend.getX(), legend.getY() + i);
	}
>>>>>>> f3a2e9a97bb00a5af3d781ff1083155583228d28
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::WHITE));
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::LIGHTGREY));
		std::cout << "Initializing non-color mode..." << std::endl;
	}
	else
	{
		newColorSettings = true;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(colorConstants::WHITE));
		std::cout << "Initializing color mode..." << std::endl;
	}
	ConsoleApp::pauseScreen();
	return newColorSettings;
}
// Compares the current file name to the format we are needed to work with
// The game would look for files in the working directory, with the names pacman_*.screen
bool Menu::validName(const string& name, const string& type)
{
	if (name.compare(strlen("Screens\\"), 7, "pacman_") == 0)
	{
		string part;
		for (size_t i = strlen("Screens\\") + strlen("pacman_"); name[i] != '.'; i++)
			part.push_back(name[i]);
		if (name.compare(strlen("Screens\\") + strlen("pacman_"), part.size() + 1 + type.size(), part + "." + type) == 0)
			return true;
	}
	return false;
}