#include "ball.h"

Ball::Ball(QWidget *parent)
    : QLabel{parent},vector(0,0),velocity(5)
{
    this->setStyleSheet(
        "background-color: red;"
        "border-radius: 6px;"
        "color: white;"
        );

    this->setGeometry(200,570,12,12);
}

void Ball::setPos(double x,double y){
    posX = x;
    posY = y;
    this->move(posX, posY);
}

void Ball::setVector(QVector2D vector){
    this->vector = vector;
}

QVector2D Ball::getVector(){
    return vector;
}

void Ball::setVelocity(int vel){
    velocity = vel;
}

int Ball::getVelocity(){
    return velocity;
}

double Ball::getPosX(){
    return posX;
}

double Ball::getPosY(){
    return posY;
}
