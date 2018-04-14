#include "tile.h"

Tile::Tile(QGraphicsItem* parent)
{
    //drawing polygon
    QVector<QPointF> hexpoints;

    hexpoints << QPointF(1,0) << QPointF(2,0) << QPointF(2+sideOffset,sideOffset)
              <<  QPointF(2,2*sideOffset) << QPointF(1,2*sideOffset) << QPointF(1-sideOffset,sideOffset);



    for(size_t i = 0,n = hexpoints.size(); i < n; ++i){
        hexpoints[i] *= SCALE_BY;
    }

    //creating a polygon based on the points above
    QPolygonF hexagon(hexpoints);

    setPolygon(hexagon);
}

void Tile::SwapStates(Tile &t)
{
    state temp = this->getState();
    this->setState(t.getState());
    t.setState(temp);
}

void Tile::setState(state s)
{
    this->TileState_ = s;
}
