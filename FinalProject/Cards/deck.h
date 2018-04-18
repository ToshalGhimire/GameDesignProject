#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Card;

class Deck
{
public:
    Deck();

    void Shuffle();
    Card * Draw();

    QVector<Card*> getDeck(){return deck_;}

private:
    QVector<Card*> deck_;
    //QVector<Card*> graveyard_;
};

#endif // DECK_H
