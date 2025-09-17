#include "ball.h"

Ball::Ball(QWidget *parent)
    : QLabel{parent},velocity(10)
{
    pointX = 200;
    pointY = 570;
}
void Ball::setVelocity(const int vel){
    velocity = vel;
}
int Ball::getVelocity(){
    return velocity;
}
