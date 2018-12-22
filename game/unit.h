#ifndef UNIT_H
#define UNIT_H

#define N_ROOM_X 40
#define N_ROOM_Y 10

enum {STILL, UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT, END_DIR};

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
