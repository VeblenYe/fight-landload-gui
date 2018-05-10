#pragma once


#include <vector>
#include "Window.h"
#include "EventManager.h"
#include "Player.h"


using std::vector;

// 初始化所有组件
int initialize(Window *window);

// 读入扑克牌
vector<Poker *> readIn(Window *window);

// 发牌
void deal(vector<Poker *> vec , Player *p1, Player *p2, Player *p3);

