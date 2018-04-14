#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>


#include "board.h"
#include "button.h"
#include "Cards/deck.h"
#include "Cards/card.h"

class Deck;


enum class Player {one,two,none};

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

public slots:
    void Start();
    void BackToMain();
    void About();

    void Test();

private:
    QMediaPlayer * Music;
    Deck * testDeck;

};

#endif // GAME_H
