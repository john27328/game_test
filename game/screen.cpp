#include "screen.h"

Screen::Screen(QWidget *parent) : QWidget(parent)
{
    t=new QTimer;
    connect(t,SIGNAL(timeout()),this,SLOT(step()));
}

void Screen::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
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
            case GUN:
                pen.setColor(Qt::darkRed);
                brush.setColor(Qt::darkRed);
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
    t->start(100);
    game.createGame();
    game.pathCreate(8,1);
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

void Screen::mousePressEvent(QMouseEvent *pe)
{
    double xm = pe->x(), ym=pe->y();
    double w=width(), h=height(), wr=w/N_ROOM_X, hr=h/ N_ROOM_Y;
    double x = int(xm/wr);
    double y = int(ym/hr);
    qDebug()<<"mousePressEvent"<<x<<y;

    if (pe->buttons() & Qt::RightButton)
    {
        qDebug()<<"RightButton";
        game.setRoom(x,y);
        game.pathCreate(game.xTerminal,game.yTerminal);
        update();
    }

    if (pe->buttons() & Qt::LeftButton)
    {
        qDebug()<<"LeftButton";
        game.pathCreate(x,y);

        update();
    }
}
