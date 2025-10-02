#include "ball.h"
#include <QPainter>

Ball::Ball(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(20, 20);
    m_velocity = QVector2D(0, 0);
}

void Ball::setVelocity(const QVector2D& v)
{
    m_velocity = v;
}

QVector2D Ball::velocity() const
{
    return m_velocity;
}

bool Ball::doesHitted(QWidget* widget)
{
    if (!widget) return false;
    return this->geometry().intersects(widget->geometry());
}

void Ball::moveBall()
{
    move(x() + m_velocity.x(), y() + m_velocity.y());
}

void Ball::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.drawEllipse(rect());
}
