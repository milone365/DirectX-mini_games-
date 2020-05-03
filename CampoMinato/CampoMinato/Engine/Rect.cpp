#include "Rect.h"

Rect::Rect(float l_in, float r_in, float t_in, float b_in)
{
	left = l_in, right = r_in, top = t_in, bottom = b_in;
}

Rect::Rect(const Vector2 & topLeft, const Vector2 & bottomRight)
{
	Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y);
}

Rect::Rect(const Vector2 & topLeft, float width, float height)
{
	Rect(topLeft, topLeft + Vector2(width, height));
}

bool Rect::isOverlapedWidth(const Rect & other) const
{
	return right > other.left&&left<other.right&&
		bottom>other.top&&top < other.bottom;
}

bool Rect::isConteinedBy(const Rect & other) const
{
	return left >= other.left&&right <= other.right&&
		top >= other.top&&bottom <= other.bottom;
}

bool Rect::contains(const Vector2 & vec) const
{
	return vec.x >= left && vec.x <= right && vec.y >= top && vec.y <= bottom;
}

Rect Rect::fromCenter(const Vector2 & center, float halfWidth, float halfHeight)
{
	const Vector2 half(halfWidth, halfHeight);
	return Rect(center-half,center+half);
}

Rect Rect::getExpanded(float offset) const
{
	return Rect(left-offset,right+offset,top-offset,bottom+offset);
}

Vector2 Rect::getCenter() const
{
	return Vector2((left+right)/2,(top+bottom)/2);
}
