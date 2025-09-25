#include "game_scene.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include "bricks_factory.h"

GameScene::GameScene(int brickCount, int brickRowCount, QWidget *parent)
    : QWidget(parent), aimBall(nullptr), ball_count(1), collected_balls(0), state(Aiming), aimAngle(0), bricksMovedThisTurn(false)
{
    setFixedSize(800, 600);
    setMouseTracking(true);
    startGame();
}

void GameScene::startGame()
{
    for (Ball* ball : balls) delete ball;
    balls.clear();
    for (Brick* brick : bricks) delete brick;
    bricks.clear();
    if (aimBall) delete aimBall;

    aimBall = new Ball(this);
    aimBall->move(width()/2 - aimBall->width()/2, height() - 50);
    aimBall->show();

    bricks = BricksFactory::createBricks(30, 1, 20, true, this);
    for (Brick* brick : bricks) {
        brick->show();
        if (BonusBrick* bonus = qobject_cast<BonusBrick*>(brick)) {
            connect(bonus, &BonusBrick::brickCrashed, this, [=]() {
                ball_count++;
                Ball* extra = new Ball(this);
                extra->move(width()/2 - extra->width()/2, height() - 50);
                extra->setVelocity(QVector2D(QRandomGenerator::global()->bounded(-5,5), -10));
                extra->show();
                balls.push_back(extra);
            });
        }
    }

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::updateGame);
    timer->start(16);
}

void GameScene::moveBalls()
{
    for (int i = 0; i < balls.size(); ++i) {
        Ball* ball = balls[i];
        ball->moveBall();

        if (ball->x() <= 0 || ball->x() + ball->width() >= width()) {
            QVector2D v = ball->velocity();
            v.setX(-v.x());
            ball->setVelocity(v);
        }
        if (ball->y() <= 0) {
            QVector2D v = ball->velocity();
            v.setY(-v.y());
            ball->setVelocity(v);
        }
        if (ball->y() + ball->height() >= height()) {
            int offset = collected_balls * ball->width();
            ball->move((width()/2 - (ball_count * ball->width() / 2)) + offset, height() - 50);
            ball->setVelocity(QVector2D(0, 0));
            collected_balls++;
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
                if (brick->isDestroyed()) {
                    brick->hide();
                    bricks.removeAt(j);
                    --j;
                }
                QVector2D v = ball->velocity();
                v.setY(-v.y());
                ball->setVelocity(v);
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
            QMessageBox msgBox;
            msgBox.setWindowTitle("Game Over");
            msgBox.setText("Game Over! Would you like to restart or quit?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, "Restart");
            msgBox.setButtonText(QMessageBox::No, "Quit");
            if (msgBox.exec() == QMessageBox::Yes) {
                startGame();
            } else {
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
            int health = QRandomGenerator::global()->bounded(1, 21);
            Brick* brick;
            if (QRandomGenerator::global()->bounded(10) < 1) {
                brick = new BonusBrick(this);
                connect(static_cast<BonusBrick*>(brick), &BonusBrick::brickCrashed, this, [=]() {
                    ball_count++;
                    Ball* extra = new Ball(this);
                    extra->move(width()/2 - extra->width()/2, height() - 50);
                    extra->setVelocity(QVector2D(QRandomGenerator::global()->bounded(-5,5), -10));
                    extra->show();
                    balls.push_back(extra);
                });
            } else {
                brick = new Brick(health, this);
            }
            int x = col * (brickW + spacing) + (800 - cols * (brickW + spacing)) / 2;
            int y = 10;
            brick->move(x, y);
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
    for (int i = 1; i < balls.size(); ++i) {
        delete balls[i];
    }
    if (!balls.isEmpty()) {
        balls[0]->move(width()/2 - balls[0]->width()/2, height() - 50);
        balls.resize(1);
    } else {
        Ball* newBall = new Ball(this);
        newBall->move(width()/2 - newBall->width()/2, height() - 50);
        newBall->show();
        balls.push_back(newBall);
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
        painter.setPen(Qt::yellow);
        QPointF center = aimBall->pos() + QPointF(aimBall->width()/2, aimBall->height()/2);
        QPointF end = center + QPointF(qCos(aimAngle) * 400, qSin(aimAngle) * 400);
        painter.drawLine(center, end);
    }
}

void GameScene::mouseMoveEvent(QMouseEvent *event)
{
    if (state == Aiming) {
        QPointF center = aimBall->pos() + QPointF(aimBall->width()/2, aimBall->height()/2);
        float dx = event->x() - center.x();
        float dy = event->y() - center.y();
        aimAngle = qAtan2(dy, dx);
        update();
    }
}

void GameScene::mousePressEvent(QMouseEvent* event)
{
    if (state == Aiming) {
        state = Firing;
        aimBall->hide();
        collected_balls = 0;

        for (Ball* ball : balls) delete ball;
        balls.clear();

        float spread = 0.0;
        for (int i = 0; i < ball_count; ++i) {
            Ball* ball = new Ball(this);
            ball->move(width()/2 - ball->width()/2, height() - 50);
            float angle = aimAngle;
            QVector2D dir(qCos(angle) * 10, qSin(angle) * 10);
            ball->setVelocity(dir);
            ball->show();
            balls.push_back(ball);
        }
    }
}
