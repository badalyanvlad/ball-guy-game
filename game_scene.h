#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>
#include <random>
#include <algorithm>
#include <QThread>

#include "actor.h"
#include "ball.h"
//#include "bonus_brick.h"
//#include "brick.h"


class GameScene : public QWidget
{
    Q_OBJECT

    enum class State {
        BallsAreFlying,
        ActorIsAiming,
        Wait
    };
public:
    explicit GameScene(/*int brickCount, int brickRowCount,*/ QWidget *parent = nullptr);

    void startGame();
    void fireAnim();
    void fire(double dx1, double dy1);
    /**
     * shows balls fire direction
     */
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void mouseupdate(double mousePosX, double mousePosY);
    void timerStop();

signals:
    void readyToFire(double,double);
private:
    State s;
    QTimer* timer;
    QVector<Ball*> balls;    //QVector<BonusBrick*> bonusBricks;
    QList<QWidget*> bricks;
    QList<QLabel*> ballsForAim;
    Actor* actor;
    Ball* ball;
    int currentBallIndex = 0;
    // double ballX;
    // double ballY;
    double dx;
    double dy;
};

#endif // GAME_SCENE_H
