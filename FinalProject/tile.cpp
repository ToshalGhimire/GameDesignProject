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
        QFont titlefont("impact",35);
        SpawnText->setDefaultTextColor(QColor(5,200,5,245));
        SpawnText->setFont(titlefont);
        SpawnText->setPos(this->boundingRect().x() + 37, this->boundingRect().y()+3);
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
        SpawnText->setPos(this->boundingRect().x() + 31, this->boundingRect().y()+6);
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
        SpawnText->setPos(this->boundingRect().x() + 31, this->boundingRect().y()+6);
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
        SpawnText->setPos(this->boundingRect().x() + 40, this->boundingRect().y()+4);
    }

    if(this->TileState_ == state::hero){
            //caltapult tile design
            setFlag(QGraphicsItem::ItemIsMovable);
            this->setZValue(2);

            if(owner_ == tileOwner::one){
                QPen pen(Qt::blue);
                pen.setWidth(6);
                setPen(pen);

              }else if(owner_ == tileOwner::two){
                 QPen pen(Qt::red);
                 pen.setWidth(6);
                 setPen(pen);
               }else{
                  QPen pen(Qt::black);
                  pen.setWidth(6);
                  setPen(pen);
             }

            QBrush brush(Qt::gray);


            qDebug() << "Tiles position: " << this->pos();

            brush.setStyle(Qt::SolidPattern);
            setBrush(brush);
    /*
            QBrush brush(Qt::gray);
            brush.setStyle(Qt::SolidPattern);

            setBrush(brush)*/;

            // Attack text
            QGraphicsTextItem * AttackText = new QGraphicsTextItem(this);
            AttackText->setPlainText(QString("⚔") + QString::number(data_->power));
            QFont titlefont("Avenir",15);
            AttackText->setDefaultTextColor(Qt::black);
            AttackText->setFont(titlefont);
            AttackText->setPos(this->boundingRect().x() + 35, this->boundingRect().y());

            // Movement text
            QGraphicsTextItem * MovementText = new QGraphicsTextItem(this);
            MovementText->setPlainText(QString("☈") + QString::number(data_->movement));
            MovementText->setDefaultTextColor(Qt::black);
            MovementText->setFont(titlefont);
            MovementText->setPos(this->boundingRect().x() + 42, this->boundingRect().y()+33);

            // Name text
            QGraphicsTextItem * NameText = new QGraphicsTextItem(this);
            NameText->setPlainText(QString(data_->name));
            QFont namefont("times new roman",10);
            NameText->setDefaultTextColor(Qt::black);
            NameText->setFont(namefont);
            NameText->setPos(this->boundingRect().x() + 15, this->boundingRect().y() + 24);

            if(data_->range != 1){
                // Adding range text (if range is more then one)
                MovementText->setPos(this->boundingRect().x() + 31, this->boundingRect().y()+45);
                QGraphicsTextItem * RangeText = new QGraphicsTextItem(this);
                RangeText->setPlainText(QString("R:") + QString::number(data_->range));
                RangeText->setDefaultTextColor(Qt::black);
                RangeText->setFont(titlefont);
                RangeText->setPos(this->boundingRect().x() + 65, this->boundingRect().y() + 45);

            }
        }
}

void Tile::MakeHero(CardData * data, tileOwner who){
    data_ = data;
    owner_ = who;
    TileState_ = state::hero;
    this->SetColor();
}
