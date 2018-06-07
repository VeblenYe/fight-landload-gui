#include "Button.h"
#include "Window.h"


Button::Button(Window *window, int x, int y, int w, int h, int p) : Widget(window, x, y, w, h, p) {}


void Button::loadButtonImage(const std::string &file) {
	buttonImage =  getWindow()->loadImage(file);
}


void Button::show() const {
	getWindow()->draw(buttonImage, getBox());
}


void Button::addToWindow() const {
	getWindow()->addWidget(std::make_shared<Button>(*this));
}


void Button::removeFromWindow() const {
	getWindow()->removeWidget(std::make_shared<Button>(*this));
}


void Button::registered(int type) {
	handler = std::make_shared<ClassEventHandler<Button>>(this, &Button::handle, getPriority());
	EventManager::instance().AddEventHandler(type, { handler });
}
