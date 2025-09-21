#include "ball.h"

Ball::Ball(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(300, 300);


}

void Ball::setVelocity(const QPoint& v){
    this->position.setX(v.x());
    this->position.setY(v.y());
}

void Ball::doesHittedWall(QWidget *widget){
    if(position.x() - radius < 0 || position.x() + radius > widget->width()){
        position.setX(-position.x());
    }
    if(position.y() - radius < 0){
        position.setY(-position.y());
    }
    if(position.y() > widget->height()){
        alive = false;
    }
}

void Ball::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(Qt::black, 6);
    painter.setPen(pen);
    painter.setBrush(Qt::red);

    int halfPen = pen.width() / 2;
    QRectF circleRect = rect().adjusted(halfPen, halfPen, -halfPen, -halfPen);
    painter.drawEllipse(circleRect);
}






















