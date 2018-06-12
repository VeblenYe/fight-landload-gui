#pragma once


#include "GameItemfwd.h"
#include <vector>
#include <memory>
#include "CardTypeMap.h"


using std::vector;
using std::shared_ptr;


class Player : public std::enable_shared_from_this<Player> {
public:

	void show();

	// 加入手牌
	void addToHold(Poker *p);

	// 重载版本
	void addToHold(vector<Poker *> &vec);

	// 移出手牌
	void removeFromHold(Poker *p);

	void removeFromHold(vector<Poker *> &vec);

	int holdSize() const { return hold.size(); }

	// 加入临时牌堆
	void addToTemp(Poker *);

	void addToTemp(vector<Poker *> &vec);

	// 移出临时牌堆
	void removeFromTemp(Poker *);

	int tempSize() const { return temp.size(); }

	void resetPos();

	void setPokerState(int i);

	vector<Poker *> &getTemp() { return temp; }

	void clear() {
		m.clear();
		t.clear();
		clearHold();
		clearTemp();
	}

	void clearHold();

	void clearTemp() { temp.clear(); }

	bool isEmpty() const { return hold.empty(); }

	const CardTypeMap &getCardTypeMap() const { return m; }

	CardTypeMap &getCardTypeMapTemp() { return t; }

	const vector<Poker *> &getHold() const { return hold; }

private:
	// 持有的牌
	vector<Poker *> hold;

	CardTypeMap m;

	// 选中的牌，妥协了，智能指针老自己析构
	vector<Poker *> temp;

	CardTypeMap t;
};
