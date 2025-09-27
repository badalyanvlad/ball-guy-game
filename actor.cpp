#include "actor.h"

Actor::Actor(QWidget* parent, int balls):QWidget(parent){
    QPixmap* pixmap  = new QPixmap(":/images/nkar.png");
    act = new QLabel(this);
    act->setPixmap(*pixmap);
    act->setScaledContents(true);
    this->resize(parent->height()/10,parent->height()/15);
    this->setPos(parent->width()/2 - this->width()/2,parent->height() - this->height());
    act->setGeometry(0,0,this->width()/2,this->height());
    ballCount = new QLabel("x" + QString::number(balls),this);

    QFont font = ballCount->font();
    font.setPointSize(10);
    ballCount->setFont(font);
    ballCount->setGeometry(this->width()/2, this->height()/3*2,
                           this->width()/2,this->height()/3);
}
void Actor::setPos(double x, double y){
    posX = x;
    posY = y;
    this->move(x,y);
}

double Actor::getPosX(){
    return posX;
}
double Actor::getPosY(){
    return posY;
}
void Actor::updateSize(){
    act->setGeometry(0,0,this->width()/2,this->height());
    this->resize(this->parentWidget()->height()/10,this->parentWidget()->height()/15);
    this->setPos(this->parentWidget()->width()/2 - this->width()/4,this->parentWidget()->height() - this->height());
}

void Actor::setBallCount(int balls){
    ballCount ->setText("x" + QString::number(balls));
}

