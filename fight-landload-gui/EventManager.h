#pragma once


#include <SDL.h>
#include <list>
#include <map>
#include <memory>
#include "EventHandle.h"


using std::list;
using std::map;


/* 带有优先级的事件管理类 */
class EventManager {
public:
	using HandleList = list<std::shared_ptr<EventHandle>>;
	using TypeHandleMap = map<int, HandleList>;

	EventManager(const EventManager &) = delete;

	static EventManager &instance() {
		static EventManager inst;
		return inst;
	}

	void AddEventHandler(int type, std::initializer_list<std::shared_ptr<EventHandle>> handles);

	void RemoveEventHandler(int type, std::shared_ptr<EventHandle> handle);

	void ClearEventHandler(int type) { THMap.erase(type); }

	void DispatchEvent(SDL_Event *e);
private:
	EventManager() {};
	
	~EventManager() {};

	TypeHandleMap THMap;
};
