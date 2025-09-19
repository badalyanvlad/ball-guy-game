#ifndef BONUS_BRICK_H
#define BONUS_BRICK_H

#include "brick.h"

class BonusBrick : public Brick
{
    Q_OBJECT
public:


    explicit BonusBrick(int health,QWidget *parent = nullptr);
    ~BonusBrick() override;

    void hit() override;      // override: երբ քանդվի  bonus գցի

signals:
    void brickCrashed();

};

#endif // BONUSBRICK_H
