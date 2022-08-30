#include "Pacman.h"
#include "Game.h"
#include "Menu.h"
#include "ConsoleApp.h"

// Setters
void Pacman::setPacman(const Point& coord, const pair<Tunnel, Tunnel>& tunnels) // Used every move, when we seek to update Pac-Man's coordinator (also when he goes through the tunnels)
{
	int i;
	bool isTunnel = false;
	// Vertical tunnels
	for (i = 0; isTunnel == false && i < tunnels.first.size(); i++)
	{
		if (coord == Point(tunnels.first[i].first.getX() - 1, tunnels.first[i].first.getY()))
		{
			_coord = tunnels.first[i].second;
			isTunnel = true;
		}
		else if (coord == Point(tunnels.first[i].second.getX() + 1, tunnels.first[i].first.getY()))
		{
			_coord = tunnels.first[i].first;
			isTunnel = true;
		}
	}
	// Horizontal tunnels
	for (i = 0; isTunnel == false && i < tunnels.second.size(); i++)
	{
		if (coord == Point(tunnels.second[i].first.getX(), tunnels.second[i].first.getY() - 1))
		{
			_coord = tunnels.second[i].second;
			isTunnel = true;
		}
		else if (coord == Point(tunnels.second[i].second.getX(), tunnels.second[i].second.getY() + 1))
		{
			_coord = tunnels.second[i].first;
			isTunnel = true;
		}
	}
	if (isTunnel == false)
		_coord = coord;
}
// Methods
bool Pacman::Move(const pair<Tunnel, Tunnel>& tunnels, const Board& board, bool colorAllowed) // Updates Pac-Man's move. Pac-Man would not move if the player pressed STAY button, or did not choose any legal directions after hitting the wall. Returns true if player decides to quit
{
	static int nextDirection = valOf(pointConstants::TRASH); // nextDirection is used to "remember" the user's next direction, when a wall does not appear anymore
	static bool isWallPrev, isWallCurr;
	bool nextToTunnel;
	char key = getArrowKeys(board, colorAllowed);
	if (getDirection() >= valOf(pointConstants::UP) || getFirstMove() == true)
	{
		Point pointToUpdate(0, 0);
		if (isWallPrev == false)
			isWallPrev = getNextDirection(tunnels, board, key, nextDirection, nextToTunnel);
		else
			isWallCurr = getNextDirection(tunnels, board, key, nextDirection, nextToTunnel);
		pointToUpdate = getCoord();
		if (isWallPrev == true && getDirection() != nextDirection)
		{
			if (isWallCurr == true)
				pointToUpdate.updateCoord(getDirection());
			else
			{
				pointToUpdate.updateCoord(nextDirection);
				isWallPrev = false;
			}
		}
		else
		{
			int x = getCoord().getX(), y = getCoord().getY();
			if (nextToTunnel == true || !((getDirection() == valOf(pointConstants::UP)) && (board.isWall(x, y - 1) == true)) && !((getDirection() == valOf(pointConstants::DOWN)) && (board.isWall(x, y + 1) == true)) && !((getDirection() == valOf(pointConstants::LEFT)) && (board.isWall(x - 1, y) == true)) && !((getDirection() == valOf(pointConstants::RIGHT)) && (board.isWall(x + 1, y) == true)))
				pointToUpdate.updateCoord(getDirection());
			else
				setDirection(valOf(pointConstants::TRASH));
		}
		setPacman(pointToUpdate, tunnels);
	}
	if (getDirection() != valOf(gameConstants::QUIT))
		return false;
	else
	{
		nextDirection = valOf(pointConstants::TRASH);
		return true;
	}
}
char Pacman::getArrowKeys(const Board& board, bool colorAllowed) // Returns the key value of the button that the player pressed on keyboard
{
	static char key;
	if (_kbhit())
	{
		setFirstMove(true);
		key = _getch();
		if (key == valOf(gameConstants::ESC))
			ConsoleApp::pauseGame(board.getLegend(), colorAllowed);
	}
	return key;
}
bool Pacman::getNextDirection(const pair<Tunnel, Tunnel>& tunnels, const Board& board, char key, int& nextDirection, bool& nextToTunnel) // Returns the direction of the Pac-Man, depends whether there is a wall or not
{
	bool res = false;
	int x = getCoord().getX();
	int y = getCoord().getY();
	if (key == valOf(gameConstants::ESC))
		res = true;
	else if (key == 'w' || key == 'W')
	{
		if (y == 0 || board.isWall(x, y - 1) == true)
			res = true;
		else
		{
			res = false;
			setDirection(valOf(pointConstants::UP)); // Can go UP
			nextDirection = valOf(pointConstants::UP);
		}
	}
	else if (key == 'x' || key == 'X')
	{
		if (y == board.getHeight() - 1 || board.isWall(x, y + 1) == true)
			res = true;
		else
		{
			res = false;
			setDirection(valOf(pointConstants::DOWN)); // Can go DOWN
			nextDirection = valOf(pointConstants::DOWN);
		}
	}
	else if (key == 'a' || key == 'A')
	{
		if (x == 0 || board.isWall(x - 1, y) == true)
			res = true;
		else
		{
			res = false;
			setDirection(valOf(pointConstants::LEFT)); // Can go LEFT
			nextDirection = valOf(pointConstants::LEFT);
		}
	}
	else if (key == 'd' || key == 'D')
	{
		if (x == board.getWidth() - 1 || board.isWall(x + 1, y) == true)
			res = true;
		else
		{
			res = false;
			setDirection(valOf(pointConstants::RIGHT)); // Can go RIGHT
			nextDirection = valOf(pointConstants::RIGHT);
		}
	}
	else if (key == 's' || key == 'S')
	{
		res = false;
		setDirection(valOf(gameConstants::STAY)); // Can STAY
		nextDirection = valOf(gameConstants::STAY);
	}
	else if (key == 'q' || key == 'Q')
	{
		res = false;
		setDirection(valOf(gameConstants::QUIT)); // Can QUIT
		nextDirection = valOf(gameConstants::QUIT);
	}
	nextToTunnel = checkForTunnels(tunnels, board, key);
	if (nextToTunnel == true && (y == 0 || y == board.getHeight() - 1 || x == 0 || x == board.getWidth() - 1))
		res = true;
	else if (res == true && (y == 0 || y == board.getHeight() - 1 || x == 0 || x == board.getWidth() - 1))
		setDirection(valOf(gameConstants::STAY));
	else
		res = true;
	return res;
}
bool Pacman::checkForTunnels(const pair<Tunnel, Tunnel>& tunnels, const Board& board, char key)
{
	for (auto i = 0; key != 'w' && key != 'W' && key != 'x' && key != 'X' && i < tunnels.first.size(); i++)
	{
		if (getCoord() == tunnels.first[i].first || getCoord() == tunnels.first[i].second)
		{
			if (getDirection() == valOf(gameConstants::STAY) || getCoord().getX() == 0 || getCoord().getX() == board.getWidth() - 1)
			{
				if ((key == 'a' || key == 'A') && (getCoord().getX() == 0 || board.isWall(getCoord().getX() - 1, getCoord().getY()) == false))
					setDirection(valOf(pointConstants::LEFT)); // Can go LEFT
				else if ((key == 'd' || key == 'D') && (getCoord().getX() == board.getWidth() - 1 || board.isWall(getCoord().getX() + 1, getCoord().getY()) == false))
					setDirection(valOf(pointConstants::RIGHT)); // Can go RIGHT
				return true;
			}
			if (getDirection() != valOf(gameConstants::STAY))
			{
				if (getCoord() == tunnels.first[i].second && (key == 'a' || key == 'A') && board.isWall(getCoord().getX() + 1, getCoord().getY()) == true)
					setDirection(valOf(gameConstants::STAY)); // Can STAY
				else if (getCoord() == tunnels.first[i].first && (key == 'd' || key == 'D') && board.isWall(getCoord().getX() - 1, getCoord().getY()) == true)
					setDirection(valOf(gameConstants::STAY)); // Can STAY
				return true;
			}
		}
	}
	for (auto i = 0; key != 'a' && key != 'A' && key != 'd' && key != 'D' && i < tunnels.second.size(); i++)
	{
		if (getCoord() == tunnels.second[i].first || getCoord() == tunnels.second[i].second)
		{
			if (getDirection() == valOf(gameConstants::STAY) || getCoord().getY() == 0 || getCoord().getY() == board.getHeight() - 1)
			{
				if ((key == 'w' || key == 'W') && (getCoord().getY() == 0 || board.isWall(getCoord().getX(), getCoord().getY() - 1) == false))
					setDirection(valOf(pointConstants::UP)); // Can go UP
				else if ((key == 'x' || key == 'X') && (getCoord().getY() == board.getHeight() - 1 || board.isWall(getCoord().getX(), getCoord().getY() + 1) == false))
					setDirection(valOf(pointConstants::DOWN)); // Can go DOWN
				return true;
			}
			if (getDirection() != valOf(gameConstants::STAY))
			{
				if (getCoord() == tunnels.second[i].second && (key == 'w' || key == 'W') && board.isWall(getCoord().getX(), getCoord().getY() - 1) == true)
					setDirection(valOf(gameConstants::STAY)); // Can STAY
				else if (getCoord() == tunnels.second[i].first && (key == 'x' || key == 'X') && board.isWall(getCoord().getX(), getCoord().getY() + 1) == true)
					setDirection(valOf(gameConstants::STAY)); // Can STAY
				return true;
			}
		}
	}
	return false;
}
void Pacman::Reset(const Point& coord) // Used when resetting the game (when Pac-Man hits a ghost or when playing again)
{
	resetMovement();
	if (getLives() > 0)
		updateLife();
	_coord = coord;
}