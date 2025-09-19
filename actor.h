#ifndef ACTOR_H
#define ACTOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QString>

#include "ball.h"

class Actor : public QWidget{

    Q_OBJECT

public:
    explicit Actor(QWidget *parent = nullptr,int balls = 20);
    void setPos(double x,double y);
    void setBallCount(int);
private:
    QLabel* act;
    QLabel* ballCount;
};

#endif // ACTOR_H
