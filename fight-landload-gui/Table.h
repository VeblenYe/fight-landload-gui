#pragma once


#include "Widget.h"
#include "CardTypeManager.h"
#include "GameItemfwd.h"
#include "GUIfwd.h"
#include <vector>


class Table : public Widget {
public:
	Table(Window *window);

	void show() override;

	std::pair<int, int> handle(SDL_Event *e);

	void registered(int type);

	void unregister();

	void addButton(std::shared_ptr<Button> button);

	void removeButton(std::shared_ptr<Button> button);

	void updateMap();

	void clear() { m.clear(); }

	void clearTemp();

	const std::string &getType() const { return curType; }

	bool drawOrNot(CardTypeMap &temp);

	void draw();

	bool winner() const;

	void resetPlayerPos();

	// 从给定的玩家手牌中找出比当前牌型大的牌
	bool prompt(std::shared_ptr<Player> p);

	~Table();
private:
	CardTypeMap m;
	std::string curType = INVALIDCARDTYPE;
	std::vector<Poker *> temp;

	void init();

	void setTempPos();

	int flag = 0;

	std::shared_ptr<Button> startButton;
	std::shared_ptr<Button> drawButton;
	std::shared_ptr<Button> checkButton;
	std::shared_ptr<Button> endButton;

	std::shared_ptr<Player> curPlayer;
	std::shared_ptr<Player> p1;
	std::shared_ptr<Player> p2;
	std::shared_ptr<Player> p3;

	std::shared_ptr<ClassEventHandler<Table>> handler =
		std::make_shared<ClassEventHandler<Table>>(this, &Table::handle, getPriority());
};
