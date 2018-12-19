#include "game.h"

Game::Game()
{
    clearRoom();

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
        switch (i.value()->direction) {
        case UP:
            i.value()->y++;
            break;
        case DOWN:
            i.value()->y--;
            break;
        case LEFT:
            i.value()->x--;
            break;
        case RIGHT:
           i.value()->x++;
            break;
        default:
            break;
        }
        if (room0[i.value()->x][i.value()->y] == WALL )
            i.remove();
    }
}

void Game::stepCharacter()
{

}

void Game::pathCreate(int x, int y, int d)
{
    for (int i = 1; i <= 4; i++)
    {

    }
}
