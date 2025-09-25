#ifndef BRICKS_FACTORY_H
#define BRICKS_FACTORY_H

#include "brick.h"
#include "bonus_brick.h"
#include <QVector>

class BricksFactory {
public:
    static QVector<Brick*> createBricks(int numberOfBricks,
                                         int minHealth,
                                         int maxHealth,
                                         bool withBonus,
                                         QWidget *parent);
};

#endif
