#pragma once


#include "CardTypeString.h"
#include "CardTypeMap.h"
#include "CardTypefwd.h"
#include <iostream>


class CardType {
public:
	CardType() = default;

	CardType(int p, int n, const string &t) : points(p), nums(n), type(t) {}
	
	const string &getType() const {
		return type;
	}

	void setType(const string &s) {
		type = s;
	}

	int getPoints() const {
		return points;
	}

	void setPoints(int i) {
		points = i;
	}

	int getNums() const {
		return nums;
	}

	void setNums(int i) {
		nums = i;
	}

	virtual ~CardType() {}
private:
	string type;	// 牌型
	int points;		// 基础牌型就是点数，组合牌型是主牌型点数
	int nums;		// 基础牌型就是牌张数，组合牌型是基础牌型个数
};


// 基础牌型基类
class BasicCardType : public CardType {
public:
	explicit BasicCardType(int p, int n, const string &t) : CardType(p, n, BASICCARDTYPE), basicType(t) {}

	const string &getBasicType() const {
		return basicType;
	}

	void setBasicType(const string &s) {
		basicType = s;
	}

	bool bigger(BasicCardType *t) const;

	bool bigger(CombinationCardType *t) const;

	virtual ~BasicCardType() {}
private:
	string basicType;
};


// 单牌
class Single : public BasicCardType {
public:
	explicit Single(int p) : BasicCardType(p, 1, SINGLE) {}
	static bool isSameType(BasicCardType *t) {
		return t->getBasicType() == SINGLE;
	}
};


// 对子
class Double : public BasicCardType {
public:
	explicit Double(int p) : BasicCardType(p, 2, DOUBLE) {}
	static bool isSameType(BasicCardType *t) {
		return t->getBasicType() == DOUBLE;
	}
};


// 三牌
class Triple : public BasicCardType {
public:
	explicit Triple(int p) : BasicCardType(p, 3, TRIPLE) {}
	static bool isSameType(BasicCardType *t) {
		return t->getBasicType() == TRIPLE;
	}
};


// 炸弹
class Quadruple :public BasicCardType {
public:
	explicit Quadruple(int p) : BasicCardType(p, 4, QUADRUPLE) {}
	static bool isSameType(BasicCardType *t) {
		return t->getBasicType() == QUADRUPLE;
	}
};


/*-----------------------------------------------------------------------------------------------------*/


// 组合牌型基类
class CombinationCardType : public CardType {
public:
	CombinationCardType(const CardTypeMap &m, const string &c) : conType(c) {
		int min;
		if (m.empty())
			min = 0;
		else
			min = m.begin()->first.first;
		CardType::setPoints(min);
		CardType::setNums(m.size());
		CardType::setType(COMBINATIONCARDTYPE);
	}

	const string &getConType() const {
		return conType;
	}

	void setContype(const string &s) {
		conType = s;
	}

	bool bigger(BasicCardType *t) const;

	bool bigger(CombinationCardType *t) const;

	virtual ~CombinationCardType() {}
private:
	string conType;		// 组合牌型
};


// 顺子
class ConsecutiveCards : public CombinationCardType {
public:
	ConsecutiveCards(const CardTypeMap &m, const string &c) : 
		CombinationCardType(m, c) {}

	static bool isSameType(const CardTypeMap &m, int i, const string &s);

	virtual ~ConsecutiveCards() {}
};


// 单顺
class SingleCon : public ConsecutiveCards {
public:
	SingleCon(const CardTypeMap &m) : ConsecutiveCards(m, SINGLECON) {}

	static bool isSameType(const CardTypeMap &m) {
		return ConsecutiveCards::isSameType(m, 5, SINGLE);
	}
};


// 双顺
class DoubleCon : public ConsecutiveCards {
public:
	DoubleCon(const CardTypeMap &m) : ConsecutiveCards(m, DOUBLECON) {}
	static bool isSameType(const CardTypeMap &m) {
		return ConsecutiveCards::isSameType(m, 3, DOUBLE);
	}
};


// 三顺
class TripleCon : public ConsecutiveCards {
public:
	TripleCon(const CardTypeMap &m) : ConsecutiveCards(m, TRIPLECON) {}
	static bool isSameType(const CardTypeMap &m) {
		return ConsecutiveCards::isSameType(m, 2, TRIPLE);
	}
};


// 三带
class TripleWith : public CombinationCardType {
public:
	TripleWith(const CardTypeMap &m, const string &c) : CombinationCardType(m, c) {}
	static bool isSameType(const CardTypeMap &m, const string &s);
	virtual ~TripleWith() {}
};


// 三带一
class TripleWithSingle : public TripleWith {
public:
	TripleWithSingle(const CardTypeMap &m) : TripleWith(m, TRIPLEWITHSINGLE) {}
	static bool isSameType(const CardTypeMap &m) {
		return TripleWith::isSameType(m, SINGLE);
	}
};


// 三带二
class TripleWithDouble : public TripleWith {
public:
	TripleWithDouble(const CardTypeMap &m) : TripleWith(m, TRIPLEWITHDOUBLE) {}
	static bool isSameType(const CardTypeMap &m) {
		return TripleWith::isSameType(m, DOUBLE);
	}
};


// 四带
class QuadrupleWith : public CombinationCardType {
public:
	QuadrupleWith(const CardTypeMap &m, const string &c) : CombinationCardType(m, c) {}
	static bool isSameType(const CardTypeMap &m, const string &s);
	virtual ~QuadrupleWith() {}
};


// 四带一
class QuadrupleWithSingle : public QuadrupleWith {
public:
	QuadrupleWithSingle(const CardTypeMap &m) : QuadrupleWith(m, QUARDRUPLEWITHSINGLE) {}
	static bool isSameType(const CardTypeMap &m) {
		return QuadrupleWith::isSameType(m, SINGLE);
	}
};


// 四带二
class QuadrupleWithDouble : public QuadrupleWith {
public:
	QuadrupleWithDouble(const CardTypeMap &m) : QuadrupleWith(m, QUARDRUPLEWITHDOUBLE) {}
	static bool isSameType(const CardTypeMap &m) {
		return QuadrupleWith::isSameType(m, DOUBLE);
	}
};


// 飞机
class PlaneWith : public CombinationCardType {
public:
	PlaneWith(const CardTypeMap &m, const string &c) : CombinationCardType(m, c) {}

	static bool isSameType(const CardTypeMap &m, const string &s);

	virtual ~PlaneWith() {}
};


// 飞机带单
class PlaneWithSingle : public PlaneWith {
public:
	PlaneWithSingle(const CardTypeMap &m) : PlaneWith(m, PLANEWITHSINGLE) {}
	static bool isSameType(const CardTypeMap &m) {
		return PlaneWith::isSameType(m, SINGLE);
	}
};


// 飞机带对
class PlaneWithDouble : public PlaneWith {
public:
	PlaneWithDouble(const CardTypeMap &m) : PlaneWith(m, PLANEWITHDOUBLE) {}
	static bool isSameType(const CardTypeMap &m) {
		return PlaneWith::isSameType(m, DOUBLE);
	}
};


// 火箭
class Rocket : public CombinationCardType {
public:
	Rocket(const CardTypeMap &m) : CombinationCardType(m, ROCKET) {}
	static bool isSameType(const CardTypeMap &m);
};
