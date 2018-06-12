#include "CardTypeManager.h"
#include "CardType.h"
#include <iostream>
#include <algorithm>


void add(int p, CardTypeMap &m) {
	auto pos = m.find(std::make_pair(p, 3));
	if (pos != m.end()) {
		m.erase(pos);
		m.insert_or_assign(std::make_pair(p, 4), std::make_shared<BasicCardType>(Quadruple(p)));
		return;
	}
	pos = m.find(std::make_pair(p, 2));
	if (pos != m.end()) {
		m.erase(pos);
		m.insert_or_assign(std::make_pair(p, 3), std::make_shared<BasicCardType>(Triple(p)));
		return;
	}
	pos = m.find(std::make_pair(p, 1));
	if (pos != m.end()) {
		m.erase(pos);
		m.insert_or_assign(std::make_pair(p, 2), std::make_shared<BasicCardType>(Double(p)));
		return;
	}
	m[std::make_pair(p, 1)] = std::make_shared<BasicCardType>(Single(p));
}


void remove(int p, CardTypeMap &m) {
	auto pos = m.find(std::make_pair(p, 4));
	if (pos != m.end()) {
		m.erase(pos);
		m.insert_or_assign(std::make_pair(p, 3), std::make_shared<BasicCardType>(Triple(p)));
		return;
	}
	pos = m.find(std::make_pair(p, 3));
	if (pos != m.end()) {
		m.erase(pos);
		m.insert_or_assign(std::make_pair(p, 2), std::make_shared<BasicCardType>(Double(p)));
		return;
	}
	pos = m.find(std::make_pair(p, 2));
	if (pos != m.end()) {
		m.erase(pos);
		m.insert_or_assign(std::make_pair(p, 1), std::make_shared<BasicCardType>(Single(p)));
		return;
	}
	pos = m.find(std::make_pair(p, 1));
	if (pos != m.end()) {
		m.erase(pos);
		return;
	}
	return;
}


