#include "Vector2.h"
#include<cmath>

Vector2::Vector2(int in_x, int in_y)
{
	x = in_x;
	y = in_y;
}

Vector2 Vector2::operator+(const Vector2 & vec) const
{
	return Vector2(x+vec.x,y+vec.y);
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	return *this = *this + vec;
}

Vector2 Vector2::operator*(float value) const
{
	return Vector2(x *value, y *value);
}

Vector2 & Vector2::operator*=(float value)
{
	return *this = *this * value;
}

Vector2 Vector2::operator-(const Vector2 & vec) const
{
	return Vector2(x - vec.x, y - vec.y);
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	return *this = *this - vec;
}

Vector2 Vector2::operator/(float v) const
{
	return Vector2(x / v, y / v);
}

Vector2 & Vector2::operator/=(float v)
{
	return *this = *this / v;
}

float Vector2::GetLenght()
{
	return std::sqrt(GetLenghtSqr());
}

float Vector2::GetLenghtSqr() const
{
	return (x*x+y*y);
}
