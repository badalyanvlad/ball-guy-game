#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QResizeEvent>

#include "actor.h"
#include "ball.h"
#include "bonus_brick.h"
#include "brick.h"
#include "bricks_manager.h"

class GameScene : public QWidget
{
    Q_OBJECT

    enum class State {
        Default_s,
        ActorIsAiming,
        BallsAreFlying,
    };
public:
    explicit GameScene(QWidget *parent = nullptr);

    void startGame();

    /**
     * shows balls fire direction
     */
    void mouseMoveEvent(QMouseEvent *event) override ;

    /**
     * fires balls
     */
    void mouseReleaseEvent(QMouseEvent *event) override ;

    void update();
    void set_state(State st);
    void showAiming();
    void ballsFlying();
    void addBallsByBonus(int count);
    void resizeEvent(QResizeEvent *event) override;
    void creating_brick_row();
    QVector<Brick*> getBricks();

signals:
    void bonusSignal();
public:
private:
    QVector<BonusBrick*> bonusBricks;
    QVector<Brick*> bricks;
    QVector<Ball*> balls;
    Actor* actor;
    State state;
    QTimer *timer;
};

#endif // GAME_SCENE_H
