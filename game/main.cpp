#include "widget.h"
#include <QApplication>
#include "game.h"


int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    Widget w;
//    w.show();

//    return a.exec();
    Game game;
    game.createGame();
    game.updateRoom();
    game.printRoom();
    game.stepDangers();
    game.updateRoom();
    game.printRoom();
}
