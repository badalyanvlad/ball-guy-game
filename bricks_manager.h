#ifndef BRICKSMANAGER_H
#define BRICKSMANAGER_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include "brick.h"
#include "bonus_brick.h"

class BricksManager : public QObject
{
    Q_OBJECT
public:
    explicit BricksManager(QObject *parent = nullptr);
    ~BricksManager();

    void createBricks(int rows, int cols, int brickWidth, int brickHeight, QWidget *parent = nullptr);
    const QVector<Brick*>& bricks() const;

    bool allDestroyed() const;
    void reset();

    void onBallHit(int brickWidth, int brickHeight, QWidget *parent = nullptr);
    bool checkGameOver(int windowHeight);

signals:
    void brickDestroyed(Brick* brick);
    void bonusDropped(BonusBrick::BonusType type);
    void gameOver();

private:
    QVector<Brick*> m_bricks;
    int m_brickWidth;
    int m_brickHeight;
};

#endif // BRICKSMANAGER_H
