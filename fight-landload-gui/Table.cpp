#include "Table.h"
#include "deal.h"
#include "Window.h"
#include "StartButton.h"
#include "DrawButton.h"
#include "CheckButton.h"
#include "EndButton.h"


Table::Table(Window *window) : Widget(window, 0, 0, 0, 0, 0) {
	init();
}


void Table::show() const {
	p1->show();
}


void Table::addToWindow() const {
	getWindow()->addWidget(std::make_shared<Table>(*this));
}


void Table::removeFromWindow() const {
	getWindow()->removeWidget(std::make_shared<Table>(*this));
}


std::pair<int, int> Table::handle(SDL_Event *e) {
	int handle = 0;
	
	if (e->type == SDL_MOUSEBUTTONUP) {
		if (startButton->getState() != 1) {
			auto res = startButton->handle(e);
			if (res.first == 1) {
				auto vec = readIn(getWindow());
				deal(vec, p1.get(), p2.get(), p3.get());
				startButton->removeFromWindow();
				startButton->setState(1);
				drawButton->addToWindow();
				checkButton->addToWindow();
				handle = 1;
				return { handle, 0 };
			}
		}
		if (drawButton->getState() != 1) {
			auto res = drawButton->handle(e);
			if (res.first == 1) {
				handle = 1;
				return { handle, 0 };
			}
		}
		if (checkButton->getState() != 1) {
			auto res = checkButton->handle(e);
			if (res.first == 1) {
				checkButton->setState(1);
				handle = 1;
				return { handle, 0 };
			}
		}
		if (endButton->getState() != 1) {
			auto res = endButton->handle(e);
			if (res.first == 1) {
				handle = 1;
				return { handle, 0 };
			}
		}
	}
	return { handle, 0 };
}


Table::~Table() {}


void Table::init() {
	startButton = std::make_shared<StartButton>(getWindow());
	startButton->loadButtonImage("res/start.jpg");
	startButton->addToWindow();

	drawButton = std::make_shared<DrawButton>(getWindow());
	drawButton->loadButtonImage("res/draw.jpg");

	checkButton = std::make_shared<CheckButton>(getWindow());
	checkButton->loadButtonImage("res/check.jpg");

	endButton = std::make_shared<EndButton>(getWindow());
	endButton->loadButtonImage("res/end.jpg");

	p1 = std::make_shared<Player>();
	p2 = std::make_shared<Player>();
	p3 = std::make_shared<Player>();

	registered(SDL_MOUSEBUTTONUP);
}
