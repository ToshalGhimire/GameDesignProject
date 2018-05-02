#include "card.h"
#include <qdebug.h>

#include <QGraphicsTextItem>

Card* Card::clickedCard;

Card::Card(CardData card)
{
    info = card;

    this->setPen(QPen(Qt::black));
    this->setToolTip(info.description);
    this->toolTip();

    xpos = 100;
    ypos = 100;

    this->CardStats();

    hasMoved_ = false;
    hasAttacked_ = false;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    clickedCard = this;
    if(clickedOrNot == 0){
        clickedOrNot = 1;

        update();
    }
    else{
        clickedOrNot = 0;
        update();
    }
}

/**
 * @brief displays the stats of the card
 */
void Card::CardStats()
{
    QGraphicsTextItem * nameText = new QGraphicsTextItem(this);
    nameText->setPlainText(info.name);
    nameText->setPos(this->boundingRect().x(), this->boundingRect().y());

    QGraphicsTextItem * Cost = new QGraphicsTextItem(this);
    Cost->setPlainText(QString("COST: $") + QString::number(info.manaCost));
    Cost->setPos( this->boundingRect().x(), this->boundingRect().y()+ 20 );

    QGraphicsTextItem * Power = new QGraphicsTextItem(this);
    Power->setPlainText(QString("⚔ - POWER: ") +  QString::number(info.power));
    Power->setPos( this->boundingRect().x(), this->boundingRect().y() + 130);

    QGraphicsTextItem * Movement = new QGraphicsTextItem(this);
    Movement->setPlainText(QString("☈ - MOVEMENT: ") +  QString::number(info.movement));
    Movement->setPos( this->boundingRect().x(), this->boundingRect().y() + 150);

    QGraphicsTextItem * Range = new QGraphicsTextItem(this);
    Range->setPlainText(QString("Range: ") +  QString::number(info.range));
    Range->setPos( this->boundingRect().x(), this->boundingRect().y() + 110);
}

/**
 * @brief Painter function used to set color of clicked card
 */
void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(Qt::darkBlue);
    QBrush brush(Qt::lightGray);
    QRectF rec = boundingRect();

    if(clickedOrNot == 1){
        painter->setPen(QColor(10,200,62,245));
    }
    else if(clickedOrNot == 0 ){
        painter->setPen(Qt::darkBlue);
    }

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

/**
 * @brief Card::boundingRect rect of card
 * @return
 */
QRectF Card::boundingRect() const {
    return QRectF(0,0,150,180);
}

/**
 * @brief Card::shape shape of card
 * @return
 */
QPainterPath Card::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(0,0,150,180));
    return path;
}

/**
 * @brief Card::SETPOS set the position of the card to x values
 * @param x
 * @param y
 */
void Card::SETPOS(qreal x, qreal y){
    this->xpos = this->x()+110;
    this->ypos = y;
}
