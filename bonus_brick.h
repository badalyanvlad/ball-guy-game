#ifndef BONUS_BRICK_H
#define BONUS_BRICK_H

#include "brick.h"
#include <QObject>

class BonusBrick : public Brick {
    Q_OBJECT
public:
    BonusBrick(QWidget* parent = nullptr);
    void hit() override;
signals:
    void brickCrashed();
protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif
