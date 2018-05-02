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

    // Getters/Setters
    QList<Tile *> getBoard(){return boardContainer;}
    void setSpawnTiles();
    int getResourceCount(PlayerTurn whos);

    //Board Construction
    void MakeBoard(int xPos, int yPos);
    void ResourceTiles(bool israndom = 0);
    void SpawnReset();

    //Card Movement/Attack/Spawn functions
    void SpawnCard(Tile * card,PlayerTurn t);
    void MoveTile(Tile * herotile, Tile* PosToPlace);
    void AttackTile(Tile * attacker, Tile * Target);

    PlayerTurn CapturedCaltapult();

    QList<Tile*> P1_heros;
    QList<Tile*> P2_heros;
    QList<Tile *> boardContainer;
private:
    Board() {}
    Board(Board const&) = delete;
    void operator=(Board const&)  = delete;
    void makeTileColumn(int x,int y,int row);

};

#endif // BOARD_H
