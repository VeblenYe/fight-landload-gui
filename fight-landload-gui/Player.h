#pragma once

#include "Poker.h"

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class Player {
public:
	// ���е���
	vector<Poker *> hold;

	// �Ƿ��Ǳ������
	int local;
};
