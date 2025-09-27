#include "brick.h"
#include "game_scene.h"
Brick::Brick(int health, QWidget *parent)
    : QLabel{parent}, health(health)
{
    this->setStyleSheet("background-color: red;"
                        "color:white;"
                        "border:2px solid black;"
                        "border-radius:8px");
    this->setAlignment(Qt::AlignCenter);
    this->setText(QString::number(health));
}
void Brick::setPos(int i, int j){
    posI = i;
    posJ = j;
}
int Brick::getPosI(){
    return posI;
}
int Brick::getPosJ(){
    return posJ;
}
void Brick::changeHealth(){
    if(--health == 0){
        emit brickDestroyed(this);
    }

    else
        this->setText(QString::number(health));
}

