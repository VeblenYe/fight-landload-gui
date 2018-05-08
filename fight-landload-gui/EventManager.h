#pragma once


#include <SDL.h>
#include <list>
#include <map>
#include "EventHandle.h"


using std::list;
using std::map;


/* 带有优先级的事件管理类 */
class EventManager {
public:
	using HandleList = list<EventHandle *>;
	using TypeHandleMap = map<int, HandleList>;

	static EventManager &instance() {
		static EventManager inst;
		return inst;
	}

	void AddEventHandler(int type, std::initializer_list<EventHandle *> handles);

	void RemoveEventHandler(int type, EventHandle *handle);

	void ClearEventHandler(int type) { THMap.erase(type); }

	void DispatchEvent(SDL_Event *e);
private:
	EventManager() {};
	EventManager(const EventManager &) {}
	~EventManager() {};

	TypeHandleMap THMap;
};

