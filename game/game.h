#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QList>
#include "unit.h"
#include <QDebug>
#define N_ROOM_X 30
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
    void stepUnit(Unit *u);
    QList<Unit> path;
public:
    void clearRoom();
    void printRoom();
    void createGame();
    void createROOM();
    void updateRoom();
    void stepDangers();
    void stepCharacter();
    void pathCreate(int x, int y);
    void printPath();
    void step();

};

#endif // GAME_H
