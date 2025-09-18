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
#include "brick.h"


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
    void addNewLineBrickes();
    void startGame();
    void fireAnim();
    void fire();
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void mouseupdate(double mousePosX, double mousePosY);
    void timerStop();
public slots:
    void removeBrick(Brick* brick);
signals:
    void readyToFire(double,double);
private:
    void brickCreating();
private:
    State s;
    QTimer* timer;
    QVector<Ball*> balls;    //QVector<BonusBrick*> bonusBricks;
    QVector<Brick*> bricks;
    QList<QLabel*> ballsForAim;
    Actor* actor;
    int lowestBrick;
    bool actorpos;
    int currentBallIndex;
    int count;
    int k1;
    double dx;
    double dy;

};

#endif // GAME_SCENE_H
