#include "Button.h"
#include "Window.h"
#include "common.h"
#include <iostream>


Button::Button(Window *window, int x, int y, int w, int h, int p, SDL_Rect *c) : 
	Widget(window, x, y, w, h, p), clip(c) {}


void Button::loadButtonImage(const std::string &file) {
	buttonImage = getWindow()->loadImage(file);
}


void Button::show() {
	getWindow()->draw(buttonImage, getBox(), clip);
}


std::pair<int, int> Button::handle(SDL_Event *e) {

	if (e->type == SDL_MOUSEBUTTONDOWN && isInArea(getBox())) {
		setClip(67, 30, 645, 275);
		return { 1, 0 };
	}

	if (e->type == SDL_MOUSEBUTTONUP) {
		if (isInArea(getBox())) {
			setClip(67, 40, 645, 275);
			if (state == -1) {
				return { 1, 0 };
			}
			state = 1;
			return { 1, 0 };
		}
		else {
			setClip(67, 40, 645, 275);
			return { 1, 0 };
		}
	}

	return { 0, 0 };
}


void Button::registered(int type) {
	if (!findEvent(type)) {
		addEvent(type);
		EventManager::instance().AddEventHandler(type, { handler });
	}
}

void Button::unregister() {
	for (auto type : getEvents())
		EventManager::instance().RemoveEventHandler(type, { handler });
}
