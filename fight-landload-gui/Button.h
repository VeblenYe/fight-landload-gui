#pragma once


#include <SDL.h>
#include <string>
#include <utility>
#include "Window.h"


using std::string;


class Button {
public:
	Button(Window *window, int x, int y, int w, int h) {
		pWindow = window;
		buttonBox.x = x; buttonBox.y = y;
		buttonBox.w = w; buttonBox.h = h;
	}


	// !注意，内联函数要放在头文件里，要是放在实现文件里会报错
	virtual void loadButtonImage(const string &file) {
		buttonImage = pWindow->loadImage(file);
	}

	void show(SDL_Rect *dst = NULL) {
		if (dst)
			pWindow->draw(buttonImage, *dst);
		else
			pWindow->draw(buttonImage, buttonBox);
	}

	virtual std::pair<int, int> handle(SDL_Event *e) { return { 0, 0 }; }

	SDL_Rect buttonBox;
	SDL_Texture *buttonImage;

	virtual ~Button() { SDL_DestroyTexture(buttonImage); }
private:
	Window * pWindow;
};
