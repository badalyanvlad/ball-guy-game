#include "bonus_brick.h"
#include <QPainter>

BonusBrick::BonusBrick(QWidget* parent)
    : Brick(1, parent)
{
    setFixedSize(25, 25);
}

void BonusBrick::hit()
{
    Brick::hit();
    if (isDestroyed()) {
        emit brickCrashed();
    }
}

void BonusBrick::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (!isDestroyed()) {
        painter.setBrush(Qt::gray);
        painter.drawEllipse(rect());
    }
}
