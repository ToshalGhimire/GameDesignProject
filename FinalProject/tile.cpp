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

    setPen(QColor(241,237,238, 240));
    setBrush(QColor(23,21,20,220));




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


        QPen pen(Qt::white);
        pen.setWidth(3);
        setPen(pen);


        QBrush brush(QColor(15,21,20,220));
        brush.setStyle(Qt::SolidPattern);

        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("S"));
        QFont titlefont("impact",40);
        SpawnText->setDefaultTextColor(QColor(5,200,5,245));
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 40, this->boundingRect().y()-10);

    }
    if(this->TileState_ == state::resource_one){

        QPen pen(QColor(220,50,50,230));
        pen.setWidth(6);
        setPen(pen);
        this->setZValue(1);

        QBrush brush(QColor(255,223,0, 210));
        brush.setStyle(Qt::SolidPattern);

        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("+1"));
        QFont titlefont("impact",30);
        SpawnText->setDefaultTextColor(QColor(80,80,80,245));
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 30, this->boundingRect().y());
    }
    if(this->TileState_ == state::resource_two){


        QPen pen(QColor(220,50,50,230));
        pen.setWidth(6);
        setPen(pen);
        this->setZValue(1);

        QBrush brush(QColor(255,215,0, 255));
        brush.setStyle(Qt::SolidPattern);
        this->setZValue(1);


        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("+2"));
        QFont titlefont("impact",30);
        SpawnText->setDefaultTextColor(QColor(80,80,80,245));
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 30, this->boundingRect().y());
    }
    if(this->TileState_ == state::caltaput){



        QPen pen(QColor(241,237,238, 240));
        pen.setWidth(6);
        setPen(pen);


        QBrush brush(QColor(220,50,50,250));
        brush.setStyle(Qt::SolidPattern);

        setBrush(brush);

        QGraphicsTextItem * SpawnText = new QGraphicsTextItem(this);
        SpawnText->setPlainText(QString("C"));
        QFont titlefont("impact",35);
        SpawnText->setDefaultTextColor(QColor(241,237,238, 240));
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 43, this->boundingRect().y()-4);
    }
}
