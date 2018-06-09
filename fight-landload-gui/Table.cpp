#include "Table.h"
#include "deal.h"
#include "Window.h"


Table::Table(Window *window) : Widget(window, 0, 0, 0, 0, 0) {
	init();
}


void Table::show() {
	p1->show();
	for (auto p : temp)
		p->show();
}


void Table::registered(int type) {
	if (!findEvent(type)) {
		addEvent(type);
		EventManager::instance().AddEventHandler(type, { handler });
	}
}


void Table::unregister() {
	for (auto type : getEvents())
		EventManager::instance().RemoveEventHandler(type, { handler });
}



void Table::updateMap() {
	for (auto p : temp)
		add(p->getNum(), m);
}


void Table::addButton(std::shared_ptr<Button> button) {
	button->addToWindow();
	button->registered(SDL_MOUSEBUTTONDOWN);
	button->registered(SDL_MOUSEBUTTONUP);
}


void Table::removeButton(std::shared_ptr<Button> button) {
	button->unregister();
	button->removeFromWindow();
}


std::pair<int, int> Table::handle(SDL_Event *e) {

	// 开始按钮被按下
	if (startButton->getState() == 1) {
		// 将开始按钮状态置零
		startButton->setState(0);

		// 移除开始按钮
		removeButton(startButton);
		
		// 发牌
		auto vec = readIn(getWindow());
		deal(vec, p1.get(), p2.get(), p3.get());
		p1->resetPos();

		// 添加出牌和过牌按钮，不知道为啥这里要手动，事件注册出问题
		// 因为之前都是用make_shared<>()新生成处理函数，所以每个函数不同，导致注册和移除出现问题
		addButton(drawButton);
		addButton(checkButton);

		// 直接返回
		return { 1, 0 };
	}


	// 出牌按钮被按下
	if (drawButton->getState() == 1) {
		drawButton->setState(0);
		//removeButton(drawButton);
	}


	if (checkButton->getState() == 1) {
		
	}
	if (endButton->getState() == 1) {
	}

	return { 0, 0 };
}


Table::~Table() { unregister(); }


void Table::init() {
	startButton = std::make_shared<Button>(getWindow(), 650, 550, 300, 100);
	startButton->loadButtonImage("res/start.jpg");
	addButton(startButton);

	drawButton = std::make_shared<Button>(getWindow(), 600, 575, 150, 50);
	drawButton->loadButtonImage("res/draw.jpg");

	checkButton = std::make_shared<Button>(getWindow(), 850, 575, 150, 50);
	checkButton->loadButtonImage("res/check.jpg");

	endButton = std::make_shared<Button>(getWindow(), 400, 400, 500, 200);
	endButton->loadButtonImage("res/end.jpg");

	p1 = std::make_shared<Player>();
	p2 = std::make_shared<Player>();
	p3 = std::make_shared<Player>();

	registered(SDL_MOUSEBUTTONUP);
}
