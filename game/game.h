#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QList>
#include "unit.h"
#include <QDebug>
#define N_ROOM_X 30
#define N_ROOM_Y 30
#define GUN_DENSITY 10
#define GUNS_RATE 35

using namespace std;
class Game
{
public:
    Game();
private:
    int room0[N_ROOM_X][N_ROOM_Y];
    int room[N_ROOM_X][N_ROOM_Y];
    QList <Unit *> dangers;
    QList <Gun *> guns;
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
    int getRoom(int x, int y);
    void setRoom(int x, int y);
    int xTerminal, yTerminal;

};

#endif // GAME_H
