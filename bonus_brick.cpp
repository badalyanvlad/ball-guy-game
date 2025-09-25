#include "bonus_brick.h"

BonusBrick::BonusBrick() {
    this->resize(40, 40);
    setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void BonusBrick::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::black);

    int squareSize = 10;
    int diameter = squareSize;
    int x = (width() - diameter) / 2;
    int y = (height() - diameter) / 2;

    painter.drawEllipse(x, y, diameter, diameter);
}
