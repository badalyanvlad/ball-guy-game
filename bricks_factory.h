
#ifndef BRICKS_FACTORY_H
#define BRICKS_FACTORY_H

#include <QVector>
#include <QRandomGenerator>
#include "brick.h"
#include "bonus_brick.h"

class BricksFactory : public QObject
{
    Q_OBJECT
public:
    explicit BricksFactory(QObject *parent = nullptr);
    ~BricksFactory();

   static QVector<Brick*> createBricks(int numberOfBricks,
                                  int minHealth,
                                  int maxHealth,
                                  bool withBonus,
                                  QWidget *parent = nullptr);



};

#endif // BRICKS_FACTORY_H
