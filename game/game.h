#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QList>
#include "unit.h"
#include <QDebug>
#define N_ROOM_X 40
#define N_ROOM_Y 10
enum {SPACE, CHARACTER, PIT, WALL, GUARD, FIREBALL};

using namespace std;
class Game
{
public:
    Game();
private:
    int room0[N_ROOM_X][N_ROOM_Y];
    int room[N_ROOM_X][N_ROOM_Y];
    QList <Unit *> dangers;
    Unit *character;
    QList <int> path;
    void step(Unit *u);
public:
    void clearRoom();
    void printRoom();
    void createGame();
    void createROOM();
    void updateRoom();
    void stepDangers();
    void stepCharacter();
    QList<Unit> pathCreate(int x, int y);

};

#endif // GAME_H
