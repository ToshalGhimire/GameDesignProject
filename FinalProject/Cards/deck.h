#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Card;

class Deck
{
public:
    Deck();
    void displayDeck();

    void Shuffle();
    Card * Draw();

private:
    QVector<Card*> deck_;
};

#endif // DECK_H
