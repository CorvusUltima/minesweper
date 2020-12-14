#pragma once
#include"Graphics.h"
#include"RectI.h"
#include"Vei2.h"
#include"Keyboard.h"
#include"Mouse.h"
#include<assert.h>
#include"img.h"


class MineField
{
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	
	public:

		Tile() = default;
		Tile(Vei2& topleft);
	 	void DrawTile(Graphics& gfx,Vei2& MousePos);
		
		RectI rect;
		State state = State::Hidden;
		bool hasMine = false;
		bool isFlaged = false;
		bool IsPointedAt(Vei2& MousePos);
		void Revieal(Vei2& MousePos);
		void Flag(Vei2& MousePos);
		Vei2 topleft;
		int MineCounter = 0;
		
		
	};

public:

	MineField(Vei2 FieldTopLeft,Mouse& mouse);
	void Draw(Graphics& gfx,Vei2& MousePos);
	void Update(Vei2& MousePos);
	void SpawnMines();
	int  GetIndex(int x, int y);
	bool CheckMines(int x, int y);
	bool Victory = false;
	bool CheckAllTiles();
	void WinCondition();
	void WinDraw(int x, int y, Graphics& gfx);
	
	RectI GetRect();


private:


	static constexpr int width = 5;
	static constexpr int height = 1;
	static constexpr int nTilesMax = width * height;
	int nMines=1;
	Vei2 FieldTopLeft;
	Tile tile[nTilesMax];
	Mouse& mouse;


};
