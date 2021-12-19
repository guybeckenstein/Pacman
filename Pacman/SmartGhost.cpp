#include "SmartGhost.h"
#include <math.h>

std::queue<int> SmartGhost::createRouteGhost(int x, int y, const Board& board, int direction)
{
	std::queue<int> route;
	if (Point(x, y) == _target)
	{
		route.push(direction);
		return route;
	}
	else
	{
		int i, tmpIndex = -1;
		double distanceArray[TOTAL_DIRECTIONS], shortestDistance = 0;
		if (board.isWall(x, y - 1) == true)
			distanceArray[valOf(pointConstants::UP)] = -1;
		else
			distanceArray[valOf(pointConstants::UP)] = getDistanceFromTarget(x, y - 1);
		if (board.isWall(x, y - 1) == true)
			distanceArray[valOf(pointConstants::LEFT)] = -1;
		else
			distanceArray[valOf(pointConstants::LEFT)] = getDistanceFromTarget(x - 1, y);
		if (board.isWall(x, y - 1) == true)
			distanceArray[valOf(pointConstants::DOWN)] = -1;
		else
			distanceArray[valOf(pointConstants::DOWN)] = getDistanceFromTarget(x, y + 1);
		if (board.isWall(x, y - 1) == true)
			distanceArray[valOf(pointConstants::RIGHT)] = -1;
		else
			distanceArray[valOf(pointConstants::RIGHT)] = getDistanceFromTarget(x + 1, y);
		for (i = 0; i < TOTAL_DIRECTIONS; i++)
		{
			if (tmpIndex == -1)
			{
				if (distanceArray[0] == -1)
				{
					if (distanceArray[1] == -1)
					{
						if (distanceArray[2] == -1)
							tmpIndex = 3;
						else
							tmpIndex = 2;
						break;
					}
				}
			}
		}
		return route;
	}
}