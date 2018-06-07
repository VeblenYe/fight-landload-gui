#pragma once


#include "GUIfwd.h"
#include <utility>
#include <SDL.h>
#include "ClassEventHandler.h"
#include "EventManager.h"
#include <memory>


class Widget {
public:
	Widget(Window *window, int x, int y, int w, int h, int p);

	virtual void show() const {}

	virtual std::pair<int, int> handle(SDL_Event *e) { return { 0, 0 }; }

	virtual void addToWindow() const;

	virtual void removeFromWindow() const;

	virtual void registered(int type) {
		handler = std::make_shared<ClassEventHandler<Widget>>(this, &Widget::handle, priority);
		EventManager::instance().AddEventHandler(type, { handler });
	}

	Window *getWindow() const { return pWindow; }

	const SDL_Rect &getBox() const {
		return Box;
	}

	void setPos(int x, int y) {
		Box.x = x; Box.y = y;
	}

	int getPriority() const { return priority; }

	void setPriority(int p) { priority = p; }

	virtual ~Widget();
private:
	Window * pWindow;
	SDL_Rect Box;
	int priority;
	std::shared_ptr<ClassEventHandler<Widget>> handler;
};
