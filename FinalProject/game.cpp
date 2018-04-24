#include "game.h"
#include "board.h"
#include "game.h"

Game::Game(QWidget *parent)
{
   //set screen
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setFixedSize(1500,768);

   //set scene
   scene_ = new QGraphicsScene();
   scene_->setSceneRect(0,0,1500,768);
   setScene(scene_);

   //Music = new QMediaPlayer(); MUSIC


}

void Game::Start()
{
    //Music->pause(); MUSIC
    scene_->clear();

    //create board
    GameBoard = new Board();
    GameBoard->MakeBoard(30,50);

    //create players
    player_one = new Player();
    player_two = new Player();

    player_one->shuffle();
    player_two->shuffle();

    turn = PlayerTurn::one;

    displayScoreBoard();

    //Quit button
    Button * QuitButton = new Button(QString("Quit"));
    int backPos_X = this->width() - 250;
    int backpos_Y = 100;
    QuitButton->setPos(20,700);
    scene_->addItem(QuitButton);
    connect(QuitButton,SIGNAL(clicked()),this,SLOT(BackToMain()));

    //End Turn button
    Button * EndTurnButton = new Button(QString("End Turn"));
    EndTurnButton->setPos(1250,700);
    scene_->addItem(EndTurnButton);
    connect(EndTurnButton,SIGNAL(clicked()),this,SLOT(EndTurn()));

    //Draw Button
    Button * drawButton = new Button(QString("Draw"));
    drawButton->setPos(1025,700);
    connect(drawButton,SIGNAL(clicked()),this,SLOT(draw()));
    scene_->addItem(drawButton);

    //add gold icon
    QString filename = ":/card/Coins.png";
    QImage image(filename);

    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    item->setPos(580,620);
    scene_->addItem(item);





}

void Game::displayScoreBoard(){

    QString p1 = player_one->GetHealthInfo();
    QString p2 = player_two->GetHealthInfo();


    QString p1_gold = QString::number(player_one->GetGold());
    QString p2_gold = QString::number(player_two->GetGold());

    QString goldString,turnString;


    if(turn == PlayerTurn::one){
        turnString = QString("Player 1 Turn");
        goldString = p1_gold;
    }else if(turn == PlayerTurn::two){
        turnString = QString("Player 2 Turn");
        goldString = p2_gold;

    }else {
        turnString = QString("No One's Turn");
    }

    QString score = QString(p1 + " | " + turnString + " | " + p2);

    scene_->removeItem(scoreBoard_);
    scene_->removeItem(goldCount_);

    goldCount_ = new QGraphicsTextItem(goldString);
    scoreBoard_ = new QGraphicsTextItem(score);

    QFont scoreFont("impact",20);
    QFont goldFont("impact",70);
    scoreBoard_->setFont(scoreFont);
    goldCount_->setFont(goldFont);

    goldCount_->setDefaultTextColor(QColor(255,223,0, 245));

    scene_->addItem(goldCount_);
    scene_->addItem(scoreBoard_);

    scoreBoard_->setPos(800, 0);
    goldCount_->setPos(720,610);

    player_one->PlusGold(1); //DEBUG
    player_two->PlusGold(2); //DEBUG

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

    player_one->hand_.clear();
    player_two->hand_.clear();

    if(turn == PlayerTurn::one){
       turn = PlayerTurn::two;
    } else if(turn == PlayerTurn::two){
       turn = PlayerTurn::one;
    }
    displayScoreBoard();

    qDebug()<< strify(turn);

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
            i->setPos(750 + xx,300);
            scene_->addItem(i);
            xx += 170;
        }


    } else if (turn == PlayerTurn::two){

        for(auto i: player_one->hand_) scene_->removeItem(i);//remove everything player one
        for(auto i: player_two->hand_) scene_->removeItem(i);//remove everything player two

        qreal xx = 0;
        player_two->DrawCard();
        for(auto i: player_two->hand_){
            i->setPos(750 + xx,300);
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



