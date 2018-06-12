#include "Table.h"
#include "deal.h"
#include "Window.h"
#include "Poker.h"
#include <algorithm>


Table::Table(Window *window) : Widget(window, 0, 0, 0, 0, 1) {
	init();
}


void Table::show() {
	curPlayer->show();
	for (auto p : temp)
		p->show();
}


void Table::registered(int type) {
	if (!findEvent(type)) {
		addEvent(type);
		EventManager::instance().AddEventHandler(type, { handler });
	}
}


void Table::unregister() {
	for (auto type : getEvents())
		EventManager::instance().RemoveEventHandler(type, { handler });
}


void Table::updateMap() {
	for (auto p : temp)
		add(p->getNum(), m);
}


void Table::addButton(std::shared_ptr<Button> button) {
	button->addToWindow();
	button->setState(0);
}


void Table::removeButton(std::shared_ptr<Button> button) {
	button->setState(-1);
	button->removeFromWindow();
}


void Table::clearTemp() {
	for (auto p : temp) {
		delete p;
		//std::cout << "删除扑克" << std::endl;
	}
	m.clear();
	temp.clear();
}


inline
bool compare1(Poker *lhs, Poker *rhs) {
	return lhs->getPriority() > rhs->getPriority();
}


void Table::setTempPos() {
	if (temp.empty()) return;
	std::sort(temp.begin(), temp.end(), compare1);
	int mid = temp.size() / 2;
	int midl = (1600 - 45 * (temp.size() - 1) - 105) / 2 + mid * 45;
	for (int i = 0; i < mid; i++)
		temp[i]->setPos(midl - (mid - i) * 45, 300);
	for (int i = mid; i < temp.size(); i++)
		temp[i]->setPos(midl + (i - mid) * 45, 300);
}


void Table::draw() {
	// 复制临时牌组
	temp = curPlayer->getTemp();
	m.clear();
	updateMap();
	curPlayer->removeFromHold(temp);
	curPlayer->resetPos();
	setTempPos();
}


void Table::resetPlayerPos() {
	p1->resetPos();
	p2->resetPos();
	p3->resetPos();
}


bool Table::drawOrNot(CardTypeMap &temp) {
	auto res = drawJudgement(m, temp);
	if (res.second) {
		curType = res.first;
		clearTemp();
	}
	return res.second;
}


bool Table::winner() const {
	if (p1->isEmpty())
		return true;
	if (p2->isEmpty())
		return true;
	if (p3->isEmpty())
		return true;
	return false;
}


std::pair<int, int> Table::handle(SDL_Event *e) {

	// 开始按钮被按下
	if (startButton->getState() == 1) {
		// 将开始按钮状态置无效
		startButton->setState(-1);

		// 移除开始按钮
		removeButton(startButton);
		
		
		// 发牌
		auto vec = readIn(getWindow());
		deal(vec, p1.get(), p2.get(), p3.get());
		resetPlayerPos();
		p1->setPokerState(1);
		p2->setPokerState(-1);
		p3->setPokerState(-1);
		curPlayer = p1;

		// 添加出牌和过牌按钮，不知道为啥这里要手动，事件注册出问题，已解决
		// 因为之前都是用make_shared<>()新生成处理函数，所以每个函数不同，导致注册和移除出现问题
		addButton(drawButton);
		addButton(checkButton);
		checkButton->setState(-1);

		// 直接返回
		return { 1, 0 };
	}


	// 出牌按钮被按下
	if (drawButton->getState() == 1) {
		drawButton->setState(0);
		
		if (drawOrNot(curPlayer->getCardTypeMapTemp())) {
			draw();
			checkButton->setState(0);
			flag = 1;
			if (curPlayer == p1) {
				curPlayer = p2;
				p1->setPokerState(-1);
				p2->setPokerState(1);
				p3->setPokerState(-1);
				resetPlayerPos();
			}
			else if (curPlayer == p2) {
				curPlayer = p3;
				p1->setPokerState(-1);
				p2->setPokerState(-1);
				p3->setPokerState(1);
				resetPlayerPos();
			}
			else {
				curPlayer = p1;
				p1->setPokerState(1);
				p2->setPokerState(-1);
				p3->setPokerState(-1);
				resetPlayerPos();
			}
			if (winner()) {
				removeButton(drawButton);
				removeButton(checkButton);
				addButton(endButton);
				clearTemp();
				curType = INVALIDCARDTYPE;
				p1->clear();
				p2->clear();
				p3->clear();
			}
		}
		else
			std::cout << "不能出牌" << std::endl;
	}

	// 过牌按钮被按下
	if (checkButton->getState() == 1) {
		checkButton->setState(0);
		if (flag == 2) {
			flag = 1;
			clearTemp();
			checkButton->setState(-1);
		}
		else 
			drawButton->setState(0);

		if (curPlayer == p1) {
			curPlayer = p2;
			flag++;
			p1->clearTemp();
			p1->setPokerState(-1);
			p2->setPokerState(1);
			p3->setPokerState(-1);
			resetPlayerPos();
		}
		else if (curPlayer == p2) {
			curPlayer = p3;
			flag++;
			p2->clearTemp();
			p1->setPokerState(-1);
			p2->setPokerState(-1);
			p3->setPokerState(1);
			resetPlayerPos();
		}
		else {
			curPlayer = p1;
			flag++;
			p3->clearTemp();
			p1->setPokerState(1);
			p2->setPokerState(-1);
			p3->setPokerState(-1);
			resetPlayerPos();
		}
	}

	// 结束游戏按钮被按下
	if (endButton->getState() == 1) {
		removeButton(endButton);
		addButton(startButton);
		startButton->setState(0);
	}

	return { 0, 0 };
}

