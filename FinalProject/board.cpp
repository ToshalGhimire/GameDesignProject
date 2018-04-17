#include "game.h"
#include "board.h"

extern Game * game;

Board::Board()
{

}

QList<Tile *> Board::getBoard()
{
  return boardContainer;
}

void Board::MakeBoard(int xPos, int yPos)
{

    double xSHIFT,ySHIFT;

    Tile * OffsetInfo = new Tile();

    xSHIFT =(OffsetInfo->SCALE_BY*(OffsetInfo->sideOffset+1));
    ySHIFT = OffsetInfo->SCALE_BY* OffsetInfo->sideOffset;

    delete OffsetInfo;

    makeTileColumn(xPos-2,yPos+ySHIFT*4,4);//1st column - index: 0-3
    makeTileColumn(xPos+xSHIFT,yPos+ySHIFT,7);//2nd column - index: 4-10

    makeTileColumn(xPos+xSHIFT*2,yPos,8); //3rd column - index: 11-18
    makeTileColumn(xPos+xSHIFT*3,yPos-ySHIFT,9); //4th column - index: 19-27
    makeTileColumn(xPos+xSHIFT*4,yPos,8); //5th column - index: 28-35

    makeTileColumn(xPos+xSHIFT*5,yPos+ySHIFT,7); //6th column - index: 36-42
    makeTileColumn(xPos+xSHIFT*6,yPos+ySHIFT*4,4); //7th column - index: 43-46


    //seting Spawn points

    boardContainer[0]->setState(state::spawn);
    boardContainer[1]->setState(state::spawn);
    boardContainer[2]->setState(state::spawn);
    boardContainer[3]->setState(state::spawn);
    boardContainer[43]->setState(state::spawn);
    boardContainer[44]->setState(state::spawn);
    boardContainer[45]->setState(state::spawn);
    boardContainer[46]->setState(state::spawn);


}

void Board::makeTileColumn(int x, int y, int row)
{
    double yOffset;
    for(int i = 0; i < row;i++){
        Tile* temp = new Tile();
        yOffset = temp->SCALE_BY * (2 * temp->sideOffset);
        temp->setPos(x,y+yOffset*i);
        boardContainer.append(temp);
        game->scene_->addItem(temp);

    }
}
