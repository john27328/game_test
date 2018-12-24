#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include "game.h"
#include <QTimer>
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QImage>

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
    Game game;
    virtual void paintEvent(QPaintEvent*);
    QTimer *t;
    QImage img;
    QImage img0;
    QImage imgCharUp;
    QImage imgCharDown;
    QImage imgCharLeft;
    QImage imgCharRight;
    QImage imgCharUpLeft;
    QImage imgCharUpRight;
    QImage imgCharDownLeft;
    QImage imgCharDownRight;
    QImage imgWallUp;
    QImage imgWallDown;
    QImage imgWallLeft;
    QImage imgWallRight;
    QImage imgWallUpLeft;
    QImage imgWallUpRight;
    QImage imgWallDownLeft;
    QImage imgWallDownRight;
    QImage imgGuardUp;
    QImage imgGuardDown;
    QImage imgGuardLeft;
    QImage imgGuardRight;
    QImage imgSpace;
    QImage imgPIT;
    QImage imgImpty;
    QImage imgGUNUp;
    QImage imgGUNDown;
    QImage imgGUNLeft;
    QImage imgGUNRight;
    QImage imgFireBoll;
    QImage imgFinish;



signals:
    void setTXT(QString str);
    void stop();

public slots:
    void startT();
    void stopT();
    void step();
protected:
    virtual void mousePressEvent  (QMouseEvent* pe);
};

#endif // SCREEN_H
