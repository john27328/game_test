#include "unit.h"

Unit::Unit(int tipeU, int xU, int yU, int directionU)
{
    tipe = tipeU;
    x = xU;
    y = yU;
    direction = directionU;
}


Gun::Gun(int x, int y, int direction, int phaseU): Unit(GUN, x, y, direction)
{
    phase = phaseU;
}
