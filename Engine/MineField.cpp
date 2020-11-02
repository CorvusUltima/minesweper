#include "MineField.h"
#include<random>
#include<assert.h>
#include"SpriteCodex.h"

bool MineField::Tile::HasMine()
{
    return hasMine;
}

void MineField::Tile::SpawnMine()
{
    assert(!hasMine);
   hasMine =true; 
}

void MineField::Tile::DrawTile(Vei2& ScreenPosition, Graphics& gfx) const
{
    switch (state)
    {
    case State::Hidden:
        {
        SpriteCodex::DrawTileButton(ScreenPosition,gfx);
        }
          break;
    case State::Flagged:
         {
        SpriteCodex::DrawTileButton(ScreenPosition, gfx);
        SpriteCodex::DrawTileFlag(ScreenPosition, gfx);
         }
         break;

    case State::Revealed:
         {
        if (!hasMine)
        {
            SpriteCodex::DrawTile0(ScreenPosition, gfx);
        }
        else
        {
            SpriteCodex::DrawTileBomb(ScreenPosition, gfx);
        }
         }
         break;
    }
}

MineField::MineField(int nMines)
{
    assert(nMines > 0 && nMines < Width* Height - 1);
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> xDist(0, Width - 1);
    std::uniform_int_distribution<int> yDist(0, Height - 1);

    for (int nSpawnd = 0; nSpawnd < nMines; ++nSpawnd)
    {
        Vei2 SpawnPos;

        do
        {
            SpawnPos = { xDist(rng),yDist(rng) };
        }
         
        while ( TileAt(SpawnPos).HasMine());
         
        TileAt(SpawnPos).SpawnMine();
       

    }

    


}

void MineField::Draw(Graphics& gfx)
{
    for (Vei2 GridPos{0,0};GridPos.y<Height;GridPos.y++)
    {
        for (; GridPos.x < Width; GridPos.x++)

            TileAt(GridPos).DrawTile(GridPos * SpriteCodex::tileSize, gfx);
    }
}

MineField::Tile& MineField::TileAt(const Vei2& gridpos)
{
    return  field[gridpos.y * Width+gridpos.x];
}
