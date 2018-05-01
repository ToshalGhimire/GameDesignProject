#ifndef BOARD_H
#define BOARD_H
#include "tile.h"
#include "game.h"
#include <QList>

class Tile;
enum class PlayerTurn;

class Board
{

public:
    static Board& getInstance();
//    Board();
    QList<Tile *> getBoard(){return boardContainer;}

    void MakeBoard(int xPos, int yPos);
    void setSpawnTiles();
    void ResourceTiles(bool israndom = 0);

    void SpawnCard(Tile * card,PlayerTurn t);

    void MoveTile(Tile * herotile, Tile* PosToPlace);

    int Return5(){return 5;} //test DEBUG
    //QList<Tile *> boardContainer; DEBUG

    QList<Tile*> P1_heros;
    QList<Tile*> P2_heros;

    void SpwanReset();
    int getResourceCount(PlayerTurn whos);
    PlayerTurn CapturedCaltapult();

private:
    Board() {}
    Board(Board const&) = delete;
    void operator=(Board const&)  = delete;

    QList<Tile *> boardContainer;
    void makeTileColumn(int x,int y,int row);

//    QList<Tile*> P1_heros;
//    QList<Tile*> P2_heros;
};

#endif // BOARD_H
