#pragma once


#include <SDL.h>


// ��ǰ����Ƿ��ھ�����
bool isInArea(const SDL_Rect &box);


// ���������Ƿ��ھ�����
bool isInArea(const SDL_Rect &box, int x, int y);



/* ���������ཻ�������ĵ����ߵľ���С�ڵ����������α߳��͵�һ��*/
bool hasIntersection(const SDL_Rect &r1, const SDL_Rect &r2);
