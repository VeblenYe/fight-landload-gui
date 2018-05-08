#include "EventManager.h"
#include "MouseDrag.h"


void EventManager::AddEventHandler(int type, std::initializer_list<EventHandle *> handles) {
	if (handles.size() == 0)
		return;
	auto target = THMap.insert(std::make_pair(type, HandleList()));
	if (target.first == THMap.end())
		return;
	for (auto it = handles.begin(); it != handles.end(); it++)
		target.first->second.push_back(*it);
	target.first->second.sort();
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
