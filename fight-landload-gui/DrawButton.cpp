#include "DrawButton.h"
#include "common.h"



DrawButton::DrawButton(Window *window) : Button(window, 100, 100, 300, 150) {}


std::pair<int, int> DrawButton::handle(SDL_Event *e) {
	int handle = 0;

	if (isInArea(getBox())) {
		handle = 1;
		state = 1;
	}

	return { handle, state };
}


DrawButton::~DrawButton() {}
