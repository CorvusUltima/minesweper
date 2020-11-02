#pragma once
#include"Graphics.h"

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

		bool HasMine();
		void SpawnMine();

		void DrawTile(Vei2& ScreenPosition, Graphics& gfx) const;

	private:

		State state = State::Hidden;
		bool hasMine;

	};

public:

	MineField(int nMines);
	void Draw(Graphics& gfx);

private:
	
	Tile& TileAt(const Vei2& gridpos);

private:

	static constexpr int Width = 20;
	static constexpr int Height = 16;
	Tile field[ Width * Height];



};

