#pragma once


#include "GUIfwd.h"
#include "EventManager.h"
#include "ClassEventHandler.h"

#include <SDL.h>
#include <memory>
#include <unordered_set>
#include <utility>


class Widget : public std::enable_shared_from_this<Widget> {
public:
	Widget(Window *window, int x, int y, int w, int h, int p);

	// 实际上只要show()和析构函数为虚函数即可
	virtual void show() {}

	// 事件处理
	std::pair<int, int> handle(SDL_Event *e) { return { 0, 0 }; }

	// 注册到窗口
	void addToWindow();

	// 从窗口移除
	void removeFromWindow();

	// 注册事件处理
	void registered(int type);

	// 移除所有事件
	void unregister();

	Window *getWindow() const { return pWindow; }

	const SDL_Rect &getBox() const {
		return Box;
	}

	void setPos(int x, int y) {
		Box.x = x; Box.y = y;
	}

	int getPriority() const { return priority; }

	void setPriority(int p) { priority = p; }

	void addEvent(int type) {
		events.insert(type);
	}

	bool findEvent(int type) {
		return events.find(type) != events.end();
	}

	const std::unordered_set<int> &getEvents() const {
		return events;
	}

	virtual ~Widget() {}
private:
	// 所在窗口
	Window * pWindow;

	// 所占区域
	SDL_Rect Box;

	// 优先级
	int priority;

	// 注册的事件及处理函数
	std::shared_ptr<ClassEventHandler<Widget>> handler =
		std::make_shared<ClassEventHandler<Widget>>(this, &Widget::handle, getPriority());
	std::unordered_set<int> events;
};
