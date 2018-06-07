#pragma once

#include "Buttonfwd.h"
#include "GameItemfwd.h"
#include <vector>
#include <memory>


using std::vector;
using std::shared_ptr;


class Player {
public:

	void show();

	void addToHold(shared_ptr<Poker> p);

	// ���ذ汾
	void addToHold(vector<shared_ptr<Poker>> &vec);

	void removeFromHold(shared_ptr<Poker> p);

	void addToTemp(shared_ptr<Poker> p);

	void removeFromTemp(shared_ptr<Poker> p);

	void clear() {
		hold.clear();
		temp.clear();
	}

private:
	// ���е���
	vector<shared_ptr<Poker>> hold;

	// ѡ�е���
	vector<shared_ptr<Poker>> temp;

	void reset();
};
