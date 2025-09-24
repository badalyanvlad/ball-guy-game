#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QWidget>
#include <QTimer>
#include "actor.h"
#include "ball.h"
#include "bonus_brick.h"
#include "brick.h"
#include <QLabel>

class GameScene : public QWidget
{
    Q_OBJECT

    enum class State {
        BallsAreFlying,
        ActorIsAiming,
    };
public:
    explicit GameScene(int brickCount, int brickRowCount, QWidget *parent = nullptr);

    void startGame();

    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:

private:
    QVector<BonusBrick*> bonusBricks;
    QVector<Brick*> bricks;
    QVector<Ball*> balls;
    Actor* actor;
    QTimer* timer;
    QLabel* livesLabel = nullptr;
    int lives = 3;

};

#endif // GAME_SCENE_H
