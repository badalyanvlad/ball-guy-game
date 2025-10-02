#include "bricks_factory.h"
#include <QRandomGenerator>

QVector<Brick*> BricksFactory::createBricks(int numberOfBricks,
                                             int minHealth,
                                             int maxHealth,
                                             bool withBonus,
                                             QWidget *parent)
{
    QVector<Brick*> bricks;
    int rows = QRandomGenerator::global()->bounded(3, 7);
    int cols = QRandomGenerator::global()->bounded(6, 11);
    int spacing = 5;
    int brickW = 60;
    int brickH = 25;
    int startY = 10;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (QRandomGenerator::global()->bounded(100) < 70) {
                int health = QRandomGenerator::global()->bounded(minHealth, 11);
                Brick* brick;
                if (withBonus && QRandomGenerator::global()->bounded(10) < 1) {
                    brick = new BonusBrick(parent);
                } else {
                    brick = new Brick(health, parent);
                }

                int x = col * (brickW + spacing) + (800 - cols * (brickW + spacing)) / 2;
                int y = startY + row * (brickH + spacing);
                brick->move(x, y);
                bricks.push_back(brick);
            }
        }
    }

    return bricks;
}
