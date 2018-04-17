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

    void SetColor();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        if(TileState_ == state::spawn){
            qDebug() << "Spawn item clicked";
        }
    }

private:
    state TileState_;
    //Player owner = Player::none;

    //(1,0),(2,0)
};



#endif // TILE_H
