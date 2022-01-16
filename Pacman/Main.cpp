#include <filesystem>
#include <fstream>
#include "Game.h"
#include "InputParser.h"
#include "Menu.h"

// Compares the current file name to the format we are needed to work with.
// The game would look for files in the working directory, with the names 'pacman_*.screen'.
// If there are files of this type, the game would look for files in the working directory, with the names 'pacman_*.result' and 'pacman_*.steps'.
// Game only runs in load/silently load mode if the amount of 'pacman_*.result' and 'pacman_*.steps' is equal to 'pacman_*.screen'.

int main(int argc, char* argv[])
{
    Menu::clearScreen();
    int numOfResult = 0, numOfScreens = 0, numOfSteps = 0;
    vector<string> screenNames;

    for (auto const& cwd_entry : std::filesystem::directory_iterator{ "Screens" }) // The game would look for files in working directory->Screens
    {
        if (Menu::validName(cwd_entry.path().string(), "screen") == true)
        {
            screenNames.push_back(cwd_entry.path().string());
            numOfScreens++;
        }
    }
    std::sort(screenNames.begin(), screenNames.end()); // Sorting files in lexicographical order as requested
    // All files existance check
    for (auto const& cwd_entry : std::filesystem::directory_iterator{ "Screens" }) // The game would look for files in working directory->Screens
    {
        if (Menu::validName(cwd_entry.path().string(), "result") == true)
            numOfResult++;
        if (Menu::validName(cwd_entry.path().string(), "steps") == true)
            numOfSteps++;
    }
    if (numOfScreens > 0)
    {
        InputParser input(argc, argv);
        const string save = input.getCmdOption("-save"), load = input.getCmdOption("-load"), silent = input.getCmdOption("-silent");
        Menu initialize(screenNames);
        // If the input includes '-load'"
        if (load.compare("-load") == 0)
            if (numOfResult != numOfScreens || numOfSteps != numOfScreens)
                std::cout << "Could not find enough appropriate files with the names pacman_*.result or pacman_*.steps," << std::endl
                << "hence the game could not be played." << std::endl;
            else if (silent.compare("-silent") == 0)
                initialize.Run(true, true, true);
            else
                initialize.Run(true, true, false);
        // If the input is one of these: "(1) '-save -silent' (2) '-silent -save' (3) '-silent'"
        else if (silent.compare("-silent") == 0)
            std::cout << "Invalid command line parameters combination. The silent option is relevant only for load, hence the game could not be played." << std::endl
                << "Valid arguments are:" << std::endl
                << "(1) Blank argument" << std::endl
                << "(2) -save" << std::endl
                << "(3) -load" << std::endl
                << "(4) -load -silent" << std::endl;
        // If the input is '-save'"
        else if (save.compare("-save") == 0)
            initialize.Run(true, false, false);
        // If there's no input
        else
            initialize.Run(false, false, false);
    }
    else
        std::cout << "Could not find any appropriate files with the names pacman_*.screen, hence the game could not be played." << std::endl;
	return 0;
}