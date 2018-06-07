#include "Widget.h"
#include "Window.h"



Widget::Widget(Window *window, int x, int y, int w, int h, int p) : pWindow(window), priority(p) {
	Box.x = x; Box.y = y;
	Box.h = h; Box.w = w;
}


void Widget::addToWindow() const {
	// 这里可不能传this
	pWindow->addWidget(std::make_shared<Widget>(*this));
}


void Widget::removeFromWindow() const {
	pWindow->removeWidget(std::make_shared<Widget>(*this));
}


Widget::~Widget() {}
