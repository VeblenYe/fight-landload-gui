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

	// handlerҪ���������ʼ������Ȼ���ȼ�Ϊ0
	void loadButtonImage(const std::string &file) override {
		Button::loadButtonImage(file);
		setPriority(std::stoi(file.substr(10)));
		nums = getPriority() / 10;
		handler = std::make_shared<ClassEventHandler<Poker>>(this, &Poker::handle, getPriority());
	}

	// ע������ȶ���ͼƬ��ע��
	void registered(int type);

	void unregister();

	int getNum() const { return nums; }

	std::pair<int, int> handle(SDL_Event *e);

	~Poker() { unregister();}
private:
	// ���Ǿ�̬�������ᱻ��ʼ��Ϊ��
	static const int weight = 105;
	static const int height = 150;

	// �Ƶ���
	int nums;

	// ��״̬
	int state = 1;

	// �����ˣ�����û��shared_ptr������˵ԭ�򣬿�����shared_ptr��
	std::shared_ptr<Player> holder;

	// ע����¼���������
	std::shared_ptr<ClassEventHandler<Poker>> handler;
};
