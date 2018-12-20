#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(200, 200);
    setMaximumSize(1024,720);
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(0);
    for (int i = 0; i < N_ROOM_X; i++)
        for (int j = 0; j < N_ROOM_Y; j++)
        {
            auto lbl = new QLabel;
            lbl->setPixmap(QPixmap(":/img/img/wag.PNG"));
            lbl->setScaledContents ( 1 );
            grid->addWidget(lbl,i,j);
         }
    //    ui->label->setScaledContents ( 1 );
//    ui->label->setPixmap(QPixmap(":/img/img/wag.PNG"));
//    ui->label_2->setScaledContents ( 1 );

}

Widget::~Widget()
{
    delete ui;
}
