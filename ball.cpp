#include "ball.h"

Ball::Ball(QWidget *parent)
    : QWidget{parent}, velocity(0,0)
{}

void Ball::setVelocity(const QVector2D& v) // գնդակի տալիս է արագություն
{
    velocity = v;
}

void Ball:: moveBall() //շարժում է գնդակը
{
    QPointF position = this->pos() + QPointF(velocity.x(), velocity.y());//նոր դիրքն ենք որոշում
    this->move(position.toPoint());
}
