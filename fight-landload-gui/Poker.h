#pragma once


#include "Button.h"
#include "GameItemfwd.h"


class Poker : public Button {
	friend bool operator<(const Poker &lhs, const Poker &rhs);
public:
	Poker(Window *window, int x, int y) : Button(window, x, y, weight, height), holder(nullptr) {}

	void setHolder(std::shared_ptr<Player> h) {
		holder = h;
	}

	// handler要放在这里初始化，不然优先级为0
	void loadButtonImage(const std::string &file) override {
		Button::loadButtonImage(file);
		setPriority(std::stoi(file.substr(10)));
		nums = getPriority() / 10;
		handler = std::make_shared<ClassEventHandler<Poker>>(this, &Poker::handle, getPriority());
	}

	// 注意必须先读入图片再注册
	void registered(int type);

	void unregister();

	int getNum() const { return nums; }

	std::pair<int, int> handle(SDL_Event *e);

	~Poker() { unregister();}
private:
	// 不是静态参量不会被初始化为零
	static const int weight = 105;
	static const int height = 150;

	// 牌点数
	int nums;

	// 牌状态
	int state = 1;

	// 持有人，这里没用shared_ptr，懒得说原因，可以用shared_ptr了
	std::shared_ptr<Player> holder;

	// 注册的事件及处理函数
	std::shared_ptr<ClassEventHandler<Poker>> handler;
};
