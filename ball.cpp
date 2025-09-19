#include "ball.h"

Ball::Ball(QWidget *parent)
    : QWidget{parent}
{}


bool Ball::doesHitted(QWidget* widget) {
    Brick* brick = qobject_cast<Brick*>(widget);
    if (!brick) return false;

    QRect rectBall = this->geometry();
    QRect rectBrick = brick->geometry();

    return rectBall.intersects(rectBrick);
}
//stugum e ardyoq harvacel e qwidget tipi obyeckti te voch
