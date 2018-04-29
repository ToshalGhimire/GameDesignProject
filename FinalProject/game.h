#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>


#include "board.h"
#include "button.h"
#include "Cards/deck.h"
#include "Cards/card.h"
#include "Player/player.h"

class Card;
class Deck;
class Player;


enum class PlayerTurn {one,two,none};

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget* parent=NULL); //constructor

    void MainMenu();

    //public fields (since global class)
    QGraphicsScene * scene_;
    Board * GameBoard;

    //Player player;

    void displayScoreBoard();

public slots:
    void Start();
    void BackToMain();
    void About();
    void EndTurn();
    void draw();
    void Test();
    void Summon();

private:
    QMediaPlayer * Music;
    Deck * testDeck;
    QVector<Card*> hand;

    Player * player_one;
    Player * player_two;
    PlayerTurn turn = PlayerTurn::none;

    QGraphicsTextItem * scoreBoard_ = new QGraphicsTextItem();
    QGraphicsTextItem * scoreBoard_1 = new QGraphicsTextItem();
    QGraphicsTextItem * scoreBoard_2 = new QGraphicsTextItem();
    QGraphicsTextItem * goldCount_ = new QGraphicsTextItem();


};

#endif // GAME_H
