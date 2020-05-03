#pragma once

#include "SpriteCodex.h"
#include "Graphics.h"
#include <algorithm>

class LifeCounter
{
public:
	//contructor
	LifeCounter(Vec2 pos,int life) 
	{
		position = pos;
		lives = life;
	}
	//erase life
	bool consumeLife()
	{
		const bool haslife = lives > 0;
		lives = std::max(lives - 1, 0);
		return haslife;
	}
	// draw poo
	void Draw(Graphics& gfx)const
	{
		const Vec2 offset(spacing, 0.0f);
		for (int c = 0; c < lives; c++)
		{
			SpriteCodex::DrawPoo(position + offset * float(c), gfx);
		}
	}
private:
	//space
	static constexpr float spacing = 28;
	//number of lives
	int lives;
	//position for draw
	Vec2 position;
};