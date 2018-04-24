#include "player.h"
#include <QDebug>

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

void Player::DrawCard()
{
    if(deck_->getDeck().size() == 0){
        qDebug() << "Deck Is Empty!\nYou Lose!";
        return;
    }

    if(hand_.size() < 4){
        hand_.append(deck_->Draw());
    }else{
        qDebug() << "Hand size is full!";
    }


}

void Player::shuffle()
{
    this->deck_->Shuffle();
}

QString Player::GetHealthInfo()
{

    QString healthScore = QString(QString::number(health_[0]) + " - " +
                                   QString::number(health_[0]) + " - " +
                                    QString::number(health_[0]) + " - " +
                                    QString::number(health_[0]) );

    return healthScore;
}
