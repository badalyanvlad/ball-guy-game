#include "brick.h"
#include <QPainter>
#include <QColor>

Brick::Brick(int health, QWidget *parent)
    : QWidget(parent), health_(health)
{
    setFixedSize(60, 25);
}

void Brick::hit()
{
    if (health_ > 0) {
        health_--;
        if (health_ <= 0) {
            hide();
        }
        update();
    }
}

void Brick::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (health_ > 0) {
        QColor outlineColor;
        switch (health_) {
        case 1:
            outlineColor = QColor(173, 216, 230);
            break;
        case 2:
            outlineColor = QColor(240, 182, 203);
            break;
        case 3:
            outlineColor = QColor(144, 238, 144);
            break;
        default:
            outlineColor = QColor(255, 245, 157);
            break;
        }

        painter.setPen(QPen(outlineColor, 2));
        painter.setBrush(Qt::white);
        painter.drawRect(0, 0, width() - 1, height() - 1);

        painter.setPen(Qt::black);
        painter.drawText(rect(), Qt::AlignCenter, QString::number(health_));
    }
}
