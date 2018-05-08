#pragma once


#include "Button.h"


class Poker : public Button {
	friend bool operator<(const Poker &lhs, const Poker &rhs);
public:
	Poker(Window *window, int x, int y) : Button(window, x, y, weight, height) {}

	void loadButtonImage(const string &file) override {
		Button::loadButtonImage(file);
		priority = std::stoi(file);
		nums = priority / 10;
	}

	int getNum() const {
		return nums;
	}

	void show() {
		auto temp = buttonBox;
		temp.y += moveExtent;
		Button::show(&temp);
	}

	std::pair<int, int> handle(SDL_Event *e) override;
	
	// 优先级
	int priority;

	~Poker() {}
private:
	// 不是静态参量不会被初始化为零
	static const int weight = 105;
	static const int height = 150;

	// 牌点数
	int nums;

	// 牌状态
	int state = 0;

	// 移动距离
	int moveExtent;

	// 固定的上移距离
	static const int move = -60;
};

