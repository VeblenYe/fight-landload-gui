#include "Player.h"
#include "Poker.h"
#include <algorithm>


bool compare(shared_ptr<Poker> lhs, shared_ptr<Poker> rhs) {
	return lhs->getPriority() > rhs->getPriority();
}


void Player::show() {
	for (auto i : hold)
		i->show();
}


void Player::addToHold(shared_ptr<Poker> p) {
	hold.push_back(p);
	p->setHolder(std::make_shared<Player>(*this));
}


void Player::addToHold(vector<shared_ptr<Poker>> &vec) {
	hold = vec;
	for (auto p : hold)
		p->setHolder(std::make_shared<Player>(*this));
}


void Player::removeFromHold(shared_ptr<Poker> p) {
	auto pos = std::find(hold.begin(), hold.end(), p);
	if (pos != hold.end()) {
		hold.erase(pos);
		p->setHolder(nullptr);
	}
}


void Player::addToTemp(shared_ptr<Poker> p) {
	temp.push_back(p);
	p->setHolder(std::make_shared<Player>(*this));
}


void Player::removeFromTemp(shared_ptr<Poker> p) {
	auto pos = std::find(temp.begin(), temp.end(), p);
	if (pos != temp.end()) {
		temp.erase(pos);
		p->setHolder(nullptr);
	}
}


// 重新分配牌的位置
void Player::reset() {
	if (hold.empty()) return;
	std::sort(hold.begin(), hold.end(), compare);
	int mid = hold.size() / 2;
	int midl = 315 + mid * 45;
	for (int i = 0; i < mid; i++)
		hold[i]->setPos(midl - (mid - i) * 45, 700);
	for (int i = mid; i < hold.size() - 1; i++)
		hold[i]->setPos(midl + (i - mid) * 45, 700);
}
