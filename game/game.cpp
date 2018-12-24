#include "game.h"

Game::Game()
{
    createGame();

}

void Game::stepUnit(Unit *u)
{
    switch (u->direction) {
    case UP:
        u->y--;
        if (u->tipe == GUARD) u->direction = DOWN;
        break;
    case DOWN:
        u->y++;
        if (u->tipe == GUARD) u->direction = UP;
        break;
    case LEFT:
        u->x--;
        if (u->tipe == GUARD) u->direction = RIGHT;
        break;
    case RIGHT:
        u->x++;
        if (u->tipe == GUARD) u->direction = LEFT;
        break;
    case UP_LEFT:
        u->x--;
        u->y--;
        break;
    case UP_RIGHT:
        u->x++;
        u->y--;
        break;
    case DOWN_LEFT:
        u->x--;
        u->y++;
        break;
    case DOWN_RIGHT:
        u->x++;
        u->y++;
        break;
    default:
        break;
    }



}

void Game::clearRoom()
{
    guns.clear();
    dangers.clear();
    for(int i = 0; i < N_ROOM_X; i++)
        for(int j = 0; j < N_ROOM_Y; j++){
            room0[i][j] = room[i][j] = 0;
            roomDir[i][j] = 0;
        }
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
    gameStatus = PLAY;
    srand(time(NULL));
    for(int i = 0; i < N_ROOM_X; i++){
        room0[i][0] = room0[i][N_ROOM_Y - 1] = WALL; //рисую стены
        roomDir[i][0] = DOWN;
        roomDir[i][N_ROOM_Y -1] = UP;
        if (rand()%99 < GUN_DENSITY) guns.append(new Gun (i, 0, DOWN, rand()%GUNS_RATE)); // ставлю пушки
        if (rand()%99 < GUN_DENSITY) guns.append(new Gun (i, N_ROOM_Y - 1, UP, rand()%GUNS_RATE)); // ставлю пушки
    }
    for(int j = 0; j < N_ROOM_Y; j++){
        room0[0][j] = room0[N_ROOM_X - 1][j] = WALL; //рисую стены
        roomDir[0][j] = RIGHT;
        roomDir[N_ROOM_X - 1][j] = LEFT;
        if (rand()%99 < GUN_DENSITY) guns.append(new Gun (0, j, RIGHT, rand()%GUNS_RATE)); // ставлю пушки
        if (rand()%99 < GUN_DENSITY) guns.append(new Gun (N_ROOM_X - 1, j, LEFT, rand()%GUNS_RATE)); // ставлю пушки
    }
    roomDir[0][0] = DOWN_RIGHT;
    roomDir[0][N_ROOM_Y-1] = DOWN_LEFT;
    roomDir[N_ROOM_Y - 1][0] = UP_RIGHT;
    roomDir[N_ROOM_Y - 1][N_ROOM_Y-1] = UP_LEFT;
//test
    //    for (int i = 1; i < 5; i++)
    //        room0[6][i] = PIT;
    //    for (int i = 2; i < 7; i++)
    //        room0[i][4] = PIT;

    character = new Unit(CHARACTER, 1,1,0);
    path.clear();
    room0[N_ROOM_X - 2][N_ROOM_Y - 2] = FINISH;
    for(int i = 1; i < N_ROOM_X-1; i++)
        for(int j = 1; j < N_ROOM_Y-1; j++)
        {
            if ((i > 3 || j > 3) && (i < N_ROOM_X - 2 || j < N_ROOM_Y -2))
                if (rand()%99 < GUARD_DENSITY) dangers.append(new Unit (GUARD, i,j, 1 + (rand()%4)));
        }

    updateRoom();

}


void Game::updateRoom()
{
    for(int i = 0; i < N_ROOM_X; i++)
        for(int j = 0; j < N_ROOM_Y; j++){
            room[i][j] = room0[i][j];
        }
    for (Unit *u:dangers)
    {
        room[u->x][u->y] = u->tipe;
        roomDir[u->x][u->y] = u->direction;
    }
    for (auto u:guns)
    {
        room[u->x][u->y] = GUN;
        roomDir[u->x][u->y] = u->direction;

    }
    if (room[character->x][character->y] == FIREBALL || room[character->x][character->y] == GUARD)
    {
        gameStatus = DEAD;
        qDebug()<<"game over";
    }
    else if(room[character->x][character->y] == FINISH){
        gameStatus = WIN;
        qDebug()<<"win";
    }
    else
    {
        room[character->x][character->y] = CHARACTER;
        roomDir[character->x][character->y] = character->direction;
    }
    for(int i = 0; i < N_ROOM_X; i++){
        roomDir[i][0] = DOWN;
        roomDir[i][N_ROOM_Y -1] = UP;
    }
    for(int j = 0; j < N_ROOM_Y; j++){
        roomDir[0][j] = RIGHT;
        roomDir[N_ROOM_X - 1][j] = LEFT;
    }
    roomDir[0][0] = DOWN_RIGHT;
    roomDir[0][N_ROOM_Y-1] = UP_RIGHT;
    roomDir[N_ROOM_X - 1][0] = DOWN_LEFT;
    roomDir[N_ROOM_X - 1][N_ROOM_Y-1] = UP_LEFT;

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

    for (auto u : guns)
    {
        u->phase++;
        if (u->phase == GUNS_RATE){
            u->phase = 0;
            dangers.append(new Unit(FIREBALL,u->x,u->y, u->direction));
        }
    }
}

void Game::stepCharacter()
{
    if(path.isEmpty())
    {
//        qDebug()<<"не двигается";
        character->direction = STILL;
    }
    else {
        auto tmp = path.takeFirst();
//        qDebug() << "stepChar" << tmp.x << tmp.y;
        character->x = tmp.x;
        character->y = tmp.y;
        character->direction = tmp.direction;
    }
}

void Game::pathCreate(int x, int y)
{
    //шаг за шагом проверяю все возможные сдвиги героя во все стороны,
    //помечая пройденые клетки как помечанные и запоминая не тупиковые пути.
    //Когда герой достигает точки назначения прерываю цикл и возвращаю последний путь.
    //Если не осталось доступных путей, а точка не достигнута, возвращаю пустой путь.
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
    if (character->x != x || character->y != y)
        while (!stop)
        {
            QList<QList<Unit>> pathListNext;
            if (pathList.isEmpty())
            {
                stop = 1;
                qDebug()<< "пути нет";
                gameStatus = BRICK;
            }
            //        qDebug()<<"****";
            for(auto p: pathList)
            {
                int x0 = p.last().x;
                int y0 = p.last().y;
//                            qDebug()<<x0 <<y0;
                for (int d = 1; d <=END_DIR - 1; d++)
                {
//                    qDebug()<<d;
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
                            gameStatus = GOING;
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

int Game::getRoomDir(int x, int y)
{
    return roomDir[x][y];
}

void Game::setRoom(int x, int y)
{
//    qDebug() << room0[x][y];
    if (room0[x][y] == SPACE)
        room0[x][y] = PIT;
    else if (room0[x][y] == PIT)
        room0[x][y] = SPACE;
    updateRoom();

}
