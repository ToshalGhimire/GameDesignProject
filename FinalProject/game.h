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

private:
    QMediaPlayer * Music;
    Deck * testDeck;
    QVector<Card*> hand;

    Player * player_one;
    Player * player_two;
    PlayerTurn turn = PlayerTurn::none;

    QGraphicsTextItem * scoreBoard = new QGraphicsTextItem();


};

#endif // GAME_H
