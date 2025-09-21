#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QPainter>

class Ball : public QWidget
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    Ball(QPoint pos, QPoint vel = {1, 1}) : position(pos), velocity(vel), radius(10.0), alive(true){};

    void setVelocity(const QPoint& v);

    void doesHitted(QWidget* widget);

    void doesHittedWall(QWidget *widget);
protected:
    void paintEvent(QPaintEvent*) override;
signals:
    //void bonusSignal();
private:
    QPoint position;
    QPoint velocity;
    qreal radius;
    bool alive = true;
};

#endif // BALL_H
