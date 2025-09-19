#include "bricks_factory.h"

BricksFactory::BricksFactory(QObject *parent)
    : QObject(parent)
{
}

BricksFactory::~BricksFactory()
{
    qDeleteAll(m_bricks);
}

QVector<Brick*> BricksFactory::createBricks(int numberOfBricks,
                                           int minHealth,
                                           int maxHealth,
                                           bool withBonus,
                                           QWidget *parent)
{
    reset();

    QVector<Brick*> result;
    result.reserve(numberOfBricks);

    for (int i = 0; i < numberOfBricks; ++i) {
        int health = QRandomGenerator::global()->bounded(minHealth, maxHealth + 1);

        Brick* brick = nullptr;
        if (withBonus && i % 5 == 0) {  //amen 5rdy bonus brick
            brick = new BonusBrick(health, parent);
        } else {
            brick = new Brick(health, parent);
        }

        result.append(brick);
    }

    m_bricks = result;
    return result;
}

void BricksFactory::reset()
{
    qDeleteAll(m_bricks);
    m_bricks.clear();
}
