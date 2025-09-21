#ifndef BONUS_BRICK_H
#define BONUS_BRICK_H

#include <QWidget>
#include <QPainter>

class BonusBrick : public QWidget
{
public:
    BonusBrick();
    void paintEvent(QPaintEvent*) override;
};

#endif // BONUS_BRICK_H
