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
    if(position.x() - ball_radius < 0 || position.x() + ball_radius > widget->width()){
        position.setX(-position.x());
    }
    if(position.y() - ball_radius < 0){
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

void Ball::doesHitted(QVector<Brick*>& bricks){
    for(auto *b : bricks){
        QRect brick_shape = b->geometry();
        QRect ball_shape(position.x(), position.y(), ball_radius*2, ball_radius*2);
        if(brick_shape.intersects(ball_shape)){
            QRectF overlap = brick_shape.intersected(ball_shape);
            b->reduce_health();
            if (overlap.width() < overlap.height()) {
                velocity.setX(-velocity.x());
            } else {
                velocity.setY(-velocity.y());
            }
        }
    }
}




















