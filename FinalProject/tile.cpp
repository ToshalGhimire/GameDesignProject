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


        QPen pen(Qt::green);
        pen.setWidth(3);
        setPen(pen);


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
    if(this->TileState_ == state::resource_one){

        QPen pen(Qt::blue);
        pen.setWidth(3);
        setPen(pen);
        this->setZValue(1);

        QBrush brush(Qt::yellow);
        brush.setStyle(Qt::SolidPattern);

        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("+1"));
        QFont titlefont("impact",30);
        SpawnText->setDefaultTextColor(Qt::darkGray);
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 30, this->boundingRect().y());
    }
    if(this->TileState_ == state::resource_two){


        QPen pen(Qt::blue);
        pen.setWidth(3);
        setPen(pen);
        this->setZValue(1);

        QBrush brush(Qt::yellow);
        brush.setStyle(Qt::SolidPattern);
        this->setZValue(1);


        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("+2"));
        QFont titlefont("impact",30);
        SpawnText->setDefaultTextColor(Qt::darkGray);
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 30, this->boundingRect().y());
    }
    if(this->TileState_ == state::caltaput){



        QPen pen(Qt::red);
        pen.setWidth(5);
        setPen(pen);


        QBrush brush(Qt::lightGray);
        brush.setStyle(Qt::SolidPattern);

        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("C"));
        QFont titlefont("impact",35);
        SpawnText->setDefaultTextColor(Qt::darkGray);
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 43, this->boundingRect().y()-4);
    }
}
