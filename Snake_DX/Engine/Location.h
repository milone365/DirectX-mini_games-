#pragma once

class Location
{
public:
	int x=100;
	int y=100;
	//rhs = right hand side
	bool operator ==(const Location& rhs)const
	{
		return x == rhs.x&&y == rhs.y;
	}
	void Add(const Location& loc)
	{
		x += loc.x;
		y += loc.y;
	}
};