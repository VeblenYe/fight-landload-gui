#pragma once

#include "Button.h"


class EndButton : public Button{
public:
	EndButton(Window *window);

	void registered(int type) {
		handler = std::make_shared<ClassEventHandler<EndButton>>(this, &EndButton::handle, getPriority());
		EventManager::instance().AddEventHandler(type, { handler });
	}

	std::pair<int, int> handle(SDL_Event *e);

	int getState() const { return state; }
	void setState(int s) { state = s; }

	~EndButton();
private:
	std::shared_ptr<ClassEventHandler<EndButton>> handler;
	int state = 0;
};

