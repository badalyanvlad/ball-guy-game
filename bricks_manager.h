#ifndef BRICKS_MANAGER_H
#define BRICKS_MANAGER_H

#include <QObject>
#include <QVector>

#include "brick.h"

class BricksManager : public QObject
{
    Q_OBJECT
public:
    explicit BricksManager(QObject *parent = nullptr);
    //void creatingBricksRow(int count);

private:
    QVector<Brick> bricks;
signals:
};

#endif // BRICKS_MANAGER_H
