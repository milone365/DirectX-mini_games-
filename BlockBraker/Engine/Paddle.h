#pragma once
#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"
class Paddle
{
public:
	Paddle(const Vec2& po_in, float HWidth, float HHeight);
	void Draw(Graphics& gfx)const;
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	void Update(const Keyboard&,float time);
	RectF GetRect()const;
	void ResetCooldown();
private:
	static constexpr float wingWidth = 6;
	Color wingColor = { 210,255,210 };
	Color color = { 200,220,200 };
	float speed = 360;
	float halfWidth;
	float halfHeight;
	Vec2 pos; 
	float exitScaleFactor;
	float fixedZoneHalfWidth ;
	float fixedZoneExit;
	static constexpr float maxExitRatio = 2.6f;
	static constexpr float fixedZoneWidthRatio = 0.2f;
	bool isCoolDown = false;
};