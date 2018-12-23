#include "screen.h"

Screen::Screen(QWidget *parent) : QWidget(parent)
{
    t=new QTimer;
    connect(t,SIGNAL(timeout()),this,SLOT(step()));
    setMinimumSize(1024,768);
    imgCharUp.load(":/img/charUp.png");
    imgCharDown.load(":/img/charDown.png");
    imgCharLeft.load(":/img/charLeft.png");
    imgCharRight.load(":/img/charRight.png");
    imgCharUpLeft.load(":/img/charUpLeft.png");
    imgCharUpRight.load(":/img/charUpRight.png");
    imgCharDownLeft.load(":/img/charDownLeft.png");
    imgCharDownRight.load(":/img/charDownRight.png");
    imgWallUp.load(":/img/wallUp.png");
    imgWallDown.load(":/img/wallDown.png");
    imgWallLeft.load(":/img/wallLeft.png");
    imgWallRight.load(":/img/wallRight.png");
    imgWallUpLeft.load(":/img/wallUpLeft.png");
    imgWallUpRight.load(":/img/wallUpRight.png");
    imgWallDownLeft.load(":/img/wallDownLeft.png");
    imgWallDownRight.load(":/img/wallDownRight.png");
    imgGuardUp.load(":/img/guardUp.png");
    imgGuardDown.load(":/img/guardDown.png");
    imgGuardLeft.load(":/img/guardLeft.png");
    imgGuardRight.load(":/img/guardRight.png");
    imgSpace.load(":/img/space.png");
    imgPIT.load(":/img/PIT.png");
    imgImpty.load(":/img/impty.png");
    imgGUNUp.load(":/img/gunUp.png");
    imgGUNDown.load(":/img/gunDown.png");
    imgGUNLeft.load(":/img/gunLeft.png");
    imgGUNRight.load(":/img/gunRight.png");
    imgFireBoll.load(":/img/fireBoll.png");
    imgFinish.load(":/img/win.png");

}

void Screen::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
//    QPen pen(Qt::white);
//    QBrush brush(Qt::white);


    double w=width(), h=height(), s;
    paint.translate(w/2,0);
    if (w < h) {
        s = h/w;
        h = w = w / 1.41;
        paint.scale(1,s);
    }
    else {
        s = w/h;
        w = h = h / 1.41;
        paint.scale(s,1);
    }
    paint.rotate(45);
    QMatrix rot;
    rot.rotate(-45);

    double wr=w/N_ROOM_X, hr=h/ N_ROOM_Y;

    for(int i = 0; i < N_ROOM_X; i++)
        for(int j = 0; j < N_ROOM_Y; j++)
        {
            int dir = game.getRoomDir(i,j);
            switch (game.getRoom(i,j)) {
            case SPACE:
//                pen.setColor(Qt::white);
//                brush.setColor(Qt::white);
                img0 = imgSpace;
                img = imgImpty;
                break;
            case CHARACTER:
//                pen.setColor(Qt::green);
//                brush.setColor(Qt::green);
                img0 = imgSpace;
                if (dir == UP) img = imgCharUp;
                if (dir == DOWN) img = imgCharDown;
                if (dir == LEFT) img = imgCharLeft;
                if (dir == RIGHT) img = imgCharRight;
                if (dir == UP_LEFT) img = imgCharUpLeft;
                if (dir == UP_RIGHT) img = imgCharUpRight;
                if (dir == DOWN_LEFT) img = imgCharDownLeft;
                if (dir == DOWN_RIGHT) img = imgCharDownRight;
                if (dir == STILL) img = imgCharDown;
                img = img.transformed(rot);
                break;
            case PIT:
//                pen.setColor(Qt::black);
//                brush.setColor(Qt::black);
                img0 = imgSpace;
                img = imgPIT;
                break;
            case WALL:
//                pen.setColor(Qt::gray);
//                brush.setColor(Qt::gray);
                if (dir == UP) img0 = imgWallUp;
                if (dir == DOWN) img0 = imgWallDown;
                if (dir == LEFT) img0 = imgWallLeft;
                if (dir == RIGHT) img0 = imgWallRight;
                if (dir == UP_LEFT) img0 = imgWallUpLeft;
                if (dir == UP_RIGHT) img0 = imgWallUpRight;
                if (dir == DOWN_LEFT) img0 = imgWallDownLeft;
                if (dir == DOWN_RIGHT) img0 = imgWallDownRight;
                img = imgImpty;
                break;
            case GUARD:
//                pen.setColor(Qt::blue);
//                brush.setColor(Qt::blue);
                img0 = imgSpace;
                if (dir == UP) img = imgGuardUp;
                if (dir == DOWN) img = imgGuardDown;
                if (dir == LEFT) img = imgGuardLeft;
                if (dir == RIGHT) img = imgGuardRight;
                img = img.transformed(rot);
                break;
            case FIREBALL:
//                pen.setColor(Qt::red);
//                brush.setColor(Qt::red);
                img0.load(":/img/space.png");
                img.load(":/img/fireBoll.png");
                break;
            case GUN:
//                pen.setColor(Qt::darkRed);
//                brush.setColor(Qt::darkRed);
                if (dir == UP) img0 = imgWallUp;
                if (dir == DOWN) img0 = imgWallDown;
                if (dir == LEFT) img0 = imgWallLeft;
                if (dir == RIGHT) img0 = imgWallRight;
                if (dir == UP_LEFT) img0 = imgWallUpLeft;
                if (dir == UP_RIGHT) img0 = imgWallUpRight;
                if (dir == DOWN_LEFT) img0 = imgWallDownLeft;
                if (dir == DOWN_RIGHT) img0 = imgWallDownRight;

                if (dir == UP) img = imgGUNUp;
                if (dir == DOWN) img = imgGUNDown;
                if (dir == LEFT) img = imgGUNLeft;
                if (dir == RIGHT) img = imgGUNRight;
                break;
            case FINISH:
//                pen.setColor(Qt::darkGreen);
//                brush.setColor(Qt::darkGreen);
                img0 = imgSpace;
                img = imgFinish;
                break;
            default:
                break;
            }
//            paint.setPen(pen);
//            paint.setBrush(brush);
//            paint.drawRect(QRect(wr*i,hr*j,wr,hr));
            paint.drawImage(QRect(wr * i,hr * j ,wr+1,hr+1),img0);

            paint.drawImage(QRect(wr * i,hr * j ,wr+1,hr+1),img);
        }


    if (game.gameStatus == WIN)
    {
        emit setTXT("победа!!!");
        stopT();
    }
    if (game.gameStatus == DEAD)
    {
        emit setTXT("ПОТРАЧЕНО");
        stopT();
    }
    if (game.gameStatus == BRICK)
    {
        emit setTXT("пути нет");
    }
    if (game.gameStatus == GOING)
    {
        emit setTXT("в пути");
    }



}

void Screen::startT()
{
    qDebug()<<"start";
    t->start(TIME);
    game.pathCreate(1,1);

}

void Screen::stopT()
{
    t->stop();
    game.createGame();
    update();
}

void Screen::step()
{
    //    qDebug()<<"step";
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
