#pragma once


#include <SDL.h>
#include "ClassEventHandler.h"
#include "EventManager.h"


class MouseDrag {
public:
	MouseDrag(const MouseDrag &) = delete;

	static MouseDrag &instance(int pri = 0) {
		static MouseDrag inst(pri);
		return inst;
	}

	void registered(int type) {
		EventManager::instance().AddEventHandler(type, { handler });
	}

	std::pair<int, int> handle(SDL_Event *e);

	const SDL_Rect &getDragArea() const { return area; }

	bool isDrag() const {
		if (area.w == 0 && area.h == 0)
			return false;
		return true;
	}

	int priority;

private:
	MouseDrag(int pri) : priority(pri){
		pre.x = -1; pre.y = -1;
		cur.x = -1; cur.y = -1;
	}
	~MouseDrag() {}

	SDL_Point pre;
	SDL_Point cur;
	SDL_Rect area;

	int state = 0;

	std::shared_ptr<ClassEventHandler<MouseDrag>> handler =
		std::make_shared<ClassEventHandler<MouseDrag>>(this, &MouseDrag::handle, priority);
};

