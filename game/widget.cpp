#include "widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

    vl = new QVBoxLayout(this);
    screen = new Screen;
    gameTxt = new QLabel;
    pbStart = new QPushButton("start");
    pbStop = new QPushButton("stop");
    pbl = new QHBoxLayout;
    vl->addWidget(screen);
    vl->addLayout(pbl);
    pbl->addWidget(gameTxt);
    pbl->addWidget(pbStart);
    pbl->addWidget(pbStop);


    connect(pbStart, SIGNAL(clicked()), this, SLOT(startT()));
    connect(pbStop, SIGNAL(clicked()), this, SLOT(stopT()));
}

Widget::~Widget()
{

}

void Widget::startT()
{
    screen->startT();
}

void Widget::stopT()
{
    screen->stopT();
}

void Widget::restart()
{

}

void Widget::t()
{

}

void Widget::setCb(int k)
{

}
