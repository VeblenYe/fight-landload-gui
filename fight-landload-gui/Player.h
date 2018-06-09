#pragma once


#include "GameItemfwd.h"
#include <vector>
#include <memory>


using std::vector;
using std::shared_ptr;


class Player : public std::enable_shared_from_this<Player> {
public:

	void show();

	void addToHold(shared_ptr<Poker> p);

	// ���ذ汾
	void addToHold(vector<shared_ptr<Poker>> &vec);

	void removeFromHold(shared_ptr<Poker> p);

	int holdSize() const { return hold.size(); }

	void addToTemp(Poker *p);

	void removeFromTemp(Poker *p);

	int tempSize() const { return temp.size(); }

	void resetPos();

	vector<Poker *> &getTemp() {
		return temp;
	}

	void clear() {
		hold.clear();
		temp.clear();
	}

private:
	// ���е���
	vector<shared_ptr<Poker>> hold;

	// ѡ�е��ƣ���Э�ˣ�����ָ�����Լ�����
	vector<Poker *> temp;
};
