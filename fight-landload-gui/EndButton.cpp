#include "EndButton.h"
#include "common.h"


EndButton::EndButton(Window *window) : Button(window, 800, 500, 150, 150) {}


EndButton::~EndButton() {}


std::pair<int, int> EndButton::handle(SDL_Event *e) {
	int handle = 0;

	if (isInArea(getBox())) {
		handle = 1;
		state = 1;
	}

	return { handle, state };
}
