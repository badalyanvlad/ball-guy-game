#ifndef BRICKS_MANAGER_H
#define BRICKS_MANAGER_H

#include <QObject>

class BricksManager : public QObject
{
    Q_OBJECT
public:
    explicit BricksManager(QObject *parent = nullptr);

signals:
};

#endif // BRICKS_MANAGER_H
