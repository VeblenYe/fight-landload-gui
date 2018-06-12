#include "Poker.h"
#include "MouseDrag.h"
#include "common.h"
#include "Player.h"


bool operator<(const Poker &lhs, const Poker &rhs) {
	return lhs.nums < rhs.nums;
}


std::pair<int, int> Poker::handle(SDL_Event *e) {
	if (state == -1)
		return { 0, 0 };
	int handled = 0;

	// 鼠标拖动区域
	auto area = MouseDrag::instance().getDragArea();

	// 判断是否到达边界
	int in;
	in = (area.x >= getBox().x) ? 1 : 0;

	if(e->type == SDL_MOUSEBUTTONUP)
		if (hasIntersection(getBox(), area)) {
			if (state) {
				state = !state;
				setPos(getBox().x, getBox().y - 60);
				holder->addToTemp(this);
			}
			else {
				state = !state;
				setPos(getBox().x, getBox().y + 60);
				holder->removeFromTemp(this);
			}
			handled = 1;
		}
	
	return { handled, in };
}


void Poker::registered(int type) {
	if (!findEvent(type)) {
		addEvent(type);
		EventManager::instance().AddEventHandler(type, { handler });
	}
}


void Poker::unregister() {
	for (auto type : getEvents())
		EventManager::instance().RemoveEventHandler(type, { handler });
}
