/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(RectF::FromCenter(Graphics::GetScreenRect().GetCenter(), fieldWidth / 2.0f, fieldHeight / 2.0f),
		wallThickness, wallColor),
	ball({ 300 + 24, 300 }, { -1, -1 }),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	soundFart(L"Sounds\\fart.wav"),
	soundReady(L"Sounds\\ready.wav"),
	padle({ 400, 500 }, 50, 10),
	lifecounter({ 30,30 }, 3)

{
	const Color colors[4] = { Colors::Red,Colors::Green,Colors::Blue,Colors::Cyan };
	const Vec2 topLeft(160.0f, 15.0f);
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2(x*brickWidth, y*brickHeight), brickWidth, brickHeight), c);
			i++;
		}

	}
	ResetBall();
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsTime = ft.Mark();
	while (elapsTime>0.0f)
	{
		const float dt = std::min(0.0025f, elapsTime);
		UpdateModel(dt);
		elapsTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (gameState != 1)
	{
		
		if (gameState == 0)
		{
			if (wnd.kbd.KeyIsPressed(VK_RETURN))
			{
				StartRound();
			}
		}
		else if (gameState == 3)
		{
			if ((curWaitTime += dt) > readyWaitTime)
			{
				gameState = 1;
			}
		}
		return;
	}
	padle.Update(wnd.kbd, dt);
	padle.DoWallCollision(walls.GetInnerBounds());
	if (padle.DoBallCollision(ball))
	{
		soundPad.Play();
	}
	else
	{
		padle.ResetCooldown();
	}
	for (Brick& b : bricks)
	{
		if(b.CheckBallCollision(ball))
		{
			b.ExecuteBallCollision(ball);
			soundBrick.Play();
			break;
        }
	}

	ball.Update(dt);
	const int ballWallCollRes = ball.DoWallCollision(walls.GetInnerBounds());
	switch (ballWallCollRes)
	{
	case 1:
		soundPad.Play();
		break;
	case 2:
		soundFart.Play();
		StartRound();
		ResetBall();
		break;
	default:
		break;
	}

}

void Game::StartRound()
{
	if (lifecounter.consumeLife())
	{
		curWaitTime = 0.0;
		soundReady.Play();
		gameState = 3;
	}
	else
	{
		gameState = 2;
	}

}

void Game::ResetBall()
{
	ball = Ball(Graphics::GetScreenRect().GetCenter(), { -0.5,-1 });
}

void Game::ComposeFrame()
{
	switch (gameState)
	{
	case 0:
		SpriteCodex::DrawTitle(Graphics::GetScreenRect().GetCenter(), gfx);
		break;
	case 1:
		ball.Draw(gfx);
		padle.Draw(gfx);
		lifecounter.Draw(gfx);
		break;
	case 2:
		SpriteCodex::DrawGameOver(Graphics::GetScreenRect().GetCenter(), gfx);
		break;
	case 3:
		padle.Draw(gfx);
		lifecounter.Draw(gfx);
		SpriteCodex::DrawReady(Graphics::GetScreenRect().GetCenter(), gfx);
		break;
	}

	if (gameState != 0)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		walls.Draw(gfx);
	}
	
	
}
