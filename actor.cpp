#include "actor.h"

Actor::Actor(QWidget* parent, int balls):QWidget(parent){
    QPixmap* pixmap  = new QPixmap(":/images/nkar.png");
    act = new QLabel(this);
    act->setPixmap(*pixmap);
    act->setScaledContents(true);
    // QHBoxLayout* layoutForActor = new QHBoxLayout(this);
    //this->setFixedSize(60,30);
    this->setGeometry(190,570,60,30);
    act->setGeometry(0,0,30,30);
    ballCount = new QLabel("x" + QString::number(balls),this);
    QFont font = ballCount->font();
    font.setPointSize(10);
    ballCount->setFont(font);
    ballCount->setGeometry(30,20,30,10);
    pointX = 200.0;
    pointY = 570.0;
}
void Actor::setPoint(double x){
    pointX = x;
}
void Actor::setBallCount(int balls){
    ballCount ->setText("x" + QString::number(balls));
}
void Actor::move(double x){
    this->QWidget::move(x, pointY);
}
