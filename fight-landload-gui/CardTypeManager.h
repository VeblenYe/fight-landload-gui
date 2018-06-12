#pragma once


#include "CardTypeMap.h"
#include "CardTypeString.h"


// 更新基础牌型信息
void add(int p, CardTypeMap &m);


void remove(int p, CardTypeMap &m);


// 判断牌型和是否可以出牌
std::pair<string, bool> drawJudgement(CardTypeMap &lhs, CardTypeMap &rhs);
