#pragma once

#include "Poker.h"
#include "Player.h"


// ∂¡»Î∆ÀøÀ≈∆
vector<shared_ptr<Poker>> readIn(Window *window);


// ∑¢≈∆
void deal(vector<shared_ptr<Poker>> vec, Player *p1, Player *p2, Player *p3);

