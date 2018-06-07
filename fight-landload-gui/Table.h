#pragma once


#include "Widget.h"
#include "CardTypeManager.h"
#include "GameItemfwd.h"
#include "Buttonfwd.h"
#include <vector>


class Table : public Widget {
public:
	Table(Window *window);

	void show() const override;

	std::pair<int, int> handle(SDL_Event *e) override;

	void registered(int type) {
		handler = std::make_shared<ClassEventHandler<Table>>(this, &Table::handle, getPriority());
		EventManager::instance().AddEventHandler(type, { handler });
	}

	void addToWindow() const;

	void removeFromWindow() const;

	void clear() { m.clear(); }

	const std::string &getType() const { return curType; }

	void judgeType() { curType = typeJudgement(m); }

	~Table();
private:
	CardTypeMap m;
	std::string curType;
	std::vector<std::shared_ptr<Poker>> temp;

	void init();

	std::shared_ptr<StartButton> startButton;
	std::shared_ptr<DrawButton> drawButton;
	std::shared_ptr<CheckButton> checkButton;
	std::shared_ptr<EndButton> endButton;

	std::shared_ptr<Player> p1;
	std::shared_ptr<Player> p2;
	std::shared_ptr<Player> p3;

	std::shared_ptr<ClassEventHandler<Table>> handler;
};
