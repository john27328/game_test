#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "game.h"
#include <QMainWindow>
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>
#include "screen.h"
#include <QLineEdit>


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    QLineEdit *gameTxt;

    QHBoxLayout *hl;
    QPushButton *pbStart;
    QPushButton *pbStop;
    QVBoxLayout *vl;
    Screen *screen;
    QCheckBox *cb;
    QHBoxLayout *pbl;
public slots:
    void startT();
    void stopT();
    void stop();
    void t();
    void setCb(int k);
};

#endif // WIDGET_H
