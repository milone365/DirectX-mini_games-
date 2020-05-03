#pragma once
#include "Graphics.h"

class MineField
{
public:
	class Tile 
	{
	public:
		enum class State
		{
			hidden,
			flagged,
			revealed,

		};
	public:
		bool hasBomb()const;
		void SpawnBomb();
		void DrawTile(const Vector2& spawnPos,bool gameover,Graphics& gfx)const;
		void Reveal();
		bool isRevealed()const;
		void toggleFlag();
		bool isFlagged()const;
		void setNeighborCount(int bombCount);
		bool hasNotBombNeighbors()const;
	private:
		bool HasBomb = false;
		State state = State::hidden;
		int nNeighbor = -1;
	};

public:
	MineField(int nMines);
	void Draw(Graphics& gfx)const;
	Rect getRect()const;
	void revealOnClick(const Vector2& screenPos);
	void OnFlagClick(const Vector2& screenPos);
	bool gameIsWon()const;
	void drawWin(Graphics& gfx)const;
	void revealTile(const Vector2& vec);
private:
	Tile& tileAt(const  Vector2& gridPosition);
	const Tile& tileAt(const  Vector2& gridPosition)const;
	Vector2 ScreenToGrid(const Vector2& screenPos);
	int countNeighborsBombs(const Vector2& gridPos);
private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	Tile field[width*height];
	bool gameOver = false;
	
};

