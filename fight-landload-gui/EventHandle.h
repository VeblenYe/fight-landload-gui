#pragma once


#include <SDL.h>
#include <utility>

// 事件处理基类
class EventHandle {
	friend bool operator<(const EventHandle &lhs, const EventHandle &rhs);
public:
	EventHandle(int pri) : priority(pri) {}
	virtual std::pair<int, int> handleEvent(SDL_Event *e) {
		return { 0, 0 };
	}
	int priority;
};

