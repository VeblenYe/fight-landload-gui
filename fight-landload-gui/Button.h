#pragma once


#include <SDL.h>
#include <string>
#include <utility>
#include "ClassEventHandler.h"
#include "EventManager.h"
#include "Window.h"


using std::string;


class Button {
public:
	Button(Window *window, int x, int y, int w, int h, int pri = 0) : priority(pri) {
		pWindow = window;
		buttonBox.x = x; buttonBox.y = y;
		buttonBox.w = w; buttonBox.h = h;
	}

	void setPos(int x, int y) {
		buttonBox.x = x;
		buttonBox.y = y;
	}

	// !注意，内联函数要放在头文件里，要是放在实现文件里会报错
	virtual void loadButtonImage(const string &file) {
		buttonImage = pWindow->loadImage(file);
	}

	void show() {
		pWindow->draw(buttonImage, buttonBox);
	}

	virtual void registered(int type) {
		ClassEventHandler<Button> *handle =
			new ClassEventHandler<Button>(this, &Button::handle, this->priority);
		EventManager::instance().AddEventHandler(type, { handle });
	}

	virtual std::pair<int, int> handle(SDL_Event *e) { return { 0, 0 }; }

	SDL_Rect buttonBox;
	SDL_Texture *buttonImage;

	int priority;

	virtual ~Button() { SDL_DestroyTexture(buttonImage); }
private:
	Window * pWindow;
};
