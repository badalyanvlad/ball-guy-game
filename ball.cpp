#include "ball.h"

Ball::Ball(QWidget *parent)
    : QLabel{parent}, dx(0), dy(0)
{
    this->setStyleSheet(
        "background-color: red;"
        "border-radius: 5px;"
        "color: white;"
        );

    this->setGeometry(200,570,12,12);

}
void Ball::setVelocity(double dx1, double dy1){
    dx = dx1 * 5;
    dy = dy1 * 5;
}
bool Ball::getVelocity(){
    return dx && dy;
}

