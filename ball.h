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
    void setVector(double, double);
    bool getVelocity();
    double pointX;
    double pointY;
    double dx, dy;
private:
    int velocity;

};

#endif // BALL_H
