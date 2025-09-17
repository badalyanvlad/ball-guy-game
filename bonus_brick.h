#ifndef BONUS_BRICK_H
#define BONUS_BRICK_H

#include "brick.h"

class BonusBrick : public Brick
{
    Q_OBJECT
public:
    enum BonusType { None, ExtraLife, ExpandPaddle, ShrinkPaddle, MultiBall, SlowBall, FastBall };

    explicit BonusBrick(int health, BonusType type, QWidget *parent = nullptr);
    ~BonusBrick() override;

    BonusType bonusType() const;

    void hit() override;      // override: երբ քանդվի  bonus գցի

signals:
    void bonusDropped(BonusType type);

private:
    BonusType m_type;
};

#endif // BONUSBRICK_H
