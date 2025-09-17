#include "actor.h"

Actor::Actor(QWidget* parent):QLabel(parent){
    pointX = 200.0;
    pointY = 570.0;
}
void Actor::setPoint(double x){
    pointX = x;
}
void Actor::move(double x){
    this->QWidget::move(x, pointY);
}
