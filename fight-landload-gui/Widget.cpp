#include "Widget.h"
#include "Window.h"


Widget::Widget(Window *window, int x, int y, int w, int h, int p) : pWindow(window), priority(p) {
	Box.x = x; Box.y = y;
	Box.h = h; Box.w = w;
}


void Widget::addToWindow() {
	pWindow->addWidget(shared_from_this());
}


void Widget::removeFromWindow() {
	pWindow->removeWidget(shared_from_this());
}


void Widget::registered(int type) {
	auto pos = events.find(type);
	if (pos == events.end()) {
		events.insert(type);
		EventManager::instance().AddEventHandler(type, { handler });
	}
}

void Widget::unregister() {
	for (auto e : events)
		EventManager::instance().RemoveEventHandler(e, { handler });
}
