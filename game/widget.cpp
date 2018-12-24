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

    pbStop->setDisabled(1);
    connect(screen, SIGNAL(stop()), this, SLOT(stop()));
}

Widget::~Widget()
{

}

void Widget::startT()
{
    pbStop->setEnabled(1);
    pbStart->setDisabled(1);
    screen->startT();
}

void Widget::stopT()
{
    pbStop->setDisabled(1);
    pbStart->setEnabled(1);
    screen->stopT();
}

void Widget::stop()
{
    pbStop->setDisabled(1);
    pbStart->setEnabled(1);
}

void Widget::t()
{

}

void Widget::setCb(int k)
{

}
