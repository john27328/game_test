#ifndef UNIT_H
#define UNIT_H

#define N_ROOM_X 40
#define N_ROOM_Y 10

#define STILL 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class Unit
{
public:
    Unit(int tipe, int x, int y, int direction);
    int tipe;
    int x;
    int y;
    int direction;
};

#endif // UNIT_H
