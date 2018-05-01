#include "tile.h"

Tile* Tile::ShiftClickedPos_;

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

    if(this->TileState_ == state::spawn_p1 || this->TileState_ == state::spawn_p2 ){

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
                QPen pen(Qt::red);
                pen.setWidth(6);
                setPen(pen);

              }else if(owner_ == tileOwner::two){
                 QPen pen(Qt::blue);
                 pen.setWidth(6);
                 setPen(pen);
               }else{
                  QPen pen(Qt::black);
                  pen.setWidth(6);
                  setPen(pen);
             }

            QBrush brush(Qt::gray);

            brush.setStyle(Qt::SolidPattern);
            setBrush(brush);
    /*
            QBrush brush(Qt::gray);
            brush.setStyle(Qt::SolidPattern);

            setBrush(brush)*/;

            // Attack text
            QGraphicsTextItem * AttackText = new QGraphicsTextItem(this);
            AttackText->setPlainText(QString("⚔") + QString::number(data_->power));
            this->cardPower_ = data_->power;
            QFont titlefont("Avenir",10);
            AttackText->setDefaultTextColor(Qt::black);
            AttackText->setFont(titlefont);
            AttackText->setPos(this->boundingRect().x() + 40, this->boundingRect().y());

            // Movement text
            QGraphicsTextItem * MovementText = new QGraphicsTextItem(this);
            MovementText->setPlainText(QString("☈") + QString::number(data_->movement));
            this->cardMovement_ = data_->movement;
            MovementText->setDefaultTextColor(Qt::black);
            MovementText->setFont(titlefont);
            MovementText->setPos(this->boundingRect().x() + 42, this->boundingRect().y()+45);

            // Name text
            QGraphicsTextItem * NameText = new QGraphicsTextItem(this);
            NameText->setPlainText(QString(data_->name));
            this->cardName_ = data_->name;
            QFont namefont("times new roman",10);
            NameText->setDefaultTextColor(Qt::black);
            NameText->setFont(namefont);
            NameText->setPos(this->boundingRect().x() + 10, this->boundingRect().y() + 24);

            if(data_->range != 1){
                // Adding range text (if range is more then one)
                MovementText->setPos(this->boundingRect().x() + 31, this->boundingRect().y()+45);
                QGraphicsTextItem * RangeText = new QGraphicsTextItem(this);
                RangeText->setPlainText(QString("R:") + QString::number(data_->range));
                this->cardRange_ = data_->range;
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

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(this->TileState_ == state::hero){
        Button * moveButton = new Button(QString("Move"));
        moveButton->setPos(0,600);
        connect(moveButton,SIGNAL(clicked()),this,SLOT(test()));
        scene()->addItem(moveButton);
    }

    if(event->button() == Qt::RightButton){
        if(this->getState() == state::hero){
            qDebug() << "cannot move there!";
        }else{
            ShiftClickedPos_ = this;
        }

    }

}

int xOffset = 70;
int yOffset = 35;

bool Tile::distanceCalcuate(Tile * current,Tile * dest){

    if(dest == NULL){
        qDebug() << "Please Shift Click a point!";
        return 0;
    }
    int x1 = current->x() + xOffset;
    int y1 = current->y() + yOffset;

    int x2 = dest->x() + xOffset;
    int y2 = dest->y() + yOffset;

    int inside = pow((x1-x2),2) + pow((y1-y2),2);

    int result = pow(inside,.5);


    if(result < cardMovement_*96){
        qDebug() << "That Movement is Allowed";
        return true;
    }else{
        qDebug() << "That Movement is NOT Allowed";
        return false;
    }
}

void Tile::test()
{

    if(distanceCalcuate(this,ShiftClickedPos_)){
        Board& tempBoard = Board::getInstance();
        tempBoard.MoveTile(this,ShiftClickedPos_);

    };


}
