#include "MineField.h"
#include<random>
#include<assert.h>
#include"SpriteCodex.h"
#include<random>

MineField::Tile::Tile(Vei2& topleft)  
    :
topleft(topleft)
{
    rect = { {topleft.x,topleft.y} , SpriteCodex::tileSize, SpriteCodex::tileSize };

}





void MineField::Tile::DrawTile( Graphics& gfx,Vei2& MousePos)
{

   
    switch (state)
    {
    case State::Hidden:
    {  
          SpriteCodex::DrawTileButton(topleft, gfx);    
    }
    break;
    case State::Flagged:
    {
        SpriteCodex::DrawTileButton(topleft, gfx);
        SpriteCodex::DrawTileFlag(topleft, gfx);
    }
    break;

    case State::Revealed:
    {
       
           if (!hasMine)
           {
               if(MineCounter==0)
               SpriteCodex::DrawTile0(topleft, gfx);
               if (MineCounter == 1) SpriteCodex::DrawTile1(topleft, gfx);
               else if(MineCounter==2)SpriteCodex::DrawTile2(topleft, gfx);
               else  if(MineCounter==3)SpriteCodex::DrawTile3(topleft, gfx);
               else if (MineCounter ==4)SpriteCodex::DrawTile4(topleft, gfx);
               else if (MineCounter == 5)SpriteCodex::DrawTile5(topleft, gfx);
               else  if (MineCounter == 6)SpriteCodex::DrawTile6(topleft, gfx);
               else  if (MineCounter == 7)SpriteCodex::DrawTile7(topleft, gfx);
               else if (MineCounter == 8)SpriteCodex::DrawTile8(topleft, gfx);
           }
           else
           {
               SpriteCodex::DrawTileBomb(topleft, gfx);
           }
       
       
    }
    
    break;
  
    }
}

bool MineField::Tile::IsPointedAt(Vei2&MousePos)
{
    return(MousePos.x>rect.left&& MousePos.x<rect.right&& MousePos.y>rect.top&& MousePos.y<rect.bottom) ;
}
void MineField::Tile::Revieal(Vei2& MousePos)
{
   
    if (IsPointedAt(MousePos)&&state==State::Hidden)
    {
        state = State::Revealed;

    }

}

void MineField::Tile::Flag(Vei2& MousePos)
{
    if (IsPointedAt(MousePos) && state == State::Hidden)
    {
        state = State::Flagged;
        isFlaged = true;

    }
}





MineField::MineField(Vei2 FieldTopLeft,Mouse& mouse)
    :
    FieldTopLeft(FieldTopLeft),
    mouse(mouse)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tile[i * width + j] = { Vei2(FieldTopLeft.x + SpriteCodex::tileSize * j,
                                         FieldTopLeft.y + SpriteCodex::tileSize * i)};
        }
       
    }
    SpawnMines();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (CheckMines(j, i - 1))
            {
                tile[GetIndex(j, i)].MineCounter++;
            }

            if (CheckMines(j, i + 1))
            {
                tile[GetIndex(j, i)].MineCounter++;
            
            }
           if ( CheckMines(j-1,i))
           {
               tile[GetIndex(j, i)].MineCounter++;

           }
           if ( CheckMines(j+1,i)) 
           {
               tile[GetIndex(j, i)].MineCounter++;

           }
           if (CheckMines(j-1,i-1)) 
           {
               tile[GetIndex(j, i)].MineCounter++;

           }
           if ( CheckMines(j-1,i+1)) 
           {
               tile[GetIndex(j, i)].MineCounter++;

           }
           if (CheckMines(j + 1, i - 1))
           {
               tile[GetIndex(j, i)].MineCounter++;

           }
           if (CheckMines(j + 1, i + 1)) 
           {
               tile[GetIndex(j, i)].MineCounter++;

           }
        }

    }
   
  
}

void MineField::Draw(Graphics& gfx,Vei2& MousePos)
{
    gfx.DrawRect(GetRect(),SpriteCodex::baseColor);
   

    for (int i = 0; i < height; i++)
    {
        for (int j=0;j<width;j++)
        {
            tile[i*width+j].DrawTile( gfx,MousePos);
        }
    }
}

void MineField::Update(Vei2& MousePos)
{
    for (int i = 0; i < nTilesMax; i++)
    {
      tile[i].IsPointedAt(MousePos);
      if (mouse.LeftIsPressed())
      {
          tile[i].Revieal(MousePos);
      }
     
      if (mouse.RightIsPressed())
      {
          tile[i].Flag(MousePos);
         
      }
    }

}

void MineField::SpawnMines()
{

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> MineDist(0,nTilesMax-1);
   
    for (int i = 0; i < nMines; i++)
    {
        int x = MineDist(rng);

        if (!MineField::tile[x].hasMine)
        {
            MineField::tile[x].hasMine = true;

        }
        else  
        {

            i--;
        }

    }

}

int MineField::GetIndex(int x, int y)
{
    int index = y * width + x;
    return index;
}

bool  MineField::CheckMines(int x,int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return false;
    }

    if (tile[GetIndex(x, y)].hasMine)
    {
        return true;
    }
    return false;
    
}

bool MineField::CheckAllTiles()
{

    int TileIsChecked = 0;

    for (int i = 0; i < nTilesMax; i++)
    {

       
        if (tile[i].state == Tile::State::Revealed&& !tile[i].hasMine)
        {
            TileIsChecked++;
        }

        if (TileIsChecked == nTilesMax - nMines)
        {

            return true;
        }
       
    }
   return false;
   
}

void MineField::WinCondition()
{
    for (int i=0; i < nTilesMax; i++)
    {
        int FlagedMines=0;
        if (tile[i].isFlaged && tile[i].hasMine)
        {
            FlagedMines++;

            if (FlagedMines == nMines&&CheckAllTiles())
            {
                Victory = true;
            }
        }
    }

}

void MineField::WinDraw(int x,int y ,Graphics& gfx)
{
    if (Victory)
    {
       
        {
            img::VicPic(x, y, gfx);
        }
    }
}






RectI MineField::GetRect()
{
        return RectI(FieldTopLeft, width * SpriteCodex::tileSize, height * SpriteCodex::tileSize);
}
