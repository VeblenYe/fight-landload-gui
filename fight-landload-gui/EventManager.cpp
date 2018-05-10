#include "EventManager.h"
#include "MouseDrag.h"
#include <iostream>
#include <algorithm>

bool compare(EventHandle *lhs, EventHandle *rhs) {
	return *lhs < *rhs;
}


void EventManager::AddEventHandler(int type, std::initializer_list<EventHandle *> handles) {
	if (handles.size() == 0)
		return;
	auto target = THMap.insert(std::make_pair(type, HandleList()));
	if (target.first == THMap.end())
		return;
	for (auto it = handles.begin(); it != handles.end(); it++)
		target.first->second.push_back(*it);
	target.first->second.sort(compare);
	/*
	std::cout << THMap.size() << std::ends;*/
	/*
	for (auto mapIt = THMap.begin(); mapIt != THMap.end(); mapIt++) {
		std::cout << mapIt->first << std::ends;
		for (auto listIt = mapIt->second.begin(); listIt != mapIt->second.end(); listIt++)
			std::cout << (**listIt).priority << std::ends;
		std::cout << std::endl;
	}
	*/
}


void EventManager::RemoveEventHandler(int type, EventHandle *handle) {
	if (handle == nullptr)
		return;
	auto target = THMap.find(type);
	if (target == THMap.end())
		return;
	auto listIt = find(target->second.begin(), target->second.end(), handle);
	if (listIt != target->second.end())
		target->second.erase(listIt);
}


void EventManager::DispatchEvent(SDL_Event *e) {
	auto target = THMap.find(e->type);
	if (target == THMap.end())
		return;

	auto &handle_list = target->second;
	for (auto listIt = handle_list.begin(); listIt != handle_list.end(); ++listIt) {
		if ((*listIt) == nullptr) continue;
		auto ed = (*listIt)->handleEvent(e);
		if (((*listIt)->priority != 0) && (ed.first == 1) && (!MouseDrag::instance().isDrag() || ed.second == 1))
			break;
	}
}
