#pragma once


#include <vector>
#include <memory>
#include "Window.h"
#include "EventManager.h"
#include "Player.h"


using std::vector;
using std::shared_ptr;

// ��ʼ���������
int initialize(Window *window);

// �����˿���
vector<shared_ptr<Poker>> readIn(Window *window);

// ����
void deal(vector<shared_ptr<Poker>> vec , Player *p1, Player *p2, Player *p3);

