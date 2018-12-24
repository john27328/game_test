#ifndef GAME_H
#define GAME_H

/***********************************************************************************************
 * В данном классе производится создание уровней, обработка движения и взаимодействия объектов  *
 * *********************************************************************************************/

#include <iostream>
#include <QList>
#include "unit.h"
#include <QDebug>
#define TIME 300
#define N_ROOM_X 30
#define N_ROOM_Y 30
#define GUN_DENSITY 15
#define GUNS_RATE 25
#define GUARD_DENSITY 5
enum {PLAY, DEAD, WIN, GOING, BRICK };

using namespace std;
class Game
{
public:
    Game();
private:
    int room0[N_ROOM_X][N_ROOM_Y]; // описание фона и препядствий
    int room[N_ROOM_X][N_ROOM_Y]; // фон со всем объектами для отрисовки и взаимодействий
    int roomDir[N_ROOM_X][N_ROOM_Y]; // карта направлений объектов для отрисовки
    QList <Unit *> dangers; // список объектов, убивающих героя
    QList <Gun *> guns; // пушки
    Unit *character; // Солид Снейк - главный герой
    void stepUnit(Unit *u); // рассчет перемещений объектов
    QList<Unit> path; // хранит маршрут для перемещения героя

public:
    void clearRoom();
    void printRoom(); // тестовая функция
    void createGame(); // создание уровня
    void updateRoom(); // нанесение объектов на карту
    void stepDangers();
    void stepCharacter();
    void pathCreate(int x, int y); // рассчитывает крайчайший путь с учетом препятствий
    void printPath(); // тестовая функция
    void step();
    int getRoom(int x, int y);
    int getRoomDir(int x, int y);
    void setRoom(int x, int y); //
    int xTerminal, yTerminal; // хранит точку назначения героя
    int gameStatus;

};

#endif // GAME_H
