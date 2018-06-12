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

	// ��������
	void addToHold(Poker *p);

	// ���ذ汾
	void addToHold(vector<Poker *> &vec);

	// �Ƴ�����
	void removeFromHold(Poker *p);

	void removeFromHold(vector<Poker *> &vec);

	int holdSize() const { return hold.size(); }

	// ������ʱ�ƶ�
	void addToTemp(Poker *);

	void addToTemp(vector<Poker *> &vec);

	// �Ƴ���ʱ�ƶ�
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
	// ���е���
	vector<Poker *> hold;

	CardTypeMap m;

	// ѡ�е��ƣ���Э�ˣ�����ָ�����Լ�����
	vector<Poker *> temp;

	CardTypeMap t;
};
