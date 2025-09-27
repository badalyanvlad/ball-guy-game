#include "gameover.h"

GameOver::GameOver(QWidget* parent):QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    label = new QLabel("GAME OVER",this);
    QFont font = label->font();
    font.setPointSize(25);
    font.setBold(true);
    label->setFont(font);
    label->setStyleSheet("color:red");
    mainLayout->addWidget(label);
    mainLayout->setAlignment(Qt::AlignHCenter);
}
