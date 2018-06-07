#include "MouseDrag.h"
#include <iostream>


std::pair<int, int> MouseDrag::handle(SDL_Event *e) {
	int handled = 0;

	if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		pre.x = x; pre.y = y;
		handled = 1;
		state = 1;
		std::cout << "开始记录pre" << std::endl;
		std::cout << "pre.x" << pre.x << " pre.y" << pre.y << std::endl;
		return { handled, 0 };
	}
	
	if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT && state) {
		state = 0;
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		cur.x = x; cur.y = y;

		std::cout << "开始记录cur" << std::endl;
		std::cout << "cur.x" << cur.x << " cur.y" << cur.y << std::endl;

		// 保证矩形长宽均为正值
		if (pre.x <= cur.x) {
			if (pre.y <= cur.y) {
				area.x = pre.x; area.y = pre.y;
				area.w = cur.x - pre.x; area.h = cur.y - pre.y;
			}
			else {
				area.x = pre.x; area.y = cur.y;
				area.w = cur.x - pre.x; area.h = pre.y - cur.y;
			}
		}
		else {
			if (pre.y <= cur.y) {
				area.x = cur.x; area.y = pre.y;
				area.w = pre.x - cur.x; area.h = cur.y - pre.y;
			}
			else {
				area.x = cur.x; area.y = cur.y;
				area.w = pre.x - cur.x; area.h = pre.y - cur.y;
			}
		}
		handled = 1;
		return { handled, 0 };
	}

	return { handled, 0 };
}
