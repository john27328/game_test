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
//    game.stepDangers();
//    game.updateRoom();
//    game.printRoom();
    auto path = game.pathCreate(8,1);
    for(auto p: path)
    {
        qDebug()<<p.x<<p.y<<p.direction;
    }
}
