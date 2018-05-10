#pragma once


#include <vector>
#include "Window.h"
#include "EventManager.h"
#include "Player.h"


using std::vector;

// ��ʼ���������
int initialize(Window *window);

// �����˿���
vector<Poker *> readIn(Window *window);

// ����
void deal(vector<Poker *> vec , Player *p1, Player *p2, Player *p3);

