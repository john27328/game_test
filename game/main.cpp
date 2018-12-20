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
    game.pathCreate(8,1);
    for (int i = 0; i <3; i++)
    {
        cout <<"step" << endl;
        game.step();
        cout << "room" << endl;
        game.printRoom();
//        qDebug()<< "path";
//        game.printPath();
    }


//    game.printPath();

    return 0;
}
