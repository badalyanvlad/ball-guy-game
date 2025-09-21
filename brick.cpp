#include "brick.h"

Brick::Brick(int health, QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(50,40);
    brick_label = new QLabel();
    brick_label->setText(QString::number(health));
    QVBoxLayout *brick_layout = new QVBoxLayout(this);
    brick_layout->addWidget(brick_label, 0, Qt::AlignCenter);
    this->setLayout(brick_layout);
}

Brick::Brick(int health, int x, int y, int h, int w, QWidget *parent) : QWidget{parent}, health(health), rect_m(x,y,w,h){

    this->setFixedSize(40,40);
}

void Brick::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::red);
    QPen pen(Qt::black);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(rect());
}
