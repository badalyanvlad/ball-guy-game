#ifndef BONUS_BRICK_H
#define BONUS_BRICK_H

#include "brick.h"

class BonusBrick : public Brick
{
    Q_OBJECT
public:
    explicit BonusBrick(int health, QWidget *parent = nullptr);
    ~BonusBrick() override;
    void hit() override;

signals:
    void brickCrashed();

protected:
  //  void paintEvent(QPaintEvent *event) override;
};

#endif // BONUS_BRICK_H
