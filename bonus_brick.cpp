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
void BonusBrick::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(!isDestroyed())
    {
        painter.setBrush(Qt::gray);
        painter.setPen(Qt::NoPen);

        painter.drawEllipse(rect());
    }
}
