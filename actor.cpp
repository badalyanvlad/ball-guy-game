#include "actor.h"
#include <QPainter>
#include <QtMath>

Actor::Actor(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(100, 15);
}

void Actor::move(float x, float y)
{
    QWidget::move(x, y);
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

void Actor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);

    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(Qt::blue));
    p.drawRect(rect());
}
