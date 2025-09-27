#ifndef ACTOR_H
#define ACTOR_H

#include <QWidget>

#include "ball.h"

class Actor : public QWidget
{
    Q_OBJECT
public:
    explicit Actor(QWidget *parent = nullptr);

    void move(float x);

    void fire(float angle, const QVector<Ball*>& balls);
private:

};

#endif // ACTOR_H
