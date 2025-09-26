#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <QThread>
#include <QMainWindow>
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
#include <QResizeEvent>

#include "gameover.h"
#include "actor.h"
#include "ball.h"
//#include "bonus_brick.h"
#include "brick.h"



class GameScene : public QMainWindow
{
    Q_OBJECT

    enum class State {
        BallsAreFlying,
        ActorIsAiming,
        Wait
    };
public:
    explicit GameScene( QWidget *parent = nullptr);
    void addNewLineBrickes();
    void startGame();
    void fireAnim();
    void fire();
    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void mouseupdate(double mousePosX, double mousePosY);
    void resizeEvent(QResizeEvent*);
    void timerStop();
    void updateSpatialGrid();
public slots:
    void removeBrick(Brick* brick);
signals:
    // void readyToFire(float,float);
private:
    void brickCreating();
private:
    static const int GRID_COLS = 10;
    static const int GRID_ROWS = 15;
    std::vector<QList<Brick*>> spatialGrid;
    int gridCellWidth;
    int gridCellHeight;
    QWidget* gameWidget;
    GameOver* gameoverWidget;
    State s;
    QTimer* timer;
    QVector<Ball*> balls;
    QVector<Brick*> bricks;
    QList<QLabel*> ballsForAim;
    Actor* actor;
    QPushButton * btn;
    int currentBallIndex;
    int count;
    int k1;
    double dx;
    double dy;

};

#endif // GAME_SCENE_H
