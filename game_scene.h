#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "ball.h"
#include "brick.h"
#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QMessageBox>

enum GameState { Aiming, Firing };

class GameScene : public QWidget {
    Q_OBJECT
public:
    GameScene(int brickCount, int brickRowCount, QWidget *parent = nullptr);
    void startGame();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private slots:
    void updateGame();
private:
    void moveBalls();
    bool handleCollisions();
    void moveBricks();
    void addNewBrickRow();
    void resetTurn();

    QVector<Ball*> balls;
    QVector<Brick*> bricks;
    Ball* aimBall;
    QPointF aimPoint;
    int ball_count;
    int collected_balls;
    GameState state;
    float aimAngle;
    bool bricksMovedThisTurn;
};

#endif
