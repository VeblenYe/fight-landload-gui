#pragma once


#include "CardTypeMap.h"
#include "CardTypeString.h"


// ���»���������Ϣ
void add(int p, CardTypeMap &m);


void remove(int p, CardTypeMap &m);


// �ж����ͺ��Ƿ���Գ���
std::pair<string, bool> drawJudgement(CardTypeMap &lhs, CardTypeMap &rhs);
