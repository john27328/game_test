#include "screen.h"

Screen::Screen(QWidget *parent) : QWidget(parent)
{
    t=new QTimer;
    connect(t,SIGNAL(timeout()),this,SLOT(step()));
}

void Screen::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPen pen;
    QBrush brush;
    double w=width(), h=height(), wr=w/N_ROOM_X, hr=h/ N_ROOM_Y;
    for(int i = 0; i < N_ROOM_X; i++)
        for(int j = 0; j < N_ROOM_Y; j++)
        {
            switch (game.getRoom(i,j)) {
            case SPACE:
                pen.setColor(Qt::white);
                brush.setColor(Qt::white);
                break;
            case CHARACTER:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            case PIT:
                pen.setColor(Qt::black);
                brush.setColor(Qt::black);
                break;
            case WALL:
                pen.setColor(Qt::gray);
                brush.setColor(Qt::gray);
                break;
            case GUARD:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case FIREBALL:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            default:
                break;
            }
            paint.setPen(pen);
            paint.setBrush(brush);
            paint.drawRect(QRect(wr*i,hr*j,wr,hr));
        }




}

void Screen::startT()
{
    qDebug()<<"start";
    t->start(500);
    game.createGame();
}

void Screen::stopT()
{
    t->stop();
}

void Screen::step()
{
    qDebug()<<"step";
    game.step();
    update();
}
