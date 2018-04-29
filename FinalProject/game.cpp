#include "game.h"
#include "board.h"
#include "game.h"

Game::Game(QWidget *parent)
{
    std::srand(unsigned(std::time(0)));
   //set screen
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setFixedSize(768,1000);

   //set scene
   scene_ = new QGraphicsScene();
   scene_->setSceneRect(0,0,768,1000);
   setScene(scene_);
   //Music = new QMediaPlayer(); MUSIC
}

void Game::Start()
{
    //Music->pause(); MUSIC
    scene_->clear();

    //create board
    Board& GameBoard = Board::getInstance();
//    GameBoard->MakeBoard(2,2);
    GameBoard.MakeBoard(120,130);

    //create players
    player_one = new Player();
    player_two = new Player();

    player_one->shuffle();
    player_two->shuffle();

    turn = PlayerTurn::one;

    displayScoreBoard();

    //Quit button
    Button * QuitButton = new Button(QString("Quit"));
    QuitButton->setPos(20,40);
    scene_->addItem(QuitButton);
    connect(QuitButton,SIGNAL(clicked()),this,SLOT(BackToMain()));

    //End Turn button
    Button * EndTurnButton = new Button(QString("End Turn"));
//    EndTurnButton->setPos(1250,700);
    EndTurnButton->setPos(531,935);
    scene_->addItem(EndTurnButton);
    connect(EndTurnButton,SIGNAL(clicked()),this,SLOT(EndTurn()));

    //Draw Button
    Button * drawButton = new Button(QString("Draw"));
    drawButton->setPos(294,935);
//    drawButton->setPos(1025,700);
    connect(drawButton,SIGNAL(clicked()),this,SLOT(draw()));
    scene_->addItem(drawButton);

    //Summon Button
    Button * summonButton = new Button(QString("Summon"));
    summonButton->setPos(57,935);
    connect(summonButton,SIGNAL(clicked()),this,SLOT(Summon()));
    scene_->addItem(summonButton);

    //add gold icon
    QString filename = ":/card/Coins.png";
    QImage image(filename);

    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    item->setPos(560,43);
    item->setScale(.3);
    scene_->addItem(item);
}

void Game::displayScoreBoard(){

    QString p1 = player_one->GetHealthInfo();
    QString p2 = player_two->GetHealthInfo();

    QString p1_gold = QString::number(player_one->GetGold());
    QString p2_gold = QString::number(player_two->GetGold());

    QString goldString,turnString;

    int myColor;

    if(turn == PlayerTurn::one){
        turnString = QString("Player 1");
        goldString = p1_gold;
        myColor = 0;

    }else if(turn == PlayerTurn::two){
        turnString = QString("Player 2");
        goldString = p2_gold;
        myColor = 1;

    }else {
        turnString = QString("No One's Turn");
        myColor = 2;
    }

//    QString score = QString(p1 + " | " + turnString + " | " + p2);
    QString score = QString(turnString);
    QString score_health1 = QString(p1);
    QString score_health2 = QString(p2);

    scene_->removeItem(scoreBoard_);
    scene_->removeItem(goldCount_);

    goldCount_ = new QGraphicsTextItem(goldString);
    scoreBoard_ = new QGraphicsTextItem(score);
    scoreBoard_1 = new QGraphicsTextItem(score_health1);
    scoreBoard_2 = new QGraphicsTextItem(score_health2);

    QFont scoreFont("Avenir",30);
    QFont goldFont("Avenir",30);
    QFont healthFont("Avenir",21);
    scoreBoard_->setFont(scoreFont);
    goldCount_->setFont(goldFont);
    scoreBoard_1->setFont(healthFont);
    scoreBoard_2->setFont(healthFont);

    goldCount_->setDefaultTextColor(QColor(200,100,10, 245));
    if(myColor == 0){
        scoreBoard_->setDefaultTextColor(QColor(200,10,10, 245));
    }
    else if(myColor == 1){
        scoreBoard_->setDefaultTextColor(QColor(10,10,200, 245));
    }


    scene_->addItem(goldCount_);
    scene_->addItem(scoreBoard_);
    scene_->addItem(scoreBoard_1);
    scene_->addItem(scoreBoard_2);

    scoreBoard_->setPos(325, 40);
    scoreBoard_1->setPos(50, 255);
    scoreBoard_2->setPos(670, 255);
    goldCount_->setPos(610, 40);
//    scoreBoard_->setPos(325, -50);
//    goldCount_->setPos(610,-50);

    //scene_->addText(turnString);
}

