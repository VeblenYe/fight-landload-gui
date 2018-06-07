#pragma once


#include <SDL.h>


// 当前鼠标是否在矩形内
bool isInArea(const SDL_Rect &box);


// 给定坐标是否在矩形里
bool isInArea(const SDL_Rect &box, int x, int y);



/* 两个矩形相交，其中心点连线的距离小于等于两个矩形边长和的一半*/
bool hasIntersection(const SDL_Rect &r1, const SDL_Rect &r2);
