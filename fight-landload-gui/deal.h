#pragma once

#include "Poker.h"
#include "Player.h"


// �����˿���
vector<Poker *> readIn(Window *window);


// ����
void deal(vector<Poker *> vec, Player *p1, Player *p2, Player *p3);
