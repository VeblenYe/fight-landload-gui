#include "Poker.h"
#include "MouseDrag.h"
#include "common.h"
#include <iostream>


bool operator<(const Poker &lhs, const Poker &rhs)
{
	return lhs.nums < rhs.nums;
}


std::pair<int, int> Poker::handle(SDL_Event *e) {
	int handled = 0;

	auto area = MouseDrag::instance().getDragArea();

	int in;
	if (area.x >= buttonBox.x)
		in = 1;
	else
		in = 0;

	if(e->type== SDL_MOUSEBUTTONUP)
		if (hasIntersection(&buttonBox, &area)) {
			state = !state;
			moveExtent = state * move;
			/*
			std::cout << "¸ÃÅÆ×ø±êÎª" << buttonBox.x << " " << buttonBox.y << " " << buttonBox.w << " "
				<< buttonBox.h << std::endl;
				*/
			handled = 1;
		}
		else {
			moveExtent = moveExtent;
		}
	
		return { handled, in };
}

