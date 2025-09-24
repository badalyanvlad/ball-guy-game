#include "game_scene.h"
#include "ball.h"
#include "brick.h"
#include "bonus_brick.h"
#include "actor.h"
#include <QTimer>
#include <QVector2D>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QDebug>
#include <algorithm>

GameScene::GameScene(int brickCount, int brickRowCount, QWidget *parent)
    : QWidget(parent),
    actor(new Actor(this))
{
    setFixedSize(800, 600);


    actor->QWidget::move((width() - actor->width())/2, height() - actor->height() - 10);


    livesLabel = new QLabel(this);
    livesLabel->move(10, 10);
    livesLabel->setText("Lives: " + QString::number(lives));
    livesLabel->setStyleSheet("font-size: 18px; color: white;");

    startGame();
}

void GameScene::startGame()
{
    Ball* ball = new Ball(this);
    ball->move(width()/2 - ball->width()/2, height() - 50);
    ball->setVelocity(QVector2D(0, -5));
    balls.push_back(ball);
    ball->show();

    int cols = 10;
    int spacing = 5;
    int brickW = 60;
    int brickH = 25;
    int numberOfBricks = 30;

    for (int i = 0; i < numberOfBricks; ++i) {
        int row = i / cols;
        int col = i % cols;
        int health = QRandomGenerator::global()->bounded(1, 5);

        Brick* brick;
        if (i % 12 == 0)
            brick = new BonusBrick(health, this);
        else
            brick = new Brick(health, this);

        brick->move(col * (brickW + spacing), 50 + row * (brickH + spacing));
        brick->show();
        bricks.push_back(brick);
    }

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer]() {
        for (int i = balls.size() - 1; i >= 0; --i) {
            Ball* ball = balls[i];
            ball->moveBall();


            if (ball->x() <= 0) {
                ball->move(0, ball->y());
                QVector2D v = ball->velocity();
                v.setX(qAbs(v.x()));
                ball->setVelocity(v);
            }
            if (ball->x() + ball->width() >= width()) {
                ball->move(width() - ball->width(), ball->y());
                QVector2D v = ball->velocity();
                v.setX(-qAbs(v.x()));
                ball->setVelocity(v);
            }
            if (ball->y() <= 0) {
                ball->move(ball->x(), 0);
                QVector2D v = ball->velocity();
                v.setY(qAbs(v.y()));
                ball->setVelocity(v);
            }

            if (ball->y() + ball->height() >= actor->y() &&
                ball->y() + ball->height() <= actor->y() + actor->height() &&
                ball->x() + ball->width() >= actor->x() &&
                ball->x() <= actor->x() + actor->width())
            {
                QVector2D v = ball->velocity();
                float hitPos = (ball->x() + ball->width()/2) - actor->x();
                float ratio = (hitPos / actor->width()) - 0.5f;
                v.setX(ratio * 10);
                v.setY(-qAbs(v.y()));
                ball->setVelocity(v);
            }

            for (Brick* brick : bricks) {
                if (!brick->isDestroyed() && ball->doesHitted(brick)) {
                    brick->hit();

                    if (brick->isDestroyed()) {
                        brick->hide();

                        if (qobject_cast<BonusBrick*>(brick)) {
                            Ball* newBall = new Ball(this);
                            newBall->move(width()/2, height() - 60);
                            newBall->setVelocity(QVector2D(
                                (QRandomGenerator::global()->bounded(2) ? -3 : 3), -5));
                            newBall->show();
                            balls.push_back(newBall);
                        }
                    }

                    QRectF brickRect = brick->geometry();
                    QRectF ballRect = ball->geometry();
                    float overlapLeft = ballRect.right() - brickRect.left();
                    float overlapRight = brickRect.right() - ballRect.left();
                    float overlapTop = ballRect.bottom() - brickRect.top();
                    float overlapBottom = brickRect.bottom() - ballRect.top();
                    bool ballFromLeftRight = (overlapLeft < overlapTop && overlapLeft < overlapBottom) ||
                                             (overlapRight < overlapTop && overlapRight < overlapBottom);

                    QVector2D v = ball->velocity();
                    if (ballFromLeftRight) v.setX(-v.x());
                    else v.setY(-v.y());
                    ball->setVelocity(v);
                }
            }

            if (ball->y() + ball->height() >= height()) {
                balls.removeAt(i);
                ball->deleteLater();

                if (balls.isEmpty()) {
                    lives--;
                    livesLabel->setText("Lives: " + QString::number(lives));

                    if (lives > 0) {
                        Ball* newBall = new Ball(this);
                        newBall->move(width()/2 - newBall->width()/2, height() - 50);
                        newBall->setVelocity(QVector2D(0, -5));
                        newBall->show();
                        balls.push_back(newBall);
                    } else {
                        qDebug() << "Game Over!";
                        timer->stop();
                        return;
                    }
                }
            }
        }


    });
    timer->start(16);
}

void GameScene::mouseMoveEvent(QMouseEvent* event)
{
    actor->move(event->position().x() - actor->width()/2);
}

void GameScene::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    actor->fire(90 * M_PI / 180.0, balls);
}

