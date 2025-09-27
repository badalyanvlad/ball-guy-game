#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>
#include <QVector2D>
class Ball : public QLabel
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    void setVelocity(int);
    int getVelocity();
    void setVector(QVector2D);
    QVector2D getVector();
    void setPos(double x, double y);
    double getPosX();
    double getPosY();

private:
    double posX;
    double posY;
    QVector2D vector;
    int velocity;


};

#endif // BALL_H
