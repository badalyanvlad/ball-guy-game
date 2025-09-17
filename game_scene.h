#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QWidget>
#include <QVector>
#include <QTimer>

#include "actor.h"
#include "ball.h"
#include "bonus_brick.h"
#include "brick.h"

class GameScene : public QWidget
{
    Q_OBJECT

    enum State {
        BallsAreFlying,
        ActorIsAiming,
    };

public:
    explicit GameScene(int brickCount, int brickRowCount, QWidget *parent = nullptr);

    void startGame();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateGame();

private:
    QVector<BonusBrick*> bonusBricks;
    QVector<Brick*> bricks;
    QVector<Ball*> balls;
    Actor* actor;

    QTimer* gameTimer;
    State gameState;

    void initBricks(int brickCount, int brickRowCount);
    void checkCollisions();
};

#endif // GAME_SCENE_H
