#include "game_scene.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QMessageBox>
#include <QPushButton>
#include "bricks_factory.h"


GameScene::GameScene(int brickCount, int brickRowCount, QWidget *parent)
    : QWidget(parent), aimBall(nullptr), ball_count(1), collected_balls(0), state(Aiming), aimAngle(0), bricksMovedThisTurn(false),
    sequentialLaunchTimer(nullptr), pendingBalls(0), launchAngle(0.0f)
{
    setFixedSize(800, 600);
    setMouseTracking(true);
    startGame();
}

GameScene::~GameScene()
{
    endGame();
}

void GameScene::startGame()
{
    endGame();

    aimBall = new Ball(this);
    aimBall->move(width()/2 - aimBall->width()/2, height() - 50);
    aimBall->show();

    bricks = BricksFactory::createBricks(30, 1, 20, true, this);
    for (Brick* brick : bricks) {
        brick->show();
        if (BonusBrick* bonus = qobject_cast<BonusBrick*>(brick)) {
            connect(bonus, &BonusBrick::brickCrashed, this, [=]() {
                ball_count++;
            });
        }
    }

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::updateGame);
    timer->start(16);
}

void GameScene::endGame()
{
    for (Ball* ball : balls) delete ball;
    balls.clear();
    for (Brick* brick : bricks) delete brick;
    bricks.clear();
    if (aimBall) {
        delete aimBall;
        aimBall = nullptr;
    }
    if (sequentialLaunchTimer) {
        sequentialLaunchTimer->stop();
        delete sequentialLaunchTimer;
        sequentialLaunchTimer = nullptr;
    }
    collected_balls = 0;
    pendingBalls = 0;
    ball_count = 1;
    state = Aiming;
}


void GameScene::moveBalls()
{
    for (int i = 0; i < balls.size(); ++i) {
        Ball* ball = balls[i];
        ball->moveBall();

        if (ball->y() < 50 && qAbs(ball->velocity().y()) < 1.0f) {
            QVector2D v = ball->velocity();
            v.setY(5.0f);
            ball->setVelocity(v);
        }

        if (ball->x() <= 0) {
            QVector2D v = ball->velocity();
            v.setX(-v.x());
            if (qFuzzyCompare(v.x(), 0.0f)) v.setX(1.0f);
            ball->setVelocity(v);
            ball->move(1, ball->y());
        } else if (ball->x() + ball->width() >= width()) {
            QVector2D v = ball->velocity();
            v.setX(-v.x());
            if (qFuzzyCompare(v.x(), 0.0f)) v.setX(-1.0f);
            ball->setVelocity(v);
            ball->move(width() - ball->width() - 1, ball->y());
        }

        if (ball->y() <= 0) {
            QVector2D v = ball->velocity();
            v.setY(-v.y());
            ball->setVelocity(v);
            ball->move(ball->x(), 1);
        }


        if (ball->y() + ball->height() >= height()) {
            int offset = collected_balls * ball->width();
            ball->move((width()/2 - (ball_count * ball->width() / 2)) + offset, height() - 50);
            ball->setVelocity(QVector2D(0, 0));
            collected_balls++;
        } else if (ball->y() > height() + 50) {
            collected_balls++;
            ball->hide();
        }
    }
}


bool GameScene::handleCollisions()
{
    bool anyHit = false;
    for (int i = 0; i < balls.size(); ++i) {
        Ball* ball = balls[i];
        for (int j = 0; j < bricks.size(); ++j) {
            Brick* brick = bricks[j];
            if (!brick->isDestroyed() && ball->doesHitted(brick)) {
                brick->hit();
                anyHit = true;


                if (BonusBrick* bonus = qobject_cast<BonusBrick*>(brick)) {
                    if (brick->isDestroyed()) {
                        ball_count++;
                    }
                }

                float ballLeft = ball->x();
                float ballRight = ball->x() + ball->width();
                float ballTop = ball->y();
                float ballBottom = ball->y() + ball->height();

                float brickLeft = brick->x();
                float brickRight = brick->x() + brick->width();
                float brickTop = brick->y();
                float brickBottom = brick->y() + brick->height();

                float dxLeft = ballRight - brickLeft;
                float dxRight = ballLeft - brickRight;

                QVector2D v = ball->velocity();
                bool horizontalHit = qAbs(dxLeft) < qAbs(dxRight) && dxLeft > 0;
                horizontalHit = horizontalHit || (qAbs(dxRight) < qAbs(dxLeft) && dxRight > 0);
                if (horizontalHit) {
                    v.setX(-v.x());
                } else {
                    v.setY(-v.y());
                }
                ball->setVelocity(v);

                if (brick->isDestroyed()) {
                    brick->hide();
                    bricks.removeAt(j);
                    --j;
                }
                break;
            }
        }
    }
    return anyHit;
}


void GameScene::moveBricks()
{
    for (Brick* brick : bricks) {
        brick->move(brick->x(), brick->y() + 25);
        if (brick->y() + brick->height() >= height()) {
            QMessageBox msgBox(QMessageBox::Question, "Game Over", "Game Over! Would you like to restart or quit?");
            QPushButton *restartButton = msgBox.addButton("Restart", QMessageBox::YesRole);
            QPushButton *quitButton = msgBox.addButton("Quit", QMessageBox::NoRole);
            (void)quitButton;
            msgBox.exec();
            if (msgBox.clickedButton() == restartButton) {
                startGame();
            } else {
                endGame();
                qApp->quit();
            }
        }
    }
}


