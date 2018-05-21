#pragma once


#include "Button.h"


class Poker : public Button {
	friend bool operator<(const Poker &lhs, const Poker &rhs);
public:
	Poker(Window *window, int x, int y) : Button(window, x, y, weight, height) {}

	void loadButtonImage(const string &file) override {
		Button::loadButtonImage(file);
		priority = std::stoi(file.substr(10));
		nums = priority / 10;
	}

	// ע������ȶ���ͼƬ��ע��
	void registered(int type) override {
		ClassEventHandler<Poker> *handle =
			new ClassEventHandler<Poker>(this, &Poker::handle, this->priority);
		EventManager::instance().AddEventHandler(type, { handle });
	}

	int getNum() const {
		return nums;
	}

	std::pair<int, int> handle(SDL_Event *e) override;

	~Poker() {}
private:
	// ���Ǿ�̬�������ᱻ��ʼ��Ϊ��
	static const int weight = 105;
	static const int height = 150;

	// �Ƶ���
	int nums;

	// ��״̬
	int state = 0;

	// �ƶ�����
	int moveExtent;

	// �̶������ƾ���
	static const int move = -60;
};

