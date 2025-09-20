#include "ball.h"

Ball::Ball(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(15, 15);
}

void Ball::setVelocity(const QVector2D& v)
{

    Q_UNUSED(v);
}

bool Ball::doesHitted(QWidget* widget)
{
    if (!widget) return false;
    return this->geometry().intersects(widget->geometry());
}
