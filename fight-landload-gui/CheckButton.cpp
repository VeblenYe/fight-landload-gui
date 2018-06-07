#include "CheckButton.h"
#include "common.h"



CheckButton::CheckButton(Window *window) : Button(window, 100, 100, 300, 150) {}


CheckButton::~CheckButton() {}


std::pair<int, int> CheckButton::handle(SDL_Event *e) {
	int handle;

	if (isInArea(getBox())) {
		handle = 1;
		state = 1;
	}

	return { handle, state };
}