/*

CardTypeMap::const_iterator Find(std::shared_ptr<Player> p, int point, int i) {
	while (i <= 4) {
		auto it = p->getCardTypeMap().upper_bound({ point, i });
		if (it != p->getCardTypeMap().end() && it->first.second == i) {
			helper(p, it->first);
			return it;
		}
		i++;
	}
	p->clearTemp();
	return p->getCardTypeMap().end();
}

void helper(std::shared_ptr<Player> p, std::pair<int, int> q) {
	for (auto it = p->getHold().rbegin(); it != p->getHold().rend(); it++) {
		if ((*it)->getNum() == q.first)
			while (q.second--)
				p->addToTemp(*it++);
	}
}

void helper(std::shared_ptr<Player> p, vector<Poker *> &vec, std::pair<int, int> q) {
	for (auto it = p->getHold().rbegin(); it != p->getHold().rend(); it++) {
		if ((*it)->getNum() == q.first)
			while (q.second--)
				vec.push_back(*it++);
	}
}

CardTypeMap::const_iterator Find1(std::shared_ptr<Player> p, int point, int size, int num) {
	if ((point + size) == 15)
		return p->getCardTypeMap().end();
	vector<Poker *> temp;
	int var = point;
	for (int j = 1; j <= size && (var + j) <= 15;) {
		for (int i = num; i < 5; i++) {
			auto it = p->getCardTypeMap().find({ var + j, i });
			if (it != p->getCardTypeMap().end()) {
				j++;
				helper(p, temp, { var + j, num });
				if (j == size) {
					p->addToTemp(temp);
					return it;
				}
				break;
			}
			// 如果最后没有找到，就清空临时牌组，并从下一个数开始找
			if (i == 4) {
				temp.clear();
				p->clearTemp();
				var = var + j + 1;
			}
		}
	}
	p->clearTemp();
	return p->getCardTypeMap().end();
}

// 点数 主牌型牌数 副牌型牌数 副牌性对数
CardTypeMap::const_iterator Find2(std::shared_ptr<Player> p, int point, int i, int num, int pairNum) {
	auto res = Find(p, point, i);
	if (res != p->getCardTypeMap().end()) {
		CardTypeMap::const_iterator it, flag;
		while (pairNum--) {
			for (int j = num; j < 5; j++) {
				// 这段代码意思是，如果只找一个副牌型，则从最小开始找，如果多于一个，则要从上一次找到的副牌型开始找
				if (pairNum == 0)
					it = p->getCardTypeMap().lower_bound({ 3, j });
				else
					it = p->getCardTypeMap().upper_bound({ flag->first.first, j });

				if (it == res)
					// 如果找的的副牌性和主牌型相同，则找大于主牌型的副牌型
					it = p->getCardTypeMap().upper_bound({ res->first.first, j });

				if (it != p->getCardTypeMap().end() && it->first.first < 16 && it->first.second == j) {
					helper(p, { it->first.first, num });
					flag = it;
					if (pairNum == 0)
						return res;
					break;
				}
				if (j == 4) {
					p->clearTemp();	// 如果没找到能用的单张牌，清空临时牌堆
					return p->getCardTypeMap().end();
				}
			}
		}
	}
	p->clearTemp();
	return p->getCardTypeMap().end();
}


CardTypeMap::const_iterator Find3(std::shared_ptr<Player>p, int point, int size, int num, int pairNum) {
	if ((point + size) == 16)
		return p->getCardTypeMap().end();
	CardTypeMap::const_iterator it1, it2;
	for (int i = 1; (i + point + 1) < 15; i++) {
		it1 = Find(p, point + i, 3);
		it2 = Find(p, point + 1 + i, 3);
		if (it2->first.first == it1->first.first + 1)
			break;
	}
}


bool Table::prompt(std::shared_ptr<Player> p) {
	// 如果是火箭直接返回
	if (curType == ROCKET)
		return false;

	int point = m.begin()->first.first;	// 基础牌就是牌点数，组合牌是主牌型点数
	int size = m.begin()->first.second;	// 基础牌就是牌张数，组合牌是基础牌个数
	// 一一对应查找牌型，蠢得我都写不下去，下面的代码侮辱智商，谨慎观看！！
	// 改的有点不侮辱了
	if (curType == SINGLE) {
		return Find(p, point, 1) == p->getCardTypeMap().end();
	}
	if (curType == DOUBLE) {
		return Find(p, point, 2) == p->getCardTypeMap().end();;
	}
	if (curType == TRIPLE) {
		return Find(p, point, 3) == p->getCardTypeMap().end();;
	}
	if (curType == QUADRUPLE) {
		return Find(p, point, 4) == p->getCardTypeMap().end();;
	}
	if (curType == SINGLECON) {
		return Find1(p, point, size, 1) == p->getCardTypeMap().end();;
	}
	if (curType == DOUBLECON) {
		return Find1(p, point, size, 2) == p->getCardTypeMap().end();;
	}
	if (curType == TRIPLECON) {
		return Find1(p, point, size, 3) == p->getCardTypeMap().end();;
	}
	if (curType == TRIPLEWITHSINGLE) {
		return Find2(p, point, 3, 1, 1) == p->getCardTypeMap().end();
	}
	if (curType == TRIPLEWITHDOUBLE) {
		return Find2(p, point, 3, 2, 1) == p->getCardTypeMap().end();
	}
	if (curType == QUARDRUPLEWITHSINGLE) {
		return Find2(p, point, 4, 1, 2) == p->getCardTypeMap().end();
	}
	if (curType == QUARDRUPLEWITHDOUBLE) {
		return Find2(p, point, 3, 2, 2) == p->getCardTypeMap().end();
	}
	if (curType == PLANEWITHSINGLE) {
		return Find3(p, point, 2, 1, 2) == p->getCardTypeMap().end();
	}
	if (curType == PLANEWITHDOUBLE) {
		return Find3(p, point, 2, 2, 2) == p->getCardTypeMap().end();
	}

	// 查找玩家手牌是否有火箭
	auto it = p->getHold().begin();
	if ((*it)->getNum() == 17 && (*(it + 1))->getNum == 16) {
		p->addToTemp((*it));
		p->addToTemp(* (it + 1));
		return true;
	}

	return false;
}
*/

