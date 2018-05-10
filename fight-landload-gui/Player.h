#pragma once

#include "Poker.h"

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class Player {
public:
	// 持有的牌
	vector<Poker *> hold;

	// 是否是本地玩家
	int local;
};
