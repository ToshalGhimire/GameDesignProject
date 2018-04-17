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
//    QBrush brush(Qt::lightGray);
//    brush.setStyle(Qt::SolidPattern);

    setBrush(Qt::lightGray);




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

    SetColor();
}

void Tile::SetColor()
{

    if(this->TileState_ == state::spawn){


        setPen(QPen(Qt::green));

        QBrush brush(Qt::gray);
        brush.setStyle(Qt::SolidPattern);

        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("S"));
        QFont titlefont("impact",40);
        SpawnText->setDefaultTextColor(Qt::darkGray);
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 40, this->boundingRect().y()-10);
    }
}

//void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{

//    painter->setPen(Qt::darkBlue);
//    QBrush brush(Qt::gray);
//    QRectF rec = boundingRect();



//    if(this->TileState_ == state::spawn){
//        painter->fillRect(rec,brush);
//    }
//}
