#include "bonus_brick.h"

BonusBrick::BonusBrick(int health, QWidget *parent)
    : Brick(health, parent)
{
}

BonusBrick::~BonusBrick() {}

void BonusBrick::hit()
{
    Brick::hit();
    if (isDestroyed()) {
        emit brickCrashed();
    }
}
