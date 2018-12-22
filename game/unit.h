#ifndef UNIT_H
#define UNIT_H

#define N_ROOM_X 40
#define N_ROOM_Y 10
enum {SPACE, CHARACTER, PIT, WALL, GUARD, FIREBALL, GUN, FINISH};
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

class Gun: public Unit
{
public:
    Gun(int x, int y, int direction, int phase);
    int phase;
};

#endif // UNIT_H
