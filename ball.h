#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QRect>
#include <QVector2D>
#include "brick.h"

class Ball : public QWidget
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    void setVelocity(const QVector2D& v);
    bool doesHitted(QWidget* widget);
    void moveBall();
    QVector2D velocity(){ return m_velocity;}

    void moveBallTo(float x, float y) {
        move(int(x), int(y));
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector2D m_velocity;

};

#endif // BALL_H
