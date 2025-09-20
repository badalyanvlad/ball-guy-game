#include "game_scene.h"
#include <QMouseEvent>

GameScene::GameScene(int brickCount, int brickRowCount, QWidget *parent)
    : QWidget(parent),
    actor(new Actor(this))
{
    Q_UNUSED(brickCount);
    Q_UNUSED(brickRowCount);

    // Example: window size
    setFixedSize(800, 600);
}

void GameScene::startGame()
{
    // TODO: balls + bricks initialization
}

void GameScene::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    // TODO: aiming logic
}

void GameScene::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    // TODO: fire balls logic
}
