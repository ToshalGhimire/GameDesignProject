#include <QApplication>
#include "game.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    game = new Game();
    game->show();

    game->MainMenu();
    return a.exec();
}
