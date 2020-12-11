#pragma once
#include"Graphics.h"
#include"RectI.h"
#include"Vei2.h"
#include"Keyboard.h"
#include"Mouse.h"
#include<assert.h>

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
	 	void DrawTile(Vei2& topleft, Graphics& gfx,Vei2& MousePos);
		
		RectI rect;
		State state = State::Hidden;
		bool hasMine = false;
		bool IsPointedAt(Vei2& MousePos);
		void Revieal(Vei2& MousePos);
	
		
	};

public:

	MineField(Vei2 FieldTopLeft,Mouse& mouse);
	void Draw(Graphics& gfx,Vei2& MousePos);
	void Update(Vei2& MousePos);
	void SpawnMines();
	void  Revieal(Vei2& MousePos);
	

	
	RectI GetRect();


private:


	static constexpr int width = 8;
	static constexpr int height = 10;
	static constexpr int nTilesMax = width * height;
	int nMines=20;
	Vei2 FieldTopLeft;
	Tile tile[nTilesMax];
	Mouse& mouse;


};
