#ifndef CARD_H
#define CARD_H

#include<QGraphicsItem>
#include <string>


#include "tile.h"

struct CardData{
    QString name;
    int manaCost;
    int power;
    int movement;
    int range;
    QString description;
};

struct CardIcons {
    QImage coins;
    QImage movement;
    QImage power;
};

class Card : public QGraphicsRectItem
{
public:
    Card(CardData Card);

    void CardStats();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;

    QPainterPath shape() const;

    void SETPOS(qreal x, qreal y);

private:
    CardData info;
    CardIcons icon;

    qreal xpos,ypos;

    bool hasMoved_;
    bool hasAttacked_;


};


#endif // CARD_H
