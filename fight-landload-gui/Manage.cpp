#include "Manage.h"
#include "ClassEventHandler.h"
#include "MouseDrag.h"
#include <iostream>
#include <random>
#include <sstream>
#include <algorithm>
#include <memory>
#include <ctime>


using std::cout;
using std::endl;
using std::vector;
using std::ostringstream;
using std::default_random_engine;
using std::uniform_int_distribution;


// 初始化所有组件
int initialize(Window *window) {

	// 载入背景图
	try {
		window->loadBackground("res/background.jpg");
	}
	catch (const std::runtime_error &e) {
		cout << e.what() << endl;
		delete window;
		return -1;
	}

	// 注册鼠标拖动事件到事件分发系统
	// 这里一定要new对象，否则会被析构
	// 记得删除。。。
	MouseDrag::instance().registered(SDL_MOUSEBUTTONDOWN);
	MouseDrag::instance().registered(SDL_MOUSEBUTTONUP);

	return 1;
}

// 读入所有扑克牌
vector<shared_ptr<Poker>> readIn(Window *window) {
		ostringstream os;
		vector<shared_ptr<Poker>> vec;
		for (int i = 30; i < 180; i += 10) {
			if(i < 160)
				for (int j = 0; j < 4; j++) {
					os << "pukeImage/" << i + j << ".jpg";
					Poker *p = new Poker(window, 800, 700);
					p->loadButtonImage(os.str());
					p->registered(SDL_MOUSEBUTTONUP);
					vec.push_back(shared_ptr<Poker>(p));
					os.str("");
				}
			else {
				os << "pukeImage/" << i << ".jpg";
				Poker *p = new Poker(window, 800, 700);
				p->loadButtonImage(os.str());
				p->registered(SDL_MOUSEBUTTONUP);
				vec.push_back(shared_ptr<Poker>(p));
				os.str("");
			}
		}
		return vec;
}


// 发牌
bool compare(shared_ptr<Poker> lhs, shared_ptr<Poker> rhs) {
	return lhs->priority < rhs->priority;
}

void deal(vector<shared_ptr<Poker>> vec, Player *p1, Player *p2, Player *p3) {

	p1->hold.clear();
	p2->hold.clear();
	p3->hold.clear();
	// 随机分发
	static default_random_engine e(std::time(0));
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 18; j++) {
			uniform_int_distribution<unsigned> u(0, vec.size() - 1);
			if (i == 0) {
				int k = u(e);
				p1->hold.push_back(vec[k]);
				std::swap(vec[k], vec[vec.size() - 1]);
				vec.erase(vec.begin() + vec.size() - 1);
			}
			else {
				int k = u(e);
				p2->hold.push_back(vec[k]);
				std::swap(vec[k], vec[vec.size() - 1]);
				vec.erase(vec.begin() + vec.size() - 1);
			}
		}
	}
	p3->hold = vec;

	std::sort(p1->hold.begin(), p1->hold.end(), compare);
	std::sort(p2->hold.begin(), p2->hold.end(), compare);
	std::sort(p3->hold.begin(), p3->hold.end(), compare);

	for (int i = 0; i < p1->hold.size(); i++) {
		p1->hold[i]->setPos(1125 - 45 * i, 700);
	}

	for (int i = 0; i < p2->hold.size(); i++) {
		p2->hold[i]->setPos(1125 - 45 * i, 400);
	}
	
	for (int i = 0; i < p3->hold.size(); i++) {
		p3->hold[i]->setPos(1125 - 45 * i, 100);
	}

	std::reverse(p1->hold.begin(), p1->hold.end());
	std::reverse(p2->hold.begin(), p2->hold.end());
	std::reverse(p3->hold.begin(), p3->hold.end());
}
