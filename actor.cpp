#include "actor.h"
#include <QVector2D>
#include <QtMath>

Actor::Actor(QWidget *parent)
    : QWidget(parent)
{
}

void Actor::move(float x)
{
    QWidget::move(x, this->y());
}

void Actor::fire(float angle, const QVector<Ball*>& balls)
{
    QVector2D dir(qCos(angle), -qSin(angle));

    for (Ball* ball : balls)
    {
        if (ball)
            ball->setVelocity(dir);
    }
}
