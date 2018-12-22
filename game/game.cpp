#include "game.h"

Game::Game()
{
    clearRoom();

}

void Game::stepUnit(Unit *u)
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
    case UP_LEFT:
        u->x--;
        u->y++;
        break;
    case UP_RIGHT:
        qDebug()<<"UP_RIGHT";
        u->x++;
        u->y++;
        break;
    case DOWN_LEFT:
        u->x--;
        u->y--;
        break;
    case DOWN_RIGHT:
        u->x++;
        u->y--;
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
    cout << endl;
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
    QMutableListIterator<Unit *> i(dangers);
    while (i.hasNext()) {
        i.next();
        stepUnit(i.value());
        if (room0[i.value()->x][i.value()->y] == WALL )
            i.remove();
    }
}

void Game::stepCharacter()
{
    if(path.isEmpty())
    {
        qDebug()<<"не двигается";
        character->direction = STILL;
    }
    else {
        auto tmp = path.takeFirst();
        qDebug() << "stepChar" << tmp.x << tmp.y;
        character->x = tmp.x;
        character->y = tmp.y;
        character->direction = tmp.direction;
    }
}

void Game::pathCreate(int x, int y)
{
    xTerminal = x; yTerminal = y;
    bool stop = 0;
    QList<QList<Unit>> pathList;
    QList<Unit> start;
    start << *character;
    pathList << start;
    path.clear();
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
            for (int d = 1; d <=END_DIR - 1; d++)
            {
                qDebug()<<d;
                QList<Unit> temp = p;
                Unit st(CHARACTER,x0,y0,d);
                stepUnit(&st);
                if (roomPath[st.x][st.y] != PIT && roomPath[st.x][st.y] != WALL)
                {
                    temp << st;
                    pathListNext << temp;
                    roomPath[st.x][st.y] = PIT;
                    if (st.x == x && st.y == y)
                    {
                        temp.removeFirst();
                        path = temp;
                        stop = 1;
                        break;
                    }
                }


            }

        }
        pathList = pathListNext;
    }
}

void Game::printPath()
{
    for(auto p: path)
    {
        qDebug()<<p.x<<p.y<<p.direction;
    }
}

void Game::step()
{
    stepDangers();
    stepCharacter();
    updateRoom();
}

int Game::getRoom(int x, int y)
{
    return room[x][y];
}

void Game::setRoom(int x, int y)
{
    qDebug() << room0[x][y];
    if (room0[x][y] == SPACE)
        room0[x][y] = PIT;
    else if (room0[x][y] == PIT)
        room0[x][y] = SPACE;
    updateRoom();

}
