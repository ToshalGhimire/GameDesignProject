#ifndef TILE_H
#define TILE_H

#include "game.h"

#include <QGraphicsPolygonItem>

enum class state {empty,spawn,hero,resource,caltaput,shop};

class Tile : public QGraphicsPolygonItem
{
public:
    Tile(QGraphicsItem* parent = NULL);

    int SCALE_BY = 50;//scale
    double sideOffset = 0.70710678118;//hexagon side offset

    void SwapStates(Tile &t);
    void setState(state s);
    state getState(){return TileState_;}




private:
    state TileState_;
    //Player owner = Player::none;

    //(1,0),(2,0)
};


class Hero : public Tile
{
public:
    Hero(state s,QGraphicsItem* parent = NULL);



private:
    int movement_ = 2;
    int attack_ = 2;
    int health = 3;

    int attackRange_ = 1;

};
#endif // TILE_H