#pragma once


#include <SDL.h>
#include "EventHandle.h"
#include <iostream>


// 一个模板辅助类，只需特例化就可以将一个普通类进行事件注册、处理和分发
template <typename T>
class ClassEventHandler : public EventHandle {
public:
	using Func = std::pair<int, int> (T::*)(SDL_Event *e);

	ClassEventHandler(T *t, Func f, int pri) : ptc(t), func(f), EventHandle(pri) {}

	std::pair<int, int> handleEvent(SDL_Event *e) override {
		if (ptc && func)
			return (ptc->*func)(e);	// ptr是类的指针，func是函数指针，我们要调用ptr中的func函数
		return { 0, 0 };
	}

private:
	T * ptc;
	Func func;
};