Table::~Table() { unregister(); }


void Table::init() {
	startButton = std::make_shared<Button>(getWindow(), 650, 550, 300, 100);
	startButton->loadButtonImage("res/start.jpg");
	startButton->setClip(67, 40, 645, 275);
	startButton->registered(SDL_MOUSEBUTTONDOWN);
	startButton->registered(SDL_MOUSEBUTTONUP);
	addButton(startButton);

	drawButton = std::make_shared<Button>(getWindow(), 600, 575, 150, 50);
	drawButton->loadButtonImage("res/draw.jpg");
	drawButton->registered(SDL_MOUSEBUTTONDOWN);
	drawButton->registered(SDL_MOUSEBUTTONUP);
	drawButton->setClip(67, 40, 645, 275);

	checkButton = std::make_shared<Button>(getWindow(), 850, 575, 150, 50);
	checkButton->loadButtonImage("res/check.jpg");
	checkButton->registered(SDL_MOUSEBUTTONDOWN);
	checkButton->registered(SDL_MOUSEBUTTONUP);
	checkButton->setClip(67, 40, 645, 275);

	endButton = std::make_shared<Button>(getWindow(), 650, 550, 300, 100);
	endButton->loadButtonImage("res/end.jpg");
	endButton->registered(SDL_MOUSEBUTTONDOWN);
	endButton->registered(SDL_MOUSEBUTTONUP);
	endButton->setClip(67, 40, 645, 275);

	p1 = std::make_shared<Player>();
	p2 = std::make_shared<Player>();
	p3 = std::make_shared<Player>();
	curPlayer = p1;

	registered(SDL_MOUSEBUTTONUP);
}
