#ifndef ACTOR_H
#define ACTOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QString>
#include <QPoint>

#include "ball.h"

class Actor : public QWidget{

    Q_OBJECT

public:
    explicit Actor(QWidget *parent = nullptr,int balls = 20);
    void setPos(double x,double y);
    double getPosX();
    double getPosY();
    void updateSize();
    void setBallCount(int);
private:
    double posX;
    double posY;
    QLabel* act;
    QLabel* ballCount;
};

#endif // ACTOR_H
