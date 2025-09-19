#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>

class Ball : public QLabel
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    void setVelocity(int);
    int getVelocity();
    void setVector(QVector2D);
    QVector2D getVector();


private:
    QVector2D vector;
    int velocity;


};

#endif // BALL_H
