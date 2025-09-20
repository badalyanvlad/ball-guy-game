#include "bricks_factory.h"

BricksFactory::BricksFactory(QObject *parent)
    : QObject(parent) {}

BricksFactory::~BricksFactory() {}

QVector<Brick*> BricksFactory::createBricks(int numberOfBricks,
                                             int minHealth,
                                             int maxHealth,
                                             bool withBonus,
                                             QWidget *parent)
{

    QVector<Brick*> bricks;
    int cols = 10;
    int spacing = 5;
    int brickW = 60;
    int brickH = 25;

    for (int i = 0; i < numberOfBricks; ++i) {
        int row = i / cols;
        int col = i % cols;

        int health = QRandomGenerator::global()->bounded(minHealth, maxHealth+1);

        Brick* brick;
        if (withBonus && i % 7 == 0) {
            brick = new BonusBrick(health, parent);
        } else {
            brick = new Brick(health, parent);
        }

        brick->move(col * (brickW + spacing), row * (brickH + spacing));
        bricks.push_back(brick);
    }

    return bricks;
}

