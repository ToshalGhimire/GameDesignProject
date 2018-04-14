#include "card.h"
#include <qdebug.h>

#include <QGraphicsTextItem>

Card::Card(CardData card)
{
    info = card;

    this->setPen(QPen(Qt::black));

    //scene()->addItem(this);

    this->setToolTip(QString("name"));

    QGraphicsTextItem * name = new QGraphicsTextItem(info.name,this);

    int xpos = rect().width()/2 - name->boundingRect().width();
    int ypos = rect().height()/2 - name->boundingRect().height();

    name->setPos(x(),y());
    /*

   text = new QGraphicsTextItem(name,this);

   int xpos = rect().width()/2 - text->boundingRect().width();
   int ypos = rect().height()/2 - text->boundingRect().height();

   QFont font("comic sans",20);
   text->setFont(font);


   text->setPos(xpos,ypos);
*/



}

void Card::CardStats()
{
    qDebug() << "Name: " << info.name
             << "\nPower: " << info.power
             << "\nMovement: " << info.movement
             << "\nRange: " << info.range
             << "\nMana: " << info.manaCost
             << "\n";


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
    return QRectF(0,100,150,210);
}

QPainterPath Card::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(0,100,100,140));
    return path;

}
