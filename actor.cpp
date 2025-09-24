#include "actor.h"
#include <QPainter>
#include <QtMath>

Actor::Actor(QWidget *parent) : QWidget(parent)
{
    setFixedSize(80, 15);
}

void Actor::move(float x)
{
    float newX = std::max(0.0f, std::min(x, float(parentWidget()->width() - width())));
    QWidget::move(int(newX), y());
}

void Actor::fire(float angle, QVector<Ball*>& balls)
{
    Ball* newBall = new Ball(parentWidget());
    QVector2D v(qCos(angle)*10.0f, qSin(angle)*-10.0f);
    newBall->setVelocity(v);

    newBall->move(x() + width()/2 - newBall->width()/2, y() - newBall->height());
    balls.push_back(newBall);
    newBall->show();
}

void Actor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::black);
    painter.drawRect(rect());
}
