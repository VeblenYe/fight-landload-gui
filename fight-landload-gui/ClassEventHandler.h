#pragma once


#include <SDL.h>
#include "EventHandle.h"
#include <iostream>


// һ��ģ�帨���ֻ࣬���������Ϳ��Խ�һ����ͨ������¼�ע�ᡢ����ͷַ�
template <typename T>
class ClassEventHandler : public EventHandle {
public:
	using Func = std::pair<int, int> (T::*)(SDL_Event *e);

	ClassEventHandler(T *t, Func f, int pri) : ptc(t), func(f), EventHandle(pri) {}

	std::pair<int, int> handleEvent(SDL_Event *e) override {
		if (ptc && func)
			return (ptc->*func)(e);	// ptr�����ָ�룬func�Ǻ���ָ�룬����Ҫ����ptr�е�func����
		return { 0, 0 };
	}

private:
	T * ptc;
	Func func;
};

