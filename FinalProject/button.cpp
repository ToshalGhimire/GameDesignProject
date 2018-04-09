#include "button.h"
#include <QBrush>
#include <QFont>


Button::Button(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
   //making rect and seting color
   setRect(0,0,200,50);

   QBrush brush;
   brush.setStyle(Qt::SolidPattern);
   brush.setColor(Qt::darkGray);

   setBrush(brush);

   //seting text

   text = new QGraphicsTextItem(name,this);

   int xpos = rect().width()/2 - text->boundingRect().width();
   int ypos = rect().height()/2 - text->boundingRect().height();

   QFont font("comic sans",20);
   text->setFont(font);


   text->setPos(xpos,ypos);

   setAcceptHoverEvents(true);

}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);
}
