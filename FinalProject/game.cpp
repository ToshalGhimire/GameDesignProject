#include "game.h"
#include "board.h"

Game::Game(QWidget *parent)
{
    //set screen
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setFixedSize(1024,768);

   //set scene

   scene_ = new QGraphicsScene();
   scene_->setSceneRect(0,0,1024,768);
   setScene(scene_);

   //Music = new QMediaPlayer(); MUSIC


}

void Game::Start()
{
    //Music->pause(); MUSIC

    scene_->clear();

    GameBoard = new Board();
    GameBoard->MakeBoard(100,100);

    //Back button
    Button * BackButton = new Button(QString("<- Back"));
    int backPos_X = this->width() - 250;
    int backpos_Y = 100;
    BackButton->setPos(backPos_X,backpos_Y);
    scene_->addItem(BackButton);
    connect(BackButton,SIGNAL(clicked()),this,SLOT(BackToMain()));
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

void Game::Test()
{
  scene_->clear();

  testDeck = new Deck();

  testDeck->displayDeck();
  scene_->addItem(testDeck->Draw());
  testDeck->displayDeck();
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
   QFont titlefont("Arial Black",30);
   title->setFont(titlefont);
   int txpos = this->width()/2 - title->boundingRect().width()/2;
   int typos = 150;
   title->setPos(txpos,typos);
   scene_->addItem(title);

   //Play button
   Button * PlayButton = new Button(QString("Play"));
   int playPos_X = this->width()/2 - title->boundingRect().width()/2;
   int playPos_Y = 310;
   PlayButton->setPos(playPos_X,playPos_Y);

   connect(PlayButton,SIGNAL(clicked()),this,SLOT(Start()));
   scene_->addItem(PlayButton);

   //About button
   Button * AboutButton = new Button(QString("About"));
   int aboutPos_X = this->width()/2 - title->boundingRect().width()/2;
   int aboutPos_Y = 370;
   AboutButton->setPos(aboutPos_X,aboutPos_Y);

   connect(AboutButton,SIGNAL(clicked()),this,SLOT(About()));
   scene_->addItem(AboutButton);

   //Exit button
   Button * ExitButton = new Button(QString("Exit"));
   int exitPos_X = this->width()/2 - title->boundingRect().width()/2;
   int exitPos_Y = 430;
   ExitButton->setPos(exitPos_X,exitPos_Y);

   connect(ExitButton,SIGNAL(clicked()),this,SLOT(close()));
   scene_->addItem(ExitButton);

   //Test button
   Button * TestButton = new Button(QString("Test Code"));
   int TestPos_X = this->width()/2 - title->boundingRect().width()/2;
   int TestPos_Y = 490;
   TestButton->setPos(TestPos_X,TestPos_Y);

   connect(TestButton,SIGNAL(clicked()),this,SLOT(Test()));
   scene_->addItem(TestButton);
}



