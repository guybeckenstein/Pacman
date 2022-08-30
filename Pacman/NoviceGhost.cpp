#include "NoviceGhost.h"

// Methods
void NoviceGhost::Reset(const Point& coord)
{
	resetMovement();
	_coord = coord;
}
