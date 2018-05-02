#include "player.h"
#include <QDebug>

/**
 * @brief Player::Player initializes health/ gold and gives and suffles deck
 */
Player::Player()
{
    deck_ = new Deck();
    deck_->Shuffle();

    health_[0] = 10;
    health_[1] = 10;
    health_[2] = 10;
    health_[3] = 10;

    gold_ = 3;
    heroCount_ = 0;
}

/**
 * @brief Player::DrawCard draws card from the dack and stores it in side hand Vector
 */
void Player::DrawCard()
{
    if(deck_->getDeck().size() == 0){
        qDebug() << "\nDeck Is Empty!\nYou Lose!";
        return;
    }

    if(hand_.size() < 4){
        hand_.append(deck_->Draw());
    }else{
        qDebug() << "\nHand size is full!";
    }


}

/**
 * @brief Player::shuffle shuffles deck
 */
void Player::shuffle()
{
    this->deck_->Shuffle();
}


/**
 * @brief Player::GetHealthInfo saves health info in a QString and returns it
 * @return QString
 */
QString Player::GetHealthInfo()
{

    QString healthScore = QString(QString::number(health_[0]) + "\n" + "\n" +
                                   QString::number(health_[1]) + "\n" + "\n" +
                                    QString::number(health_[2]) + "\n" + "\n" +
                                    QString::number(health_[3]) );

    return healthScore;
}

/**
 * @brief Player::CatapultHit if called, minues one health from all of players health
 */
void Player::CatapultHit()
{
    if(this->health_[0] > 0 ) this->health_[0]--;
    if(this->health_[1] > 0 ) this->health_[1]--;
    if(this->health_[2] > 0 ) this->health_[2]--;
    if(this->health_[3] > 0 ) this->health_[3]--;
}


/**
 * @brief Player::MinusHealth based the index given, subtracts health
 * @param index  of which health value
 * @param amount decrease by ammount
 */
void Player::MinusHealth(int index, int amount)
{
  this->health_[index] -= amount;
}
