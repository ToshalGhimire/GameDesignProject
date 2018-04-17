#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>

#include "../Cards/deck.h"



class Player
{
public:
    Player();

private:
    QVector<Card*> hand_;
    Deck * deck_;

    int health_;

};

#endif // PLAYER_H
