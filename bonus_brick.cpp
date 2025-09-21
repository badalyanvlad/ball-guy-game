#include "bonus_brick.h"

BonusBrick::BonusBrick() {
    this->setFixedSize(15, 15);
}

void BonusBrick::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::yellow, 3);
    painter.setPen(pen);
    painter.setBrush(Qt::blue);
    QRect cr = rect().adjusted(pen.width()/2, pen.width()/2, -pen.width()/2, -pen.width()/2);
    painter.drawEllipse(cr);
}
