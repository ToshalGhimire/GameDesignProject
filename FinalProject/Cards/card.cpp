#include "card.h"
#include <qdebug.h>

#include <QGraphicsTextItem>

Card::Card(CardData card)
{
    info = card;

    this->setPen(QPen(Qt::black));

    //scene()->addItem(this);

    this->setToolTip(info.description);
    this->toolTip();


    xpos = 100;
    ypos = 100;

    this->CardStats();

    setFlag(QGraphicsItem::ItemIsMovable);

    hasMoved_ = false;
    hasAttacked_ = false;
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
    Power->setPos( this->boundingRect().x(), this->boundingRect().y() + 170);

    QGraphicsTextItem * Movement = new QGraphicsTextItem(this);
    Movement->setPlainText(QString("☈ - MOVEMENT: ") +  QString::number(info.movement));
    Movement->setPos( this->boundingRect().x(), this->boundingRect().y() + 185);

    QGraphicsTextItem * Range = new QGraphicsTextItem(this);
    Range->setPlainText(QString("Range: ") +  QString::number(info.range));
    Range->setPos( this->boundingRect().x(), this->boundingRect().y() + 155);




}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::darkBlue);
    //painter->drawText(10, 10, "Title");

    //painter->drawTextItem(0,0,);

    QBrush brush(Qt::lightGray);
    QRectF rec = boundingRect();

    painter->fillRect(rec,brush);
    painter->drawRect(rec);





}

QRectF Card::boundingRect() const {
    return QRectF(0,0,150,210);
    //QRectF()

}

QPainterPath Card::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(0,0,150,210));
    return path;

}

void Card::SETPOS(qreal x, qreal y){
    this->xpos = this->x()+110;
    this->ypos = y;
}
