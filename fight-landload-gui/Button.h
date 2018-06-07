#pragma once

#include <string>
#include "Widget.h"


class Button : public Widget {
public:
	Button(Window *window, int x, int y, int w, int h, int p = 0);

	virtual void loadButtonImage(const std::string &file);

	void show() const override;

	void addToWindow() const override;

	void removeFromWindow() const override;

	void registered(int type) override;

	std::pair<int, int> handle(SDL_Event *e) override { return { 0, 0 }; }

	~Button() { SDL_DestroyTexture(buttonImage); }
private:
	SDL_Texture *buttonImage;
	std::shared_ptr<ClassEventHandler<Button>> handler;
};
