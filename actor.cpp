#include "actor.h"
#include <QDebug>
#include <QtMath>
#include <QVector2D>

Actor::Actor(QWidget *parent)
    : QWidget(parent)
{

    setFixedSize(80, 20);
    setStyleSheet("background-color: blue;");
}

void Actor::move(float x)
{

    if (!parentWidget()) return;
    //sahmanapakum e x arjeqnery aynpes vor actory chancni parent window sahmannery
    //newX misht linelu e [0, parentWidth - actorWidth] mijakayqum
    int newX = qBound(0, (int)x, parentWidget()->width() - width());
    setGeometry(newX, parentWidget()->height() - height() - 10, width(), height());
    //uxxankayan nor dirq enq dnum
}

void Actor::fire(float angle, const QVector<Ball*>& balls)
{
    float speed = 6.0f;
    QVector2D v(qCos(angle) * speed, -qSin(angle) * speed);

    for (Ball* b : balls) {
        if (b) {
            b->setGeometry(geometry().center().x() - 10,
                           geometry().y() - 20,
                           20, 20);
            b->setVelocity(v);
        }
    }
}
