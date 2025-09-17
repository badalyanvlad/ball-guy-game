#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>
class Ball : public QLabel
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    void setVelocity(const int vel);
    int getVelocity();
    bool doesHitted(QWidget* widget);
    double pointX;
    double pointY;
private:
    int velocity;

};

#endif // BALL_H
