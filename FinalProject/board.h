#ifndef BOARD_H
#define BOARD_H


#include "tile.h"
#include <QList>


class Tile;

class Board
{
public:
    Board();


    //getter
    //QList<Tile *> getBoard();
    QList<Tile *> getBoard();

    void MakeBoard(int xPos, int yPos);
private:
    //QList<Tile *> boardContainer;
    QList<Tile *> boardContainer;
    void makeTileColumn(int x,int y,int row);

};

#endif // BOARD_H
