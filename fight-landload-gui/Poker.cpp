#include "Poker.h"
#include "MouseDrag.h"
#include "common.h"
#include "Player.h"
#include <iostream>


bool operator<(const Poker &lhs, const Poker &rhs) {
	return lhs.nums < rhs.nums;
}


std::pair<int, int> Poker::handle(SDL_Event *e) {
	int handled = 0;

	// ����϶�����
	auto area = MouseDrag::instance().getDragArea();

	// �ж��Ƿ񵽴�߽�
	int in;
	in = (area.x >= getBox().x) ? 1 : 0;

	if(e->type == SDL_MOUSEBUTTONUP)
		if (hasIntersection(getBox(), area)) {
			if (state) {
				state = !state;
				setPos(getBox().x, getBox().y + 60);
				holder->addToTemp(std::make_shared<Poker>(*this));
			}
			else {
				state = !state;
				setPos(getBox().x, getBox().y - 60);
				holder->removeFromTemp(std::make_shared<Poker>(*this));
			}

			std::cout << "����Ϊ" << nums << std::endl;
			handled = 1;
		}
	
	return { handled, in };
}
