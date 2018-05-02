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

    // Getters/Setters
    int GetGold(){return gold_;}
    void MinusGold(int val){gold_ = gold_- val;}
    void PlusGold(int val){gold_ = gold_ + val;}
    QString GetHealthInfo();
    int* GetHealth(){return health_;}
    void MinusHealth(int index,int amount);

    void CatapultHit();

    QVector<Card*> hand_;
    QVector<Tile*> onField_;
private:
    Deck * deck_;
    int health_[4];
    int gold_;
    int heroCount_;

};

#endif // PLAYER_H
