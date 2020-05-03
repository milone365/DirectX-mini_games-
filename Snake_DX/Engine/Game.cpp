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
	board(gfx),
	rnd(std::random_device()()),
	snake({ 2,2 }),
	goal(rnd, board, snake)
	
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameIsStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameIsStarted = true;
		}
		return;
	}
	Inputs();
}


void Game::ComposeFrame()
{
	if (!gameIsStarted)
	{
		SpriteCodex::DrawTitle(200,200,gfx);
		return;
	}
	snake.Draw(board);
	goal.Draw(board);
	board.DrawBorder();

	if (gameIsOver)
	{
		SpriteCodex::DrawGameOver(200,200,gfx);
	}
}


void Game::Inputs()
{
	if (!gameIsOver)
	{
		
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1,0 };
		}
		speedUpCounter++;
		if (speedUpCounter >= speedUpPeriod)
		{
			speedUpCounter = 0;
			snakeMovePeriod = std::max(snakeMovePeriod - 1, minMovePeriod);
			
		}
		snakeMoveCounter++;
		if (snakeMoveCounter >= snakeMovePeriod)
		{
			snakeMoveCounter = 0;
			//gameOverCheck
			const Location next = snake.GetNextHeadLocation(delta_loc);
			if (!board.isInsideTheBoard(next)||snake.isInTile(next))
			{
				gameIsOver = true;
			}
			else 
			{
				const bool eating = next == goal.getLocation();
				if (eating)
				{
					snake.Grow();
					goal.Respawn(rnd, board, snake);
				}
				snake.MoveBy(delta_loc);
				
			}
			
			
		}
		
	}
	
	
	
}
//chose from 0 and 255
/*std::uniform_int_distribution<int>colorDist(0, 255);

for (int y = 0; y < board.GetGridHeight(); y++)
{
	for (int x = 0; x < board.GetGridWidth(); x++)
	{
		Location loc{ x,y };
		Color c(colorDist(rnd), colorDist(rnd), colorDist(rnd));
		board.DrawCell(loc, c);
	}
}*/