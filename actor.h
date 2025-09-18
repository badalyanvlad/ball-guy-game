#ifndef ACTOR_H
#define ACTOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QString>

#include "ball.h"

class Actor : public QWidget{

    Q_OBJECT

public:

    double pointX;
    double pointY;

    explicit Actor(QWidget *parent = nullptr,int balls = 20);
    void setPoint(double x);
    void move(double x);
    void setBallCount(int);
private:
    QLabel* act;
    QLabel* ballCount;
    //void fire(float angle, const QVector<Ball*>& balls);
};

#endif // ACTOR_H
