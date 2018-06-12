#pragma once


#include <map>
#include <memory>
#include "CardTypefwd.h"


using std::map;
using std::shared_ptr;
using std::pair;


// 牌数相同，点数小在前，牌数不同，牌数多在前
struct Compare {
	bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const {
		if (lhs.second == rhs.second)
			return lhs.first < rhs.first;
		return rhs.second < lhs.second;
	}
};


// pair中的第一个int是点数，第二个int是张数，这是为了比较
using CardTypeMap = map<pair<int, int>, shared_ptr<BasicCardType>, Compare>;
