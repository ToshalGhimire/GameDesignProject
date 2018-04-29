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

    void SETPOS(qreal x, qreal y);

    CardData get_CardData(){return info;}

    static Card * GetClickedItem(){return clickedCard;}
    static void clearClickedItem(){clickedCard = NULL;}

private:
    CardData info;
    int clickedOrNot = 0;
    qreal xpos,ypos;

    bool hasMoved_;
    bool hasAttacked_;

    static Card* clickedCard;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


#endif // CARD_H
