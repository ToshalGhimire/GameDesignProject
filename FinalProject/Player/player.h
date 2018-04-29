#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>

#include "../Cards/deck.h"
#include "../Cards/card.h"

class Card;
class Deck;

class Player
{
public:
    Player();

    void DrawCard();
    void shuffle();

    QString GetHealthInfo();
    QVector<Card*> hand_;
    QVector<Tile*> onField_;

    int GetGold(){return gold_;}
    void MinusGold(int val){gold_ = gold_- val;}
    void PlusGold(int val){gold_ = gold_ + val;}

private:
    Deck * deck_;

    int health_[4];
    int gold_;
    int heroCount_;

};

#endif // PLAYER_H
