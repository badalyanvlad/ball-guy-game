#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QWidget>

#include "actor.h"
#include "ball.h"
#include "bonus_brick.h"
#include "brick.h"

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

    /**
     * shows balls fire direction
     */
    void mouseMoveEvent(QMouseEvent *event) override {}

    /**
     * fires balls
     */
    void mouseReleaseEvent(QMouseEvent *event) override {}

signals:

private:
    QVector<BonusBrick*> bonusBricks;
    QVector<Brick*> bricks;
    QVector<Ball*> balls;
    Actor* actor;
};

#endif // GAME_SCENE_H
