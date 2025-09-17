#ifndef ACTOR_H
#define ACTOR_H

#include <QWidget>

#include "ball.h"

class Actor : public QLabel{

    Q_OBJECT

public:
    double pointX;
    double pointY;

    explicit Actor(QWidget *parent = nullptr);
    void setPoint(double x);
    void move(double x);

    //void fire(float angle, const QVector<Ball*>& balls);
};

#endif // ACTOR_H
