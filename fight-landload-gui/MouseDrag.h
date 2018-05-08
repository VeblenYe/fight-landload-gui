#pragma once


#include <SDL.h>
#include "ClassEventHandler.h"
#include "EventManager.h"


class MouseDrag {
public:
	MouseDrag(int pri) : priority(pri){
		pre.x = -1; pre.y = -1;
		cur.x = -1; cur.y = -1;
	}

	static MouseDrag &instance(int pri = 0) {
		static MouseDrag inst(pri);
		return inst;
	}

	std::pair<int, int> handle(SDL_Event *e);

	SDL_Rect getDragArea() const { return area; }

	bool isDrag() const {
		if (area.w == 0 && area.h == 0)
			return false;
		return true;
	}

	int priority;

	~MouseDrag() {}
private:
	SDL_Point pre;
	SDL_Point cur;
	SDL_Rect area;

	int state = 0;
};

