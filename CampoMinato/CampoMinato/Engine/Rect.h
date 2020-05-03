#pragma once
#include "Vector2.h"

class Rect
{
public:
	Rect()=default;
	Rect(float l_in, float r_in, float t_in, float b_in);
	Rect(const Vector2& topLeft, const Vector2& bottomRight);
	Rect(const Vector2& topLeft, float width, float height);
	bool isOverlapedWidth(const Rect& other)const;
	bool isConteinedBy(const Rect& other)const;
	bool contains(const Vector2& vec)const;
	static Rect fromCenter(const Vector2& center, float halfWidth, float halfHeight);
	Rect getExpanded(float offset)const;
	Vector2 getCenter()const;
public :
	int left, right, top, bottom;
};

