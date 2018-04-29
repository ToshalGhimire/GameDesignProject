#ifndef BOARD_H
#define BOARD_H
#include "tile.h"
#include <QList>

class Tile;

class Board
{

public:
    static Board& getInstance();
//    Board();
    QList<Tile *> getBoard();

    void MakeBoard(int xPos, int yPos);
    void setSpawnTiles();
    void ResourceTiles(bool israndom = 0);

private:
    Board() {}
    Board(Board const&) = delete;
    void operator=(Board const&)  = delete;

    QList<Tile *> boardContainer;
    void makeTileColumn(int x,int y,int row);
};

#endif // BOARD_H
