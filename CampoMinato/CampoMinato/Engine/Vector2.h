#pragma once
class Vector2
{
public:
	Vector2()=default;
	Vector2(int in_x, int in_y);
	Vector2 operator+(const Vector2& vec)const;
	Vector2& operator+=(const Vector2& vec);
	Vector2 operator*(float value)const;
	Vector2& operator*=(float value);
	Vector2 operator-(const Vector2& vec)const;
	Vector2& operator-=(const Vector2& vec);
	Vector2 operator/(float v)const;
	Vector2& operator/=(float v);
	float GetLenght();
	float GetLenghtSqr()const;
public:
	int x, y;
};

