#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QWidget>
#include <QVector>
#include <QVector2D>
#include "ball.h"
#include "brick.h"
#include "bonus_brick.h"

class QTimer;
class QMouseEvent;
class QPaintEvent;

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(int brickCount, int brickRowCount, QWidget *parent = nullptr);
    ~GameScene();

public slots:
    void startGame();
    void updateGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    enum State { Aiming, Firing };

    Ball* aimBall;
    int ball_count;
    int collected_balls;
    State state;
    float aimAngle;
    bool bricksMovedThisTurn;

    QVector<Ball*> balls;
    QVector<Brick*> bricks;

    QTimer* sequentialLaunchTimer;
    int pendingBalls;
    float launchAngle;

    void moveBalls();
    bool handleCollisions();
    void moveBricks();
    void addNewBrickRow();
    void resetTurn();
    void launchNextBall();
    void endGame();
};

#endif // GAME_SCENE_H
