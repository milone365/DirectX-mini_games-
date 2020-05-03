#include "MineField.h"
#include<assert.h>
#include<random>
#include "Vector2.h"
#include "SpriteCodex.h"



bool MineField::Tile::hasBomb() const
{
	return HasBomb;
}

void MineField::Tile::SpawnBomb()
{
	assert(!HasBomb);
	HasBomb = true;
		
}

void MineField::Tile::DrawTile(const Vector2 & spawnPos, bool gameover, Graphics & gfx) const
{
	switch (state)
	{
	case MineField::Tile::State::hidden:
		if (gameover&&hasBomb())
		{
			SpriteCodex::DrawTileBomb(spawnPos, gfx);
		}
		else
		{
			SpriteCodex::DrawTileButton(spawnPos, gfx);
		}
		break;
	case MineField::Tile::State::flagged:
		if (gameover&&hasBomb())
		{
			SpriteCodex::DrawTileBomb(spawnPos, gfx);
		}
		else
		{
			SpriteCodex::DrawTileButton(spawnPos, gfx);
		    SpriteCodex::DrawTileFlag(spawnPos, gfx);
		}
		
		break;
	case MineField::Tile::State::revealed:
		if (!hasBomb())
		{
			SpriteCodex::DrawTileNumber(spawnPos, nNeighbor, gfx);
		}
		else
		{
			SpriteCodex::DrawTileBombRed(spawnPos, gfx);
		}
		break;
	default:
		break;
	}
}

void MineField::Tile::Reveal()
{
	assert(state == State::hidden);
	state = State::revealed;
}

bool MineField::Tile::isRevealed() const
{
	return state == State::revealed;
}

void MineField::Tile::toggleFlag()
{
	assert(!isRevealed());
	if (state == State::hidden)
	{
		state = State::flagged;
	}
	else
	{
		state = State::hidden;
	}
	
}

bool MineField::Tile::isFlagged()const
{
	return state == State::flagged;
}

void MineField::Tile::setNeighborCount(int bombCount)
{
	assert(nNeighbor == -1);
	nNeighbor = bombCount;
	
}

bool MineField::Tile::hasNotBombNeighbors() const
{
	return nNeighbor==0;
}

void MineField::revealOnClick(const Vector2 & screenPos)
{
	if (gameOver)return;
	const Vector2 gridpos = ScreenToGrid(screenPos);
	assert(gridpos.x >= 0 && gridpos.x < width&&gridpos.y >= 0 && gridpos.y < height);
	revealTile(gridpos);
}

void MineField::OnFlagClick(const Vector2 & screenPos)
{
	if (gameOver)return;
	const Vector2 gridpos = ScreenToGrid(screenPos);
	assert(gridpos.x >= 0 && gridpos.x < width&&gridpos.y >= 0 && gridpos.y < height);
	Tile& tile = tileAt(gridpos);
	if (!tile.isRevealed())
	{
		tile.toggleFlag();
	}
}



MineField::MineField(int nMines)
{
	assert(nMines > 0 && nMines < width*height);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int>xDist(0, width - 1);
	std::uniform_int_distribution<int>yDist(0, height - 1);

	//loop number of level's mines
	for (int i = 0; i < nMines; i++)
	{
		Vector2 spawnPos;
		do
		{
			spawnPos = { xDist(rng),yDist(rng) };
		} 
		while (tileAt(spawnPos).hasBomb());
	
		tileAt(spawnPos).SpawnBomb();
	}
	for (Vector2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			tileAt(gridPos).setNeighborCount(countNeighborsBombs(gridPos));
		}
	}
}

void MineField::Draw(Graphics & gfx) const
{
		//draw rectangle of base color (all gray)
		gfx.DrawRect(getRect(), SpriteCodex::baseColor);
		//draw grid
		for (Vector2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
		{
			for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
			{
				tileAt(gridPos).DrawTile(gridPos*SpriteCodex::tileSize,gameOver, gfx);
			}
		}
}

Rect MineField::getRect() const
{
	return Rect(0,width*SpriteCodex::tileSize,0,height*SpriteCodex::tileSize);
}

MineField::Tile& MineField::tileAt(const Vector2 & gridPosition) 
{
	return field[gridPosition.y*width + gridPosition.x];
}

const MineField::Tile& MineField::tileAt(const Vector2 & gridPosition) const
{
	return field[gridPosition.y*width + gridPosition.x];
}

//conver screenPos to gridPos
Vector2 MineField::ScreenToGrid(const Vector2 & screenPos)
{
	return screenPos / SpriteCodex::tileSize;
}

int MineField::countNeighborsBombs(const Vector2 & gridPos)
{
	int zero = 0;
	int w = width - 1;
	int h = height - 1;

	const int xStart = zero>(gridPos.x - 1)?zero:(gridPos.x - 1);
	const int yStart = zero >(gridPos.y - 1)?zero:(gridPos.y - 1);
	const int xEnd = w<(gridPos.x + 1)?w:(gridPos.x + 1);
	const int yEnd = h<(gridPos.y + 1)?h:(gridPos.y + 1);
	int count = 0;
	for (Vector2 grid = { xStart,yStart }; grid.y <= yEnd; grid.y++)
	{
		for (grid.x = xStart; grid.x <= xEnd; grid.x++)
		{
			if (tileAt(grid).hasBomb())
			{
				count++;
			}
			
		}
	}
	return count;
}

bool MineField::gameIsWon() const
{
	for (const Tile& t : field)
	{
		if ( t.hasBomb() && !t.isFlagged()||!t.hasBomb()&&!t.isRevealed())
		{
          return false;
		}
	}
	return true;
}

void MineField::drawWin(Graphics& gfx) const
{
	SpriteCodex::DrawWin({200,200}, gfx);
}

void MineField::revealTile(const Vector2 & gridpos)
{
	Tile& tile = tileAt(gridpos);
	if (!tile.isRevealed() && !tile.isFlagged())
	{
		tile.Reveal();
		if (tile.hasBomb())
		{
			gameOver = true;
		}
		else if (tile.hasNotBombNeighbors())
		{
			int zero = 0;
			int w = width - 1;
			int h = height - 1;

			const int xStart = zero > (gridpos.x - 1) ? zero : (gridpos.x - 1);
			const int yStart = zero > (gridpos.y - 1) ? zero : (gridpos.y - 1);
			const int xEnd = w < (gridpos.x + 1) ? w : (gridpos.x + 1);
			const int yEnd = h < (gridpos.y + 1) ? h : (gridpos.y + 1);

			for (Vector2 grid = { xStart,yStart }; grid.y <= yEnd; grid.y++)
			{
				for (grid.x = xStart; grid.x <= xEnd; grid.x++)
				{
					Tile& tile = tileAt(grid);
					if (!tile.isRevealed())
					{
						revealTile(grid);
					}

				}
			}

		}
	}
}
