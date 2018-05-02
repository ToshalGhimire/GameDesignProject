#include "button.h"
#include <QBrush>
#include <QFont>

/**
 * @brief Button::Button sets initial values for button class
 * @param name Name to be printed on button
 */
Button::Button(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
   //making rect and seting color
//   setRect(0,0,200,50);
   setRect(0,0,180,45);

   QBrush brush;
   brush.setStyle(Qt::SolidPattern);
   brush.setColor(Qt::darkGray);

   setBrush(brush);

   //seting text

   text = new QGraphicsTextItem(name,this);

   double xpos = rect().width()/2 - (text->boundingRect().width())/1.4;
   double ypos = rect().height()/2 - (text->boundingRect().height())/1.25;

   QFont font("Avenir",20);
   text->setFont(font);


   text->setPos(xpos-10,ypos-6);

   setAcceptHoverEvents(true);

}

/**
 * @brief Button::mousePressEvent emits clicked signal
 * @param event
 */
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

/**
 * @brief Button::hoverEnterEvent changes color if hoverd over
 * @param event
 */
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
}

/**
 * @brief Button::hoverEnterEvent changes color if not over
 * @param event
 */
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);
}
