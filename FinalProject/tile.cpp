#include "tile.h"

Tile* Tile::rightClickedTile_ = NULL;
Tile* Tile::leftClickedHeroTile_ = NULL;
Button * Tile::prevMoveButton_;
Button * Tile::prevAttackButton_;




extern Game * game;

/**
 * @brief Tile::Tile creates the hexgon QGraphicsItem
 * @param parent
 */
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

/**
 * @brief Tile::SwapStates swap states with another tile
 * @param t tile state
 */
void Tile::SwapStates(Tile &t)
{
    state temp = this->getState();
    this->setState(t.getState());
    t.setState(temp);
}

/**
 * @brief Tile::setState setter for the tilestate
 * @param s
 */
void Tile::setState(state s)
{
    this->TileState_ = s;

    SetColor();
}

/**
 * @brief Tile::SetColor my custom altrnative to the Paint Function, handles coloring for each of the diffrent tile state
 */
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

            this->cardRange_ = this->data_->range; // saving for hero combat
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

/**
 * @brief Tile::MakeHero turns a tile into a hero tile, by taking a CardData Struct and owner
 * @param data Card Data
 * @param who Owner of card
 */
void Tile::MakeHero(CardData * data, tileOwner who){
    data_ = data;
    owner_ = who;
    TileState_ = state::hero;
    this->SetColor();
}

/**
 * @brief Tile::mousePressEvent saves left clicked and right clicked tiles into a static member variable
 * @param event
 */
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{


    if(event->button() == Qt::RightButton){

        if(this->getState() == state::hero){
            qDebug() << "\Tile with Existing Hero cannot moved on to!";
        }else{
            rightClickedTile_ = this;
        }

    }

    if(event->button() == Qt::LeftButton){
           if(this->TileState_ == state::hero){
                leftClickedHeroTile_ = this;

            }

            if(game->getTurn() == PlayerTurn::one ){
                if(this->TileState_ == state::spawn_p2){
                    leftClickedHeroTile_ = this;
                }
            }else if(game->getTurn() == PlayerTurn::two){
                if(this->TileState_ == state::spawn_p1){
                    leftClickedHeroTile_ = this;
                }
            }else{
                RemoveButtons();
            }

    }

}

/**
 * @brief Tile::mouseDoubleClickEvent if hero card, brings up two buttons, an attack and a move button
 * @param event
 */
void Tile::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    RemoveButtons();
    prevAttackButton_ = NULL;
    prevMoveButton_ = NULL;

    if(this->getState() == state::hero){
        Button * moveButton = new Button(QString("Move"));
        moveButton->setPos(0,620);
        connect(moveButton,SIGNAL(clicked()),this,SLOT(Move()));
        scene()->addItem(moveButton);

        Button * attackButton = new Button(QString("Attack"));
        attackButton->setPos(670,620);
        connect(attackButton,SIGNAL(clicked()),this,SLOT(Attack()));
        scene()->addItem(attackButton);

        prevAttackButton_ = attackButton;
        prevMoveButton_ = moveButton;

       }


}

/**
 * @brief Tile::RemoveButtons removes the two attack and move buttons from scene
 */
void Tile::RemoveButtons(){
    game->scene_->removeItem(prevMoveButton_);
    game->scene_->removeItem(prevAttackButton_);

}

int xOffset = 70;
int yOffset = 35;

/**
 * @brief Tile::distanceCalcuate calcuates the distance between two tiles and returns boolean based on if trying to move or attack
 * @param current current tile
 * @param dest tile to move to
 * @param attack True if attacking another tile
 * @return Bool
 */
bool Tile::distanceCalcuate(Tile * current,Tile * dest, bool attack){

    if(dest == NULL){
        qDebug() << "\nPlease click a point First!";
        return 0;
    }

    int x1 = current->x() + xOffset;
    int y1 = current->y() + yOffset;

    int x2 = dest->x() + xOffset;
    int y2 = dest->y() + yOffset;

    int inside = pow((x1-x2),2) + pow((y1-y2),2);

    int result = pow(inside,.5);

    if(attack){

        if(Tile::GetLeftClickedItem() == NULL){
            qDebug() << "\nPlease select a target first!";
            return 0;
        }

        if(result < current->cardRange_ * 95){
            //qDebug() << "\nYour hero is close enough to attack that hero!";
            return true;
        }else{
            qDebug() << "\nYour hero needs to move closer to attack that hero!";
           return false;
        }

    }else{

        if(result < cardMovement_*96){
            qDebug() << "\nThat Movement is Allowed";
            return true;
        }else{
            qDebug() << "\nThat Movement is NOT Allowed";
            return false;
        }

    }

}

/**
 * @brief Tile::clearClickedItems rests right and left clicked tiles to NULL
 */
void Tile::clearClickedItems()
{
    rightClickedTile_ = NULL;
    leftClickedHeroTile_ = NULL;

}

/**
 * @brief Tile::Move once move button is clicked, it calls movetile function if movement is allowed
 */
void Tile::Move()
{

    if(distanceCalcuate(this,rightClickedTile_)){
        Board& tempBoard = Board::getInstance();
        tempBoard.MoveTile(this,rightClickedTile_);

    };


}

/**
 * @brief Tile::Attack once attack button is clicked, it calls attacktile function if attack range is allowed
 */
void Tile::Attack()
{

    if(leftClickedHeroTile_ == NULL){
        qDebug() << "\nPlease Left Click target first!";
        return;
    }

    if(distanceCalcuate(this,leftClickedHeroTile_,true)){
        Board& tempBoard = Board::getInstance();
        tempBoard.AttackTile(this,leftClickedHeroTile_);

    };
}
