#pragma once


#include "Button.h"


// 开始游戏按钮
class StartButton : public Button {
public:
	StartButton(Window *w);

	void registered(int type) {
		handler = std::make_shared<ClassEventHandler<StartButton>>(this, &StartButton::handle, getPriority());
		EventManager::instance().AddEventHandler(type, { handler });
	}

	std::pair<int, int> handle(SDL_Event *e) override;

	int getState() const { return state; }

	void setState(int s) { state = s; }

	~StartButton();
private:
	std::shared_ptr<ClassEventHandler<StartButton>> handler;
	int state = 0;
};
