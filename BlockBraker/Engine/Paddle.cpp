#include "Paddle.h"

Paddle::Paddle(const Vec2 & po_in, float HWidth, float HHeight)
	:
	pos(po_in),halfWidth(HWidth),halfHeight(HHeight),
	exitScaleFactor(maxExitRatio/halfWidth),
	fixedZoneHalfWidth(halfWidth*fixedZoneWidthRatio),
	fixedZoneExit(fixedZoneHalfWidth*exitScaleFactor)
{
}

void Paddle::Draw(Graphics & gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, color);
}

bool Paddle::DoBallCollision(Ball & ball)
{
	if (!isCoolDown) 
	{
		const RectF rect = GetRect();
		if (rect.IsOverlappingWith(ball.GetRect()))
		{
			const Vec2 ballPos = ball.GetPosition();
			if (std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - pos).x)||
				ballPos.x >= rect.left && ballPos.x <= rect.right)
			{
				Vec2 dir;
				//calcolate magnitude
				const float xDifference = ballPos.x - pos.x;
                
				//if magnitude is less than 15;
				if (std::abs(xDifference) < fixedZoneHalfWidth)
				{
					if (xDifference < 0.0f)
					{
						dir = Vec2(-fixedZoneExit, -1);
					}
					else
					{
						dir = Vec2(fixedZoneExit, -1);
					}
				}
				else
				{
					dir = Vec2(xDifference*exitScaleFactor, -1);
				}
				ball.SetDirection(dir);
			}
		   else
			{
				ball.ReboundX();
			}
			isCoolDown = true;
			return true;
		}
	}
	
	return false;
}

void Paddle::DoWallCollision(const RectF & walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}


void Paddle::Update(const Keyboard& kbd,float time)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * time;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * time;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}

void Paddle::ResetCooldown()
{
	isCoolDown = false;
}
