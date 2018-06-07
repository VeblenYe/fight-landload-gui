#include "StartButton.h"
#include "common.h"
#include "Table.h"


StartButton::StartButton(Window *w) : Button(w, 600, 450, 300, 150) {}


StartButton::~StartButton() {}



std::pair<int, int> StartButton::handle(SDL_Event *e) {
	int handle;

	if (isInArea(getBox())) {
		handle = 1;
	}

	return { handle, 0 };
}
