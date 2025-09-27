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
    void setPos(int i,int j);
    int getPosJ();
    int getPosI();
signals:
    void brickDestroyed(Brick* brick);
private:
    int posI;
    int posJ;
    int health;


};

#endif // BRICK_H
