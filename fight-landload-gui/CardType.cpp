#include "CardType.h"


bool BasicCardType::bigger(BasicCardType *t) const {
	if (basicType == QUADRUPLE)
		if (t->basicType == QUADRUPLE)
			return getPoints() > t->getPoints();
		else
			return true;
	if (t->basicType == QUADRUPLE)
		return false;
	if (basicType != t->basicType)
		return false;
	return getPoints() > t->getPoints();
}


bool BasicCardType::bigger(CombinationCardType *t) const {
	if (t->getConType() == ROCKET)
		return false;
	if (basicType == QUADRUPLE)
		return true;
	return false;
}


bool CombinationCardType::bigger(BasicCardType *t) const {
	if (conType == ROCKET)
		return true;
	return false;
}


bool CombinationCardType::bigger(CombinationCardType *t) const {
	if (conType == ROCKET)
		return true;
	if (t->conType == ROCKET)
		return false;
	if (conType != t->conType || getNums() != t->getNums()) 
		return false;
	return getPoints() > t->getPoints();
}


bool ConsecutiveCards::isSameType(const CardTypeMap &m, int i, const string &s) {
	if (m.size() < i)
		return false;
	auto it = m.begin();
	int pre = it->second->getPoints();
	it++;
	int cur;
	for (; it != m.end(); it++) {
		if (it->second->getBasicType() != s)
			return false;
		cur = it->second->getPoints();
		if (cur != pre + 1 || cur > 15)
			return false;
		pre = cur;
	}
	return true;
}


bool TripleWith::isSameType(const CardTypeMap &m, const string &s) {
	if (m.size() != 2)
		return false;
	auto it = m.begin();
	if (it->second->getBasicType() != TRIPLE)
		return false;
	it++;
	if (it->second->getBasicType() != s || it->second->getPoints() > 15)
		return false;
	return true;
}


bool QuadrupleWith::isSameType(const CardTypeMap &m, const string &s) {
	if (m.size() != 3)
		return false;
	auto it = m.begin();
	if (it->second->getBasicType() != QUADRUPLE)
		return false;
	it++;
	if (it->second->getBasicType() != s || it->second->getPoints() > 15)
		return false;
	it++;
	if (it->second->getBasicType() != s || it->second->getPoints() > 15)
		return false;
	return true;
}


bool PlaneWith::isSameType(const CardTypeMap &m, const string &s) {
	if (m.size() < 4)
		return false;
	auto mid = m.size() / 2;
	auto it = m.begin();
	int pre = it->first.first;
	it++;
	int cur;
	while (--mid) {
		cur = it->first.first;
		if (it->second->getBasicType() != TRIPLE)
			return false;
		if (cur != pre + 1 || cur > 15)
			return false;
		pre = cur;
		it++;
	}
	while (it != m.end()) {
		if (it->first.first > 15 || it->second->getBasicType() != s)
			return false;
		it++;
	}
	return true;
}


bool Rocket::isSameType(const CardTypeMap &m) {
	if (m.size() != 2)
		return false;
	auto it = m.begin();
	if (it->first.first != 16)
		return false;
	it++;
	if (it->first.first != 17)
		return false;
	return true;
}
