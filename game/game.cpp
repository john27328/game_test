#include "game.h"

Game::Game()
{
    clearRoom();

}

void Game::step(Unit *u)
{
    switch (u->direction) {
    case UP:
        u->y++;
        break;
    case DOWN:
        u->y--;
        break;
    case LEFT:
        u->x--;
        break;
    case RIGHT:
        u->x++;
        break;
    default:
        break;
    }
}

void Game::clearRoom()
{
    for(int i = 0; i < N_ROOM_X; i++)
        for(int j = 0; j < N_ROOM_Y; j++)
            room0[i][j] = 0;
}

void Game::printRoom()
{
    for(int j = 0; j < N_ROOM_Y; j++)
    {
        for(int i = 0; i < N_ROOM_X; i++)
            cout << room[i][j];
        cout <<endl;
    }
}

void Game::createGame()
{
    clearRoom();
    for(int i = 0; i < N_ROOM_X; i++)
        room0[i][0] = room0[i][N_ROOM_Y - 1] = WALL;
    for(int j = 0; j < N_ROOM_Y; j++)
        room0[0][j] = room0[N_ROOM_X - 1][j] = WALL;
//test
    for (int i = 1; i < 5; i++)
        room0[6][i] = PIT;
    for (int i = 2; i < 7; i++)
        room0[i][4] = PIT;
    character = new Unit(CHARACTER, 1,1,0);
    dangers.append(new Unit (GUARD, 3,3, LEFT));
    dangers.append(new Unit (GUARD, 1,5, LEFT));
    dangers.append(new Unit (FIREBALL, 5,3, LEFT));
    updateRoom();

}

void Game::createROOM()
{

}

void Game::updateRoom()
{
    for(int i = 0; i < N_ROOM_X; i++)
        for(int j = 0; j < N_ROOM_Y; j++)
            room[i][j] = room0[i][j];
    for (Unit *u:dangers)
        room[u->x][u->y] = u->tipe;
    room[character->x][character->y] = CHARACTER;

}

void Game::stepDangers()
{
qDebug() <<0;
    QMutableListIterator<Unit *> i(dangers);
    while (i.hasNext()) {
        i.next();
        step(i.value());
        if (room0[i.value()->x][i.value()->y] == WALL )
            i.remove();
    }
}

void Game::stepCharacter()
{

}

QList<Unit> Game::pathCreate(int x, int y)
{
    bool stop = 0;
    QList<QList<Unit>> pathList;
    QList<Unit> start;
    QList<Unit> path;
    start << *character;
    pathList << start;
    int roomPath[N_ROOM_X][N_ROOM_Y];
    for(int i = 0; i < N_ROOM_X; i++)
        for(int j = 0; j < N_ROOM_Y; j++)
            roomPath[i][j] = room0[i][j];
    while (!stop)
    {
        QList<QList<Unit>> pathListNext;
        if (pathList.isEmpty())
        {
            stop = 1;
            qDebug()<< "пути нет";
        }
//        qDebug()<<"****";
        for(auto p: pathList)
        {
            int x0 = p.last().x;
            int y0 = p.last().y;
//            qDebug()<<x0 <<y0;
            for (int d = 1; d <=4; d++)
            {

                QList<Unit> temp = p;
                Unit st(CHARACTER,x0,y0,d);
                step(&st);
                if (roomPath[st.x][st.y] != PIT && roomPath[st.x][st.y] != WALL)
                {
                    temp << st;
                    pathListNext << temp;
                    roomPath[st.x][st.y] = PIT;
                    if (st.x == x && st.y == y)
                    {
                        path = temp;
                        stop = 1;
                        break;
                    }
                }


            }

        }
        pathList = pathListNext;
    }
    return path;
}