std::pair<string, bool> drawJudgement(CardTypeMap &lhs, CardTypeMap &rhs) {
	
	std::string s1;
	std::shared_ptr<BasicCardType> b1 = nullptr;
	std::shared_ptr<CombinationCardType> c1 = nullptr;
	if (!lhs.empty()) {
		auto point = lhs.begin()->first.first;
		auto t1 = lhs.begin()->second;
		if (t1->getBasicType() == SINGLE) {
			if (lhs.size() == 1) {
				s1 = SINGLE;
				b1 = std::make_shared<Single>(point);
			}
			else if (SingleCon::isSameType(lhs)) {
				s1 = SINGLECON;
				c1 = std::make_shared<SingleCon>(lhs);
			}
			else if (Rocket::isSameType(lhs)) {
				s1 = ROCKET;
				c1 = std::make_shared<Rocket>(lhs);
			}
			else
				s1 = INVALIDCARDTYPE;
		}
		else if (t1->getBasicType() == DOUBLE) {
			if (lhs.size() == 1) {
				s1 = DOUBLE;
				b1 = std::make_shared<Double>(point);
			}
			else if (DoubleCon::isSameType(lhs)) {
				s1 = DOUBLECON;
				c1 = std::make_shared<DoubleCon>(lhs);
			}
			else
				s1 = INVALIDCARDTYPE;
		}
		else if (t1->getBasicType() == TRIPLE) {
			if (lhs.size() == 1) {
				s1 = TRIPLE;
				b1 = std::make_shared<Triple>(point);
			}
			else if (TripleCon::isSameType(lhs)) {
				s1 = TRIPLECON;
				c1 = std::make_shared<TripleCon>(lhs);
			}
			else if (TripleWithSingle::isSameType(lhs)) {
				s1 = TRIPLEWITHSINGLE;
				c1 = std::make_shared<TripleWithSingle>(lhs);
			}
			else if (TripleWithDouble::isSameType(lhs)) {
				s1 = TRIPLEWITHDOUBLE;
				c1 = std::make_shared<TripleWithDouble>(lhs);
			}
			else if (PlaneWithSingle::isSameType(lhs)) {
				s1 = PLANEWITHSINGLE;
				c1 = std::make_shared<PlaneWithSingle>(lhs);
			}
			else if (PlaneWithDouble::isSameType(lhs)) {
				s1 = PLANEWITHDOUBLE;
				c1 = std::make_shared<PlaneWithDouble>(lhs);
			}
			else
				s1 = INVALIDCARDTYPE;
		}
		else if (t1->getBasicType() == QUADRUPLE) {
			if (lhs.size() == 1) {
				s1 = QUADRUPLE;
				b1 = std::make_shared<Quadruple>(point);
			}
			else if (QuadrupleWithSingle::isSameType(lhs)) {
				s1 = QUARDRUPLEWITHSINGLE;
				c1 = std::make_shared<QuadrupleWithSingle>(lhs);
			}
			else if (QuadrupleWithDouble::isSameType(lhs)) {
				s1 = QUARDRUPLEWITHDOUBLE;
				c1 = std::make_shared<QuadrupleWithSingle>(lhs);
			}
			else
				s1 = INVALIDCARDTYPE;
		}
	}
	else s1 = INVALIDCARDTYPE;

	std::string s2;
	std::shared_ptr<BasicCardType> b2 = nullptr;
	std::shared_ptr<CombinationCardType> c2 = nullptr;
	if (!rhs.empty()) {
		auto point = rhs.begin()->first.first;
		auto t2 = rhs.begin()->second;
		if (t2->getBasicType() == SINGLE) {
			if (rhs.size() == 1) {
				s2 = SINGLE;
				b2 = std::make_shared<Single>(point);
			}
			else if (SingleCon::isSameType(rhs)) {
				s2 = SINGLECON;
				c2 = std::make_shared<SingleCon>(rhs);
			}
			else if (Rocket::isSameType(rhs)) {
				s2 = ROCKET;
				c2 = std::make_shared<Rocket>(rhs);
			}
			else
				s2 = INVALIDCARDTYPE;
		}
		else if (t2->getBasicType() == DOUBLE) {
			if (rhs.size() == 1) {
				s2 = DOUBLE;
				b2 = std::make_shared<Double>(point);
			}
			else if (DoubleCon::isSameType(rhs)) {
				s2 = DOUBLECON;
				c2 = std::make_shared<DoubleCon>(rhs);
			}
			else
				s2 = INVALIDCARDTYPE;
		}
		else if (t2->getBasicType() == TRIPLE) {
			if (rhs.size() == 1) {
				s2 = TRIPLE;
				b2 = std::make_shared<Triple>(point);
			}
			else if (TripleCon::isSameType(rhs)) {
				s2 = TRIPLECON;
				c2 = std::make_shared<TripleCon>(rhs);
			}
			else if (TripleWithSingle::isSameType(rhs)) {
				s2 = TRIPLEWITHSINGLE;
				c2 = std::make_shared<TripleWithSingle>(rhs);
			}
			else if (TripleWithDouble::isSameType(rhs)) {
				s2 = TRIPLEWITHDOUBLE;
				c2 = std::make_shared<TripleWithDouble>(rhs);
			}
			else if (PlaneWithSingle::isSameType(rhs)) {
				s2 = PLANEWITHSINGLE;
				c2 = std::make_shared<PlaneWithSingle>(rhs);
			}
			else if (PlaneWithDouble::isSameType(rhs)) {
				s2 = PLANEWITHDOUBLE;
				c2 = std::make_shared<PlaneWithDouble>(rhs);
			}
			else
				s2 = INVALIDCARDTYPE;
		}
		else if (t2->getBasicType() == QUADRUPLE) {
			if (rhs.size() == 1) {
				s2 = QUADRUPLE;
				b2 = std::make_shared<Quadruple>(point);
			}
			else if (QuadrupleWithSingle::isSameType(rhs)) {
				s2 = QUARDRUPLEWITHSINGLE;
				c2 = std::make_shared<QuadrupleWithSingle>(rhs);
			}
			else if (QuadrupleWithDouble::isSameType(rhs)) {
				s2 = QUARDRUPLEWITHDOUBLE;
				c2 = std::make_shared<QuadrupleWithSingle>(rhs);
			}
			else
				s2 = INVALIDCARDTYPE;
		}
	}
	else
		s2 = INVALIDCARDTYPE;

	std::cout << lhs.size() << std::endl;
	std::cout << rhs.size() << std::endl;
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	

	// 如果玩家牌非法，则直接返回牌桌牌，剩下情况玩家牌都是合法的
	if (s2 == INVALIDCARDTYPE)
		return { s1, false };

	// 如果牌桌上的牌非法，也就是没有牌，则玩家直接出牌
	if (s1 == INVALIDCARDTYPE)
		return { s2, true };

	if (b1) {
		if (b2) {
			if (b2->bigger(b1.get())) 
				return { s2, true };
			return { s1, false };
		}
		if (c2->bigger(b1.get()))
			return { s2, true };
		return { s1, false };
	}
	if (b2) {
		if (b2->bigger(c1.get()))
			return { s2, true };
		return { s1, false };
	}
	if (c2->bigger(c1.get()))
		return { s2, true };
	return { s1, false };
}
