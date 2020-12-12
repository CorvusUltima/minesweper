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
               SpriteCodex::DrawTile0(topleft, gfx);
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






RectI MineField::GetRect()
{
    

        return RectI(FieldTopLeft, width * SpriteCodex::tileSize, height * SpriteCodex::tileSize);
   
}
