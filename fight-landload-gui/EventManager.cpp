#include "EventManager.h"
#include "MouseDrag.h"
#include <algorithm>
#include <iostream>

bool compare(std::shared_ptr<EventHandle> lhs, std::shared_ptr<EventHandle> rhs) {
	return *lhs < *rhs;
}


void EventManager::AddEventHandler(int type, std::initializer_list<std::shared_ptr<EventHandle>> handles) {
	if (handles.size() == 0)
		return;
	auto target = THMap.insert(std::make_pair(type, HandleList()));
	if (target.first == THMap.end())
		return;
	for (auto it = handles.begin(); it != handles.end(); it++) {
		target.first->second.push_back(*it);
		std::cout << "注册类型" << type << "注册函数地址" << *it << "优先级" << (*it)->priority << "注册成功" << std::endl;
		std::cout << "该类型处理函数个数" << target.first->second.size() << std::endl;
	}
	target.first->second.sort(compare);
}


void EventManager::RemoveEventHandler(int type, std::shared_ptr<EventHandle> handle) {
	if (handle == nullptr) {
		std::cout << "handle不存在" << std::endl;
		return;
	}
	auto target = THMap.find(type);
	if (target == THMap.end()) {
		std::cout << "没找到type" << std::endl;
		return;
	}
	auto listIt = find(target->second.begin(), target->second.end(), handle);
	if (listIt != target->second.end()) {
		target->second.erase(listIt);
		std::cout << "移除类型" << type << "移除函数地址" << *listIt << "移除成功"  << std::endl;
		std::cout << "该类型处理函数个数" << target->second.size() << std::endl;
	}
	else
		std::cout << "没找到handle" << std::endl;
}


void EventManager::DispatchEvent(SDL_Event *e) {
	auto target = THMap.find(e->type);
	if (target == THMap.end())
		return;

	auto &handle_list = target->second;
	for (auto listIt = handle_list.begin(); listIt != handle_list.end(); ++listIt) {
		if ((*listIt) == nullptr) continue;
		auto ed = (*listIt)->handleEvent(e);
		if ((*listIt)->priority != 0 && ed.first == 1 && ed.second == 1)
			break;
	}
}
