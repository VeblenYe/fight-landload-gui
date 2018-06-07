#pragma once


#include "Button.h"


class CheckButton : public Button {
public:
	CheckButton(Window *window);

	std::pair<int, int> handle(SDL_Event *e) override;

	void registered(int type) {
		handler = std::make_shared<ClassEventHandler<CheckButton>>(this, &CheckButton::handle, getPriority());
		EventManager::instance().AddEventHandler(type, { handler });
	}

	int getState() const { return state; }
	
	void setState(int s) { state = s; }

	~CheckButton();
private:
	std::shared_ptr<ClassEventHandler<CheckButton>> handler;
	int state;
};