void GameScene::addNewBrickRow()
{
    int cols = QRandomGenerator::global()->bounded(6, 11);
    int spacing = 5;
    int brickW = 60;
    int brickH = 25;
    for (int col = 0; col < cols; ++col) {
        if (QRandomGenerator::global()->bounded(100) < 70) {
            int health = QRandomGenerator::global()->bounded(1, 11);
            Brick* brick;
            if (QRandomGenerator::global()->bounded(10) < 1) {
                brick = new BonusBrick(this);

                connect(static_cast<BonusBrick*>(brick), &BonusBrick::brickCrashed, this, [=]() {
                    ball_count++;
                });
            } else {
                brick = new Brick(health, this);
            }
            int x = col * (brickW + spacing) + (800 - cols * (brickW + spacing)) / 2;
            int y = 10;
            brick->move(x, y);
            if (qobject_cast<BonusBrick*>(brick)) {

                brick->setFixedSize(21, 21);
            } else {
                brick->setFixedSize(brickW, brickH);
            }
            brick->show();
            bricks.push_back(brick);
        }
    }
}


void GameScene::resetTurn()
{
    collected_balls = 0;
    bricksMovedThisTurn = false;
    state = Aiming;
    aimBall->show();

    for (Ball* ball : balls) delete ball;
    balls.clear();

    if (sequentialLaunchTimer) {
        sequentialLaunchTimer->stop();
        delete sequentialLaunchTimer;
        sequentialLaunchTimer = nullptr;
    }
    pendingBalls = 0;
}


void GameScene::launchNextBall()
{
    Ball* ball = new Ball(this);
    ball->move(width()/2 - ball->width()/2, height() - 50);

    float speed = 8.0f;
    QVector2D dir(qCos(launchAngle) * speed, qSin(launchAngle) * speed);

    if (qAbs(dir.y()) < 2.0f) {
        dir.setY(-2.0f);
    }

    ball->setVelocity(dir);
    ball->show();
    balls.push_back(ball);

    pendingBalls--;
    if (pendingBalls <= 0) {
        if (sequentialLaunchTimer) {
            sequentialLaunchTimer->stop();
            delete sequentialLaunchTimer;
            sequentialLaunchTimer = nullptr;
        }
    }
}


void GameScene::updateGame()
{
    if (state == Firing) {
        moveBalls();
        handleCollisions();

        if (collected_balls == balls.size()) {
            resetTurn();
            moveBricks();
            addNewBrickRow();
            update();
        }
    }

    if (bricks.isEmpty()) {
        startGame();
    }

    update();
}


void GameScene::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    if (state == Aiming && aimBall && aimBall->isVisible()) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::yellow, 2, Qt::DashLine));

        QPointF pos = aimBall->pos() + QPointF(aimBall->width()/2, aimBall->height()/2);
        float vx = qCos(aimAngle) * 8.0f;
        float vy = qSin(aimAngle) * 8.0f;
        if (qAbs(vy) < 2.0f) {
            vy = -2.0f;
        }

        const int maxBounces = 5;
        QPointF current = pos;

        for (int bounce = 0; bounce < maxBounces; ++bounce) {
            float dx = width() - current.x();

            float minDist = 400.0f;
            QPointF next = current + QPointF(vx * 40, vy * 40);

            if (vx > 0) {
                float t = (width() - current.x()) / vx;
                if (t > 0 && t * 8 < minDist) {
                    minDist = t * 8;
                    next = QPointF(width(), current.y() + vy * t);
                    vx = -vx;
                }
            }
            if (vx < 0) {
                float t = -current.x() / vx;
                if (t > 0 && t * 8 < minDist) {
                    minDist = t * 8;
                    next = QPointF(0, current.y() + vy * t);
                    vx = -vx;
                }
            }

            if (vy < 0) {
                float t = -current.y() / vy;
                if (t > 0 && t * 8 < minDist) {
                    minDist = t * 8;
                    next = QPointF(current.x() + vx * t, 0);
                    vy = -vy;
                }
            }

            painter.drawLine(current, next);

            current = next;

            if (vy > 0 || current.y() > height()) break;
        }
    }
}


void GameScene::mouseMoveEvent(QMouseEvent *event)
{
    if (state == Aiming) {
        QPointF center = aimBall->pos() + QPointF(aimBall->width()/2, aimBall->height()/2);
        float dx = event->position().x() - center.x();
        float dy = event->position().y() - center.y();
        aimAngle = qAtan2(dy, dx);
        update();
    }
}


void GameScene::mousePressEvent(QMouseEvent* event)
{
    (void)event;
    if (state == Aiming) {
        state = Firing;
        aimBall->hide();
        collected_balls = 0;

        for (Ball* ball : balls) delete ball;
        balls.clear();

        launchAngle = aimAngle;
        pendingBalls = ball_count - 1;

        launchNextBall();

        if (pendingBalls > 0) {
            sequentialLaunchTimer = new QTimer(this);
            connect(sequentialLaunchTimer, &QTimer::timeout, this, &GameScene::launchNextBall);
            sequentialLaunchTimer->start(200);
        }
    }
}
