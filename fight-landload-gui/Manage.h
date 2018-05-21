#pragma once


#include <vector>
#include <memory>
#include "Window.h"
#include "EventManager.h"
#include "Player.h"


using std::vector;
using std::shared_ptr;

// 初始化所有组件
int initialize(Window *window);

// 读入扑克牌
vector<shared_ptr<Poker>> readIn(Window *window);

// 发牌
void deal(vector<shared_ptr<Poker>> vec , Player *p1, Player *p2, Player *p3);

