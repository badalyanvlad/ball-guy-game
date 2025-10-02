#include "brick.h"
#include <QPainter>
#include <QColor>

Brick::Brick(int health, QWidget *parent)
    : QWidget(parent), m_health(health)
{
    setFixedSize(60, 25);
}

void Brick::hit()
{
    if (m_health > 0) {
        m_health--;
        if (m_health <= 0) {
            hide();
        }
        update();
    }
}

void Brick::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (m_health > 0) {

        QColor colors[10] = {
            QColor(255, 245, 157),
            QColor(173, 216, 230),
            QColor(240, 182, 203),
            QColor(144, 238, 144),
            QColor(144, 125, 111),
            QColor(155, 214, 75 ),
            QColor(100, 100, 100),
            QColor(204, 255, 204),
            QColor(204, 153, 255),
            QColor(0 ,  204, 255),
        };

        int index = (m_health >= 1 && m_health <= 9) ? m_health : 0;
        QColor outlineColor = colors[index];

        painter.setPen(QPen(outlineColor, 7));
        painter.setBrush(Qt::white);
        painter.drawRect(0, 0, width() - 1, height() - 1);

        painter.setPen(Qt::black);
        painter.drawText(rect(), Qt::AlignCenter, QString::number(m_health));
    }
}
