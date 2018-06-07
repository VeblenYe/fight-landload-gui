#pragma once


#include "Button.h"
#include "Buttonfwd.h"
#include "GameItemfwd.h"


class Poker : public Button {
	friend bool operator<(const Poker &lhs, const Poker &rhs);
public:
	Poker(Window *window, int x, int y) : Button(window, x, y, weight, height), holder(nullptr) {}

	void setHolder(std::shared_ptr<Player> h) {
		holder = h;
	}

	void loadButtonImage(const std::string &file) override {
		Button::loadButtonImage(file);
		setPriority(std::stoi(file.substr(10)));
		nums = getPriority() / 10;
	}

	// 注意必须先读入图片再注册
	void registered(int type) { 
		auto handle = std::make_shared<ClassEventHandler<Poker>>(this, &Poker::handle, getPriority());
		EventManager::instance().AddEventHandler(type, { handle });
	}

	int getNum() const { return nums; }

	std::pair<int, int> handle(SDL_Event *e) override;

	~Poker() {}
private:
	// 不是静态参量不会被初始化为零
	static const int weight = 105;
	static const int height = 150;

	// 牌点数
	int nums;

	// 牌状态
	int state = 0;

	// 持有人
	std::shared_ptr<Player> holder;
};
