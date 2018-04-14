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

private:
    CardData info;

};


#endif // CARD_H
