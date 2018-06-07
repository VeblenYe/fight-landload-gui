#pragma once

#include "Button.h"


class DrawButton : public Button {
public:
	DrawButton(Window *window);

	std::pair<int, int> handle(SDL_Event *e) override;

	void registered(int type) {
		handler = std::make_shared<ClassEventHandler<DrawButton>>(this, &DrawButton::handle, getPriority());
		EventManager::instance().AddEventHandler(type, { handler });
	}

	int getState() const { return state; }
	void setState(int s) { state = s; }

	~DrawButton();
private:
	std::shared_ptr<ClassEventHandler<DrawButton>> handler;
	int state = 0;
};

