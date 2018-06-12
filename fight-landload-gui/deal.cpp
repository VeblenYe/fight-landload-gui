#include "deal.h"
#include "CardTypeManager.h"
#include <sstream>
#include <random>
#include <ctime>


using std::ostringstream;
using std::default_random_engine;
using std::uniform_int_distribution;



// 读入所有扑克牌
vector<Poker *> readIn(Window *window) {
	ostringstream os;
	vector<Poker *> vec;
	for (int i = 30; i < 180; i += 10) {
		if (i < 160)
			for (int j = 0; j < 4; j++) {
				os << "pukeImage/" << i + j << ".jpg";
				auto p = new Poker(window, 0, 0);
				p->loadButtonImage(os.str());
				p->registered(SDL_MOUSEBUTTONUP);
				vec.push_back(p);
				os.str("");
			}
		else {
			os << "pukeImage/" << i << ".jpg";
			auto p = new Poker(window, 0, 0);
			p->loadButtonImage(os.str());
			p->registered(SDL_MOUSEBUTTONUP);
			vec.push_back(p);
			os.str("");
		}
	}
	return vec;
}


// 发牌
void deal(vector<Poker *> vec, Player *p1, Player *p2, Player *p3) {
	p1->clear();
	p2->clear();
	p3->clear();

	// 随机分发
	static default_random_engine e(std::time(0));
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 18; j++) {
			uniform_int_distribution<unsigned> u(0, vec.size() - 1);
			if (i == 0) {
				int k = u(e);
				p1->addToHold(vec[k]);
				std::swap(vec[k], vec[vec.size() - 1]);
				vec.erase(vec.begin() + vec.size() - 1);
			}
			else {
				int k = u(e);
				p2->addToHold(vec[k]);
				std::swap(vec[k], vec[vec.size() - 1]);
				vec.erase(vec.begin() + vec.size() - 1);
			}
		}
	}
	p3->addToHold(vec);
}