void Game::BackToMain()
{
    scene_->clear();
    MainMenu();
}

void Game::About()
{
   scene_->clear();

   QGraphicsTextItem * about = new QGraphicsTextItem(QString("This is my final project for both CSCI 3010 and for ATLS 4040."
                                                             "\nDesigning This game is the final project for Game Design."
                                                             "\nImplementing a game is the final for Programing Project Workshop."
                                                             "\n\nProgram created using QT - Currently Under Development"
                                                             "\n\tProgrammers: Toshal Ghimire, Pujan Tandukar"
                                                             "\n\tDesigners: Liam Slyne ,Toshal Ghimire, Rasmi Lamichhane"));
   QFont titlefont("comic sans",20);
   about->setFont(titlefont);

   scene_->addItem(about);

   //Back button
   Button * BackButton = new Button(QString("Back"));
   int backPos_X = this->width() - 250;
   int backpos_Y = 400;
   BackButton->setPos(backPos_X,backpos_Y);
   scene_->addItem(BackButton);
   connect(BackButton,SIGNAL(clicked()),this,SLOT(BackToMain()));


}

QString strify(PlayerTurn n){
    switch (n){
    case PlayerTurn::none:
        return QString("none");
    case PlayerTurn::one:
        return QString("one");
    case PlayerTurn::two:
        return QString("two");
    default:
        return QString("Invalid Enum");


    }
}

void Game::EndTurn()
{
    for(auto i: player_one->hand_) scene_->removeItem(i);//remove everything player one
    for(auto i: player_two->hand_) scene_->removeItem(i);//remove everything player two

    if(turn == PlayerTurn::one){
       turn = PlayerTurn::two;
       player_two->PlusGold(1);
    } else if(turn == PlayerTurn::two){
       turn = PlayerTurn::one;
       player_one->PlusGold(1);
    }
    displayScoreBoard();

    qDebug()<< strify(turn);

    Card::clearClickedItem();

}

void Game::Summon(){
    if(Card::GetClickedItem() == NULL){
            qDebug() << "Please Select Card First!";
            return;
        }

        if(turn == PlayerTurn::one){
            //player ones summon
            Tile * HeroTile = new Tile();
            Card * carditem = Card::GetClickedItem();
            //checks if players can afford that item or not
            if(player_one->GetGold() < carditem->get_CardData().manaCost){
                qDebug() << "Cant Afford this item!";
                return;
            } else{
                //if player can afford it then
                player_one->MinusGold(carditem->get_CardData().manaCost);
                displayScoreBoard();

                CardData temp = carditem->get_CardData();
                HeroTile->MakeHero(&temp,tileOwner::one);
                HeroTile->setFlag(QGraphicsItem::ItemIsMovable);

                for(auto i : player_one->hand_){
                    if (i == carditem){
                        player_one->hand_.removeOne(carditem);
                    }
                }
                player_one->onField_.push_back(HeroTile);
                scene_->addItem(HeroTile);
                scene_->removeItem(carditem);

                HeroTile->setPos(0,0);
            }

        } else if (turn == PlayerTurn::two){
            Tile * HeroTile = new Tile();
            Card * carditem = Card::GetClickedItem();

            //checks if players can afford that item or not
            if(player_two->GetGold() < carditem->get_CardData().manaCost){
                qDebug() << "Cant Afford this item!";
                return;
            }else{
                //if player can afford it then
                player_two->MinusGold(carditem->get_CardData().manaCost);
                displayScoreBoard();

                for(auto i : player_two->hand_){
                    if (i == carditem){
                        player_two->hand_.removeOne(carditem);
                    }
                }

                CardData temp = carditem->get_CardData();
                HeroTile->MakeHero(&temp,tileOwner::two);
                HeroTile->setFlag(QGraphicsItem::ItemIsMovable);

                player_two->onField_.push_back(HeroTile);
                scene_->addItem(HeroTile);
                scene_->removeItem(carditem);

                HeroTile->setPos(0,0);
            }
        }

        Card::clearClickedItem();
}

