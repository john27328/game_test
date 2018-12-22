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

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
    Game game;
    virtual void paintEvent(QPaintEvent*);
    QTimer *t;

signals:

public slots:
    void startT();
    void stopT();
    void step();
};

#endif // SCREEN_H
