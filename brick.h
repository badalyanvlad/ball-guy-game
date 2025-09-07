#ifndef BRICK_H
#define BRICK_H

#include <QWidget>

class Brick : public QWidget
{
    Q_OBJECT
public:
    explicit Brick(int health, QWidget *parent = nullptr);

signals:

private:
    int health;
};

#endif // BRICK_H
