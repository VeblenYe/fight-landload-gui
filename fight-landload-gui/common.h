#pragma once


#include <SDL.h>
#include <algorithm>


bool isInArea(SDL_Rect *box) {
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);
	if ((x >= box->x) && (x <= box->x + box->w)
		&& (y >= box->y) && (y <= box->y + box->h))
		return true;
	return false;
}


bool isInArea(SDL_Rect *box,  int x, int y) {
	if ((x > box->x) && (x < box->x + box->w)
		&& (y > box->y) && (y < box->y + box->h))
		return true;
	return false;
}


/* 两个矩形相交，其中心点连线的距离小于等于两个矩形边长和的一半*/
bool hasIntersection(SDL_Rect *r1, SDL_Rect *r2) {
	
	int x = std::abs(r1->w) + std::abs(r2->w);
	int y = std::abs(r1->h) + std::abs(r2->h);
	SDL_Point z1 = { r1->x + r1->w / 2, r1->y + r1->h / 2 };
	SDL_Point z2 = { r2->x + r2->w / 2, r2->y + r2->h / 2 };
	int zx = std::abs(z1.x - z2.x);
	int zy = std::abs(z1.y - z2.y);
	if (zx <= x / 2 && zy <= y / 2)
		return true;
	else
		return false;
}

