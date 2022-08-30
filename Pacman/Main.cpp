#include <filesystem>
#include <fstream>
#include "Game.h"
#include "Menu.h"

// Compares the current file name to the format we are needed to work with
 // The game would look for files in the working directory, with the names pacman_*.screen
bool validName(string name);

int main()
{
	int numOfScreens = 0;
	vector<string> screenNames;

	for (auto const& cwd_entry : std::filesystem::directory_iterator{ "Screens" }) // The game would look for files in the working directory, which is "Screens" folder
	{
		if (validName(cwd_entry.path().string()) == true)
		{
			screenNames.push_back(cwd_entry.path().string());
			numOfScreens++;
		}
	}
	std::sort(screenNames.begin(), screenNames.end()); // Sorting files in lexicographical order as requested
	if (numOfScreens > 0)
	{
		Menu initialize(screenNames);
		initialize.Run();
	}
	else
		std::cout << "Could not find any appropriate files with the names pacman_*.screen, hence the game could not be played." << std::endl;
	return 0;
}
bool validName(string name)
{
	if (name.compare(strlen("Screens\\"), 7, "pacman_") == 0)
	{
		string part;
		for (size_t i = strlen("Screens\\") + strlen("pacman_"); name[i] != '.'; i++)
			part.push_back(name[i]);
		if (name.compare(strlen("Screens\\") + strlen("pacman_"), part.size() + strlen(".screen"), part + ".screen") == 0)
			return true;
	}
	return false;
}