#include "widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

    vl = new QVBoxLayout(this);
    screen = new Screen;
    gameTxt = new QLineEdit;
    pbStart = new QPushButton("start");
    pbStop = new QPushButton("stop");
    pbl = new QHBoxLayout;
    vl->addWidget(screen);
    vl->addWidget(gameTxt);
    vl->addLayout(pbl);
    pbl->addWidget(pbStart);
    pbl->addWidget(pbStop);


    connect(pbStart, SIGNAL(clicked()), this, SLOT(startT()));
    connect(pbStop, SIGNAL(clicked()), this, SLOT(stopT()));
    connect(screen, SIGNAL(setTXT(QString)), gameTxt, SLOT(setText(QString)));
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
