#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>

class Ball : public QLabel
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    void setVelocity(double, double);
    bool getVelocity();

    double dx, dy;
private:
    QVector2D vector;


};

#endif // BALL_H