qreal yy = 0;
void Game::draw()
{

    if(turn == PlayerTurn::one){
        for(auto i: player_one->hand_) scene_->removeItem(i);//remove everything player one
        for(auto i: player_two->hand_) scene_->removeItem(i);//remove everything player two

        qreal xx = 0;
        player_one->DrawCard();
        for(auto i: player_one->hand_){
            i->setPos(55 + xx,700);
            scene_->addItem(i);
            xx += 170;
        }
    } else if (turn == PlayerTurn::two){

        for(auto i: player_one->hand_) scene_->removeItem(i);//remove everything player one
        for(auto i: player_two->hand_) scene_->removeItem(i);//remove everything player two

        qreal xx = 0;
        player_two->DrawCard();
        for(auto i: player_two->hand_){
            i->setPos(55 + xx,700);
            scene_->addItem(i);
            xx += 170;
        }
    }

//    xx += 158;

//    if(xx >= 1350){
//        xx = -430;
//        yy += 220;
//    }

//    for(Card * i : hand){





//        scene_->addItem(i);
//    }

    //testDeck->displayDeck();

}

void Game::Test()
{
  scene_->clear();

  Button * drawButton = new Button(QString("Draw"));
  int DrawPos_X = this->width()/2 - drawButton->boundingRect().width()/2;
  int DrawPos_Y = 370;
  drawButton->setPos(DrawPos_X,DrawPos_Y);
  connect(drawButton,SIGNAL(clicked()),this,SLOT(draw()));
  scene_->addItem(drawButton);



  testDeck = new Deck();


}

void Game::MainMenu()
{

//MUSIC
//    if(Music->state() == QMediaPlayer::PlayingState){
//        Music->play();
//    }else{
//       Music->setMedia(QUrl("qrc:/Sounds/backgroundMusic"));
//       Music->play();
//       Music->setVolume(10);

//    }
   //title
   QGraphicsTextItem * title = new QGraphicsTextItem(QString("Final Project (Title TBD)"
                                                             "\nCSCI 3010 & ATLS 4040"));
//   QFont titlefont("Arial Black",30);
   QFont titlefont("Avenir",30);
   title->setFont(titlefont);
   int txpos = this->width()/2 - title->boundingRect().width()/2;
   int typos = 170;
   title->setPos(txpos,typos);
   scene_->addItem(title);

   //Play button
   Button * PlayButton = new Button(QString("Play"));
   int playPos_X = this->width()/2 - title->boundingRect().width()/2;
   int playPos_Y = 300;
   PlayButton->setPos(playPos_X,playPos_Y);

   connect(PlayButton,SIGNAL(clicked()),this,SLOT(Start()));
   scene_->addItem(PlayButton);

   //About button
   Button * AboutButton = new Button(QString("About"));
   int aboutPos_X = this->width()/2 - title->boundingRect().width()/2;
   int aboutPos_Y = 360;
   AboutButton->setPos(aboutPos_X,aboutPos_Y);

   connect(AboutButton,SIGNAL(clicked()),this,SLOT(About()));
   scene_->addItem(AboutButton);

   //Exit button
   Button * ExitButton = new Button(QString("Exit"));
   int exitPos_X = this->width()/2 - title->boundingRect().width()/2;
   int exitPos_Y = 420;
   ExitButton->setPos(exitPos_X,exitPos_Y);

   connect(ExitButton,SIGNAL(clicked()),this,SLOT(close()));
   scene_->addItem(ExitButton);

   //Test button
   Button * TestButton = new Button(QString("Test Code"));
   int TestPos_X = this->width()/2 - title->boundingRect().width()/2;
   int TestPos_Y = 480;
   TestButton->setPos(TestPos_X,TestPos_Y);

   connect(TestButton,SIGNAL(clicked()),this,SLOT(Test()));
   scene_->addItem(TestButton);
}



