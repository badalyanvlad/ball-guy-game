#include "ball.h"

Ball::Ball(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(15, 15);
    setAttribute(Qt::WA_TranslucentBackground);
}

void Ball::setVelocity(const QVector2D& v)
{

    m_velocity = v;
}

bool Ball::doesHitted(QWidget* widget)
{
    if (!widget) return false;
    return this->geometry().intersects(widget->geometry());
}

void Ball::moveBall() {
    move(x() + velocity().x(), y() + velocity().y());
}


void Ball::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    painter.fillRect(rect(), Qt::transparent);

    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);
    painter.drawEllipse(rect());
}
