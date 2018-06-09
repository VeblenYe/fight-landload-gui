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

	// ʵ����ֻҪshow()����������Ϊ�麯������
	virtual void show() {}

	// �¼�����
	std::pair<int, int> handle(SDL_Event *e) { return { 0, 0 }; }

	// ע�ᵽ����
	void addToWindow();

	// �Ӵ����Ƴ�
	void removeFromWindow();

	// ע���¼�����
	void registered(int type);

	// �Ƴ������¼�
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
	// ���ڴ���
	Window * pWindow;

	// ��ռ����
	SDL_Rect Box;

	// ���ȼ�
	int priority;

	// ע����¼���������
	std::shared_ptr<ClassEventHandler<Widget>> handler =
		std::make_shared<ClassEventHandler<Widget>>(this, &Widget::handle, getPriority());
	std::unordered_set<int> events;
};
