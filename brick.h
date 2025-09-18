#ifndef BRICK_H
#define BRICK_H

#include <QWidget>
#include <QLabel>
class Brick : public QLabel
{
    Q_OBJECT
public:
    explicit Brick(int health, QWidget *parent = nullptr);
    void changeHealth();
signals:
    void brickDestroyed(Brick* brick);
private:
    int health;

};

#endif // BRICK_H
