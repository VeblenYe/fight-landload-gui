#pragma once


#include <map>
#include <memory>
#include "CardTypefwd.h"


using std::map;
using std::shared_ptr;
using std::pair;


// ������ͬ������С��ǰ��������ͬ����������ǰ
struct Compare {
	bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const {
		if (lhs.second == rhs.second)
			return lhs.first < rhs.first;
		return rhs.second < lhs.second;
	}
};


// pair�еĵ�һ��int�ǵ������ڶ���int������������Ϊ�˱Ƚ�
using CardTypeMap = map<pair<int, int>, shared_ptr<BasicCardType>, Compare>;
