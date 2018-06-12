#include "Player.h"
#include "Poker.h"
#include <algorithm>
#include "CardTypeManager.h"
#include <iostream>


bool compare(Poker *lhs, Poker *rhs) {
	return lhs->getPriority() > rhs->getPriority();
}


void Player::setPokerState(int i) {
	for (auto p : hold)
		p->setState(i);
}


void Player::show() {
	for (auto i : hold)
		i->show();
}


void Player::addToHold(Poker *p) {
	hold.push_back(p);
	add(p->getNum(), m);
	p->setHolder(shared_from_this());
}


void Player::addToHold(vector<Poker *> &vec) {
	hold = vec;
	for (auto p : hold) {
		add(p->getNum(), m);
		p->setHolder(shared_from_this());
	}
}


void Player::removeFromHold(Poker *p) {
	auto pos = std::find(hold.begin(), hold.end(), p);
	if (pos != hold.end()) {
		p->unregister();
		hold.erase(pos);
		std::sort(hold.begin(), hold.end());
		removeFromTemp(p);
		remove(p->getNum(), m);
		//std::cout << "移出手牌" << std::endl;
	}
}


void Player::removeFromHold(vector<Poker *> &vec) {
	for (auto p : vec)
		removeFromHold(p);
}


void Player::addToTemp(Poker *p) {
	temp.push_back(p);
	add(p->getNum(), t);
	std::cout << "已添加临时手牌" << t.size() << std::endl;
}


void Player::addToTemp(vector<Poker *> &vec) {
	for (auto p : vec)
		addToTemp(p);
}


void Player::removeFromTemp(Poker *p) {
	auto pos = std::find(temp.begin(), temp.end(), p);
	if (pos != temp.end()) {
		temp.erase(pos);
		remove(p->getNum(), t);
		std::cout << "已移出临时手牌" << t.size() << std::endl;
	}
}


void Player::clearTemp() {
	for (auto p : temp) {
		removeFromTemp(p);
	}
	temp.clear();
}


void Player::clearHold() {
	for (auto p : hold) {
		p->unregister();
		delete p;
	}
	hold.clear();
}


// 重新分配牌的位置
void Player::resetPos() {
	if (hold.empty()) return;
	std::sort(hold.begin(), hold.end(), compare);
	int mid = hold.size() / 2;
	int midl = (1600 - 45 * (hold.size() - 1) - 105) / 2 + mid * 45;
	for (int i = 0; i < mid; i++)
		hold[i]->setPos(midl - (mid - i) * 45, 700);
	for (int i = mid; i < hold.size(); i++)
		hold[i]->setPos(midl + (i - mid) * 45, 700);
}
